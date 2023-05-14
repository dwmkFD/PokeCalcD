#pragma once

/* ダメージ計算メインヘッダ */
#include <Windows.h>
#include <afxdb.h>

#include <vector>
#include <map>
#include <memory>
#include <algorithm>

#include "pokemove.hpp"
#include "pokemon.hpp"

class CBattleSettings { // -> クラス名はいい感じに変えたいｗ
public:
	// 天気、フィールド、壁、手助け…などの状態を管理したい
	// -> メインダイアログのメンバ変数も、これにしたいね
	int m_weather; // 天気（0: なし、1: 晴れ、2: 雨、3: 砂、4: 雪）
	bool m_isBurned; // 火傷
	int m_barrier; // bit0: リフレクター、 bit1: 光の壁
	bool m_range; // ダブル補正（0: なし、1: あり）
	int m_ability; // 特性による補正
					// bit0: スナイパー、bit1: 色眼鏡、bit2: もふもふ(炎被弾)、bit3: フレンドガード、bit4: 氷の鱗粉、bit5: パンクロック(攻撃)
					// bit6: パンクロック(防御)、bit7: ファントムガード、bit8: マルチスケイル、bit9: もふもふ(接触技)、bit10: ハードロック/フィルター
					// bit11: プリズムアーマー
	bool m_twice; // 特定条件下で威力2倍判定 // -> これは攻撃技側にデータを持たせるべきだと思われる
	int m_item; // アイテム補正
				// bit0-5: メトロノーム1-6回目、bit6: 命の珠、bit7: 半減実、bit8: タイプ強化アイテム、bit9: ノーマルジュエル
				// bit10: 達人の帯、

	// 特性ビット定義
	static constexpr int ABILITY_SNIPER = 1; // スナイパー

	// アイテムビット定義
	static constexpr int ITEM_METRONOME = 0x3F; // 下位6bitを使う（6で合ってたっけ？）
	static constexpr int ITEM_LIFEORB = 0x40; // 命の珠
};

class CCalcDamage {
public:
	CCalcDamage( CDatabase *db )
	{
		m_pDatabase = db;
		CRecordset rs( db );

		try {
			// コンストラクタで技データベースを全部読み出すせいで起動が遅い…ｗ
			// ポケモンを入力されてから、必要な技だけ読めば良いんだよね、ホントは…。
			CString strSQL;
			strSQL.Format( _T( "SELECT * FROM move" ) );
			auto res = rs.Open( CRecordset::forwardOnly, strSQL );
			CODBCFieldInfo fi;
			int nFields = rs.GetODBCFieldCount();
			std::vector<CDBVariant> var( nFields );
			while ( rs.IsEOF() == FALSE )
			{
				for ( int i = 0; i < nFields; ++i )
				{
					rs.GetFieldValue( i, var[i] );
				}

				// var[0] : ID		var[1] : 技名
				// var[2] : タイプ	var[3] : 分類
				// var[4] : 威力	var[5] : 命中
				// var[6] : PP		var[7] : 接触判定
				// var[8] : 説明
				m_moveDB[*var[1].m_pstring] = PokeMove( *var[1].m_pstring, *var[2].m_pstring, PokeMove::getCategory( *var[3].m_pstring ),
											   var[4].m_lVal, var[5].m_lVal, var[7].m_boolVal );

				rs.MoveNext();
			}

			rs.Close();
		}
		catch ( CDBException &e ) {
			TCHAR msg[1024];
			e.GetErrorMessage( msg, sizeof( msg ) );
			MessageBox( nullptr, msg, _T( "error" ), MB_ICONERROR );
		}
	}

	int correctPower( CString name, CBattleSettings option ) {
		// 技の威力が変わる場合に補正する処理
		int power = m_moveDB[name].m_power;
	}

	std::map<CString, std::vector<int>> calc( PokemonData atk, PokemonData def, CBattleSettings option ) {
		// 攻撃側が覚える全ての攻撃技でダメージ計算する
		// 戻り値は、「技名：ダメージパターン(乱数と急所により全32パターン)」を覚える技全てで計算した結果
		// ただし、変化技は無視する
		std::map<CString, std::vector<int>> result;
		for ( auto &&atkmove : atk.m_move )
		{
			if ( ( m_moveDB[atkmove].m_category & 0x3 ) == 0 )
			{
				continue; // 変化技、あるいはデータベースに登録されていない技は処理しない
			}
			if ( result[atkmove].size() > 0 )
			{
				// この技のダメージは計算済みなのでスキップ
				continue;
			}

			// ダメージ計算式↓
			//  (((レベル×2/5+2)×威力×A/D)/50+2)×範囲補正×おやこあい補正×天気補正×急所補正×乱数補正×タイプ一致補正×相性補正×やけど補正×M×Mprotect
			// A = 攻撃側の攻撃(物理) or 特攻(特殊)
			// D = 防御側の防御(物理) or 特防(特殊)
			// かっこ内は計算するたびに小数点以下を切り捨て。範囲補正から急所補正までは各計算の後、小数点以下を逐一五捨五超入する。乱数補正計算後は切り捨てる。タイプ一致補正計算後は五捨五超入する。相性補正計算後は切り捨てる。やけど補正計算後は五捨五超入する。M計算後は五捨五超入する。Mprotect計算後は五捨五超入する。

			// M = 壁補正×ブレインフォース補正×スナイパー補正×いろめがね補正×もふもふほのお補正×Mhalf×Mfilter×フレンドガード補正×たつじんのおび補正×メトロノーム補正×いのちのたま補正×半減の実補正×Mtwice
			// Mの各補正値の計算では、小数点以下を逐一四捨五入する。
			// Mhalf = ダメージ半減特性による補正(0.5倍): こおりのりんぷん、パンクロック、ファントムガード、マルチスケイル、もふもふ直接
			// Mfilter = 効果バツグンのダメージを軽減する特性による補正(0.75倍): ハードロック、フィルター、プリズムアーマー
			// MTwice = 穴を掘る中の地震/マグニチュード、ダイビング中の波乗り、小さくなるへのふみつけ等 -> データベースに入れた方が良いかも
			// MProtectは現状の第九世代では存在しない（守るに対するZ技等の1/4補正）
			// 乱数補正 = 85 ～ 100の乱数をかけ、その後100で割る
			// 相性補正は全ての相性倍率を出して、掛け算したあと切り捨てる
			// 壁補正は、防御側の場に1匹なら0.5倍、2匹以上出していれば2732/4096倍
			// 特定タイプの火力を上げるアイテム(神秘のしずく等)は、威力を4915/4096倍する

			// サイコショック等の計算が特殊な技は、A/D/M等を独自計算する必要があるので、あとで実装する
			// 4096は12bit固定小数点演算のため（整数で扱うと、1.0＝4096となる）
			std::vector<long long> tmpresult( 32 ); // 急所の有無それぞれについて、乱数による16パターンのダメージを算出する
			long long damage = 4096;
			long long A = 1, D = 1, M = 1;
			long long Mhalf = 1, Mfilter = 1, MTwice = 1;

			/* STEP1. A/Dを決定 */ // --> 要確認！！！　ランク補正ってここのA/Dを直接いじる？
			if ( m_moveDB[atkmove].m_category & PokeMove::PHYSICS_CHECK )
			{
				// 物理技の時は、攻撃側の「攻撃」と防御側の「防御」を使う
				A *= atk.m_status[PokemonData::Attack_Index]; D *= def.m_status[PokemonData::Block_Index];
			}
			if ( m_moveDB[atkmove].m_category & PokeMove::SPECIAL_CHECK )
			{
				// 特殊技の時は、攻撃側の「特攻」と防御側の「特防」を使う
				A *= atk.m_status[PokemonData::Contact_Index]; D *= def.m_status[PokemonData::Diffence_Index];
			}

			// ワンダールームの場合はDを再計算する処理を入れる（防御と特防を入れ替える）
			// サイコショック等の処理もここにいれる？
			// ソーラービームは威力が変わるから、範囲補正より先にそっちかも…？
			// 威力変化系の技は、別途専用関数作って計算した方が良さそう
			// AとDが変わるタイプの威力変化系（フォトンゲイザーとか）はここかなぁ…。

			/* STEP2. 最初の()内を計算 */
			/* STEP2-1. 威力を決定 */
			int power = m_moveDB[atkmove].m_power;
			/* 以下、サイコフィールドでワイドフォースとか、ジャイロボールとか、そういうやつも計算する */
			// ↓これも関数に入れた方が良い？？
			if ( option.m_item & PokemonDataSub::ITEM_TYPE_ENHANCE )
			{
				// タイプ強化アイテムなら威力4915/4096倍
				power *= 4915; power /= 4096;
			}
			if ( ( m_moveDB[atkmove].m_category & PokeMove::PHYSICS_CHECK )
				 && ( option.m_item & PokemonDataSub::ITEM_MUSCLEBAND ) )
			{
				// 物理技でちからのハチマキを持っている時は威力4505/4096倍
				power *= 4505; power /= 4096;
			}
			if ( ( m_moveDB[atkmove].m_category & PokeMove::SPECIAL_CHECK )
				 && ( option.m_item & PokemonDataSub::ITEM_WISEGLASSES ) )
			{
				// 特殊技でものしりメガネを持っている時は威力4505/4096倍
				power *= 4505; power /= 4096;
			}

			/* STEP2-2. A/Dにランク補正を入れるのはここ？ */
			// -> 急所に当たる場合は不利な効果を無視するので、ちょっとめんどいことになるかも…

			/* STEP2-LAST. 計算した威力を使って残りを計算 */
			damage *= ( ( atk.m_Level * 2 ) / 5 ); damage = ( damage / 4096 ) * 4096; damage += 8192;
			damage = damage * ( power * A ) / D; damage = ( damage / 4096 ) * 4096;
			damage /= 50; damage = ( damage / 4096 ) * 4096;
			damage += 8192; damage = ( damage / 4096 ) * 4096;

			/* STEP3. 範囲補正 */
			// m_moveDBからではなくてoptionのダブル補正から拾わなきゃダメ
//			damage *= m_moveDB[atkmove].m_range; damage += 2047; damage /= 4096; damage *= 4096;

			/* STEP4. 親子愛補正は第九世代には存在しない */

			/* STEP5. 天気補正 */
			if ( option.m_weather == 1 )
			{
				// 晴れの時、炎技は1.5倍、水技は0.5倍
				if ( m_moveDB[atkmove].m_type == _T( "ほのお" ) )
				{
					damage *= ( 4096 + 2048 );
					damage += 2047;
					damage /= 4096;
				}
				else if ( m_moveDB[atkmove].m_type == _T( "みず" ) )
				{
					damage *= 2048;
					damage += 2047;
					damage /= 4096;
				}
			} else if ( option.m_weather == 2 )
			{
				// 雨の時、炎技は0.5倍、水技は1.5倍
				// 晴れの時、炎技は1.5倍、水技は0.5倍
				if ( m_moveDB[atkmove].m_type == _T( "みず" ) )
				{
					damage *= ( 4096 + 2048 );
					damage += 2047;
					damage /= 4096;
				}
				else if ( m_moveDB[atkmove].m_type == _T( "ほのお" ) )
				{
					damage *= 2048;
					damage += 2047;
					damage /= 4096;
				}
			}

			/* STEP6. 急所補正 */
			long long damage_critical = damage * ( 2048 + 4096 ) / 4096;
			damage_critical += 2047; damage_critical /= 4096; damage_critical *= 4096;

			/* STEP7. 乱数補正 */
			for ( int i = 0; i < 16; ++i )
			{
				tmpresult[i] = damage * ( 85 + i ); tmpresult[i] /= 100; tmpresult[i] /= 4096; tmpresult[i] *= 4096;
				tmpresult[i + 16] = damage_critical * ( 85 + i ); tmpresult[i + 16] /= 100; tmpresult[i + 16] /= 4096; tmpresult[i + 16] *= 4096;
			}

			/* STEP8. タイプ一致補正 */
			for ( auto &&type : atk.m_type )
			{
				if ( type == m_moveDB[atkmove].m_type )
				{
					for ( int i = 0; i < 32; ++i )
					{
						tmpresult[i] *= ( 4096 + 2048 );
						tmpresult[i] /= 4096;
						tmpresult[i] += 2047;
						tmpresult[i] /= 4096; tmpresult[i] *= 4096;
					}
				}
			}

			/* STEP9. 相性補正 */
			double typecomp_res = 1.0;
			for ( auto &&type : def.m_type )
			{
				typecomp_res *= m_typecomp.check( m_moveDB[atkmove].m_type, type );
			}
			for ( int i = 0; i < 32; ++i ) // STEP毎に32回のループ書くの微妙なんだけどね…
			{
				tmpresult[i] *= typecomp_res;
				tmpresult[i] /= 4096;
				tmpresult[i] *= 4096;
			}

			/* STEP10. 火傷補正 */
			for ( int i = 0; i < 32; ++i )
			{
				if ( option.m_isBurned )
				{
					tmpresult[i] *= 2048;
					tmpresult[i] += 2047;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11. Mを計算する */ // -> Mを計算する別関数を作った方が良い気がする。以下Mhalf等も同様。
			// 今更だけど、型破りを考慮してない…
			// -> 型破りフラグがONなら、残りの特性系ビットを全部OFFにすれば良いような気もする
			/* STEP11-1. 壁補正 */
			if ( m_moveDB[atkmove].m_category & option.m_barrier )
			{
				// 分類と壁の有無が一致
				// →テラバーストとかフォトンゲイザーが困るか…
				//   bitには空きがあるし、専用bit入れるか。テラバースト物理、テラバースト特殊(壁)、みたいな
				for ( int i = 0; i < 16; ++i ) // 急所に当たったら壁は無視されるので、前半16パターンだけ補正する
				{
					if ( option.m_range )
					{
						// ダブル補正がある時は2732/4096倍
						tmpresult[i] *= 2732;
					} else
					{
						// シングルなら0.5倍
						tmpresult[i] *= 2048;
					}
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-2. ブレインフォース補正は第九世代には存在しない */

			/* STEP11-3. スナイパー補正 */
			if ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
			{
				for ( int i = 16; i < 32; ++i ) // 急所に当たった時、更に威力が1.5倍
				{
					tmpresult[i] *= ( 2048 + 4096 );
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-4. いろめがね補正 */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( typecomp_res < 1.0 ) )
			{
				for ( int i = 0; i < 32; ++i )
				{
					// 効果が今ひとつ以下の場合はダメージ2倍
					tmpresult[i] *= 8192;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-5. もふもふ(炎技被弾)補正 */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( m_moveDB[atkmove].m_type == _T( "ほのお" ) ) )
			{
				for ( int i = 0; i < 32; ++i )
				{
					// 特性もふもふで炎技を被弾した場合はダメージ2倍
					// これは防御側の特性を参照するので実装に注意！！！！！
					tmpresult[i] *= 8192;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-6. Mhalf補正 */
			/* STEP11-6-1. 氷の鱗粉補正 */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( m_moveDB[atkmove].m_category & PokeMove::SPECIAL_CHECK ) )
			{
				// 氷の鱗粉で特殊技を受ける時はダメージ半減
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= 2048;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-6-2. ファントムガード、マルチスケイル補正 */
			if ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
			{
				// ファントムガード、マルチスケイルが発動する時はダメージ半減
				// -> ツールとしてはチェックボックスのON/OFFで切り替えるのでHP判定はしない
				// ファントムガードは、シャドーレイやメテオドライブの特性貫通効果や型破りを無視して半減するので、
				// 別々に計算した方が良いかも
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= 2048;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-6-3. パンクロック補正 */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( m_moveDB[atkmove].m_direct ) ) // 音属性入れないとダメ
			{
				// 音の技を受ける時はダメージ半減
				// 逆に音技を使う時は[威力]上昇？ -> 威力計算の時にやる？
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= 2048;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-6-4. もふもふ(接触技)補正 */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( m_moveDB[atkmove].m_direct ) )
			{
				// 接触技を受ける時はダメージ半減
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= 2048;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-7. Mfilter補正 */
			/* STEP11-7-1. ハードロック/フィルター補正 */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( typecomp_res > 1.0 ) )
			{
				// ハードロック/フィルターが発動する時はダメージ0.75倍
				// プリズムアーマーは、シャドーレイやメテオドライブの特性貫通を無視して軽減するので、別々に計算
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= ( 2048 + 1024 );
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}
			/* STEP11-7-2. プリズムアーマー補正 */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( typecomp_res > 1.0 ) )
			{
				// プリズムアーマーが発動する時はダメージ0.75倍
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= ( 2048 + 1024 );
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-8. フレンドガード補正 */
			if ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
			{
				// フレンドガードが発動する時はダメージ0.75倍
				// -> ツールとしてはチェックボックスのON/OFFで切り替える
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= ( 2048 + 1024 );
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-9. 達人の帯補正 */
			if ( ( option.m_item & CBattleSettings::ABILITY_SNIPER )
				&& ( typecomp_res > 1.0 ) )
			{
				// 達人の帯が発動する時はダメージ1.2倍 -> 正確にはいくつ？4915？4916？
			}

			/* STEP11-10. メトロノーム補正 */
			if ( option.m_item & CBattleSettings::ITEM_METRONOME )
			{
				// メトロノームで同じ技をN回使ったらダメージ上昇
				std::vector<int> gain = { 4096, 4096, 4096, 4096, 4096, 8192 };
				for ( int i = 0; i < 6; ++i )
				{
					if ( option.m_item & ( 1 << i ) )
					{
						// iビット目がONならgain[i]倍になる
						tmpresult[i] *= gain[i];
						tmpresult[i] += 2048;
						tmpresult[i] /= 4096;
						break;
					}
				}
			}

			/* STEP11-11. 命の珠補正 */
			if ( option.m_item & CBattleSettings::ITEM_LIFEORB )
			{
				// 命の珠ならダメージ1.3倍 -> 正確には5324/4096倍？
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= 5324;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-12. 半減実補正 */
			if ( ( option.m_item & CBattleSettings::ITEM_LIFEORB )
				&& ( typecomp_res > 1.0 ) )
			{
				// 弱点半減の実ならダメージ0.5倍 -> これは正確に2048/4096？
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= 2048;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-13. Mtwice補正 */
			if ( option.m_twice )
			{
				// 特定条件下でダメージ2倍の技を使用した
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= 8192;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP12. Mprotect補正は第九世代には存在しない */

			/* STEP13. 計算結果を4096で割る */
			// ここまでlong longで計算したのでint型に変換(別に全部long longにしても良いと思うんだけど…)
			std::vector<int> tmpres2( 32 );
			for ( int i = 0; i < 32; ++i )
			{
				tmpres2[i] = tmpresult[i] / 4096;
			}

			/* LAST STEP. 計算結果を結果配列に突っ込む */
			// 同じ技を重複してデータベースに登録してる問題をこっち側で解決する
			result[atkmove] = tmpres2;
		}

		// 与えるダメージが大きい技から順番に並べたいね…
		// たぶん、各要素の先頭の値でソートしちゃって良いと思うけど、std::mapのままだとソートできないか…
		/*
		sort( result.begin(), result.end(),
			[]( std::pair<CString, std::vector<int>> x, std::pair<CString, std::vector<int>> y ) {
			return ( x.second[0] > y.second[0] );
		} );
		*/
		return ( result );
	}

private:
	CDatabase *m_pDatabase;
	std::map<CString, PokeMove> m_moveDB;

	TypeCompatibility m_typecomp;
};

