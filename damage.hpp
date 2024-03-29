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
	CBattleSettings() {
		m_weather = 0;
		m_isBurned = false;
		m_barrier = 0;
		m_twice = false;
		m_battleStatus = 0;
		m_fieldStatus = 0;
		m_weekHit = false;
	}

	// 天気、フィールド、壁、手助け…などの状態を管理したい
	// -> メインダイアログのメンバ変数も、これにしたいね
	int m_weather; // 天気（0: なし、1: 晴れ、2: 雨、3: 砂、4: 雪）
	bool m_isBurned; // 火傷
	int m_barrier; // bit0: リフレクター、 bit1: 光の壁
	bool m_twice; // 特定条件下で威力2倍判定 // -> これは攻撃技側にデータを持たせるべきだと思われる
	unsigned int m_range; // ダブル補正（0: なし、1: あり）
	unsigned int m_battleStatus; // 場の状態
	unsigned int m_fieldStatus;  // フィールド

	// その他特殊な判定
	bool m_weekHit; // 弱点をつくと威力が1.33倍になる時
	void specialCheckReset() {
		// 特定の技でだけ立てるフラグをリセットする処理
		m_weekHit = false;
	}

	// 場の状態ビット定義 ↑ワンダールーム別変数になってるけど、あとで修正する
	static constexpr unsigned int BATTLE_STATUS_GRAVITY      = 0x01; // 重力
	static constexpr unsigned int BATTLE_STATUS_WONDERROOM   = 0x02; // ワンダールーム
	static constexpr unsigned int BATTLE_STATUS_PLASMASHOWER = 0x04; // プラズマシャワー
	static constexpr unsigned int BATTLE_STATUS_FAIRYAURA    = 0x08; // フェアリーオーラ
	static constexpr unsigned int BATTLE_STATUS_DARKAURA     = 0x10; // ダークオーラ
	static constexpr unsigned int BATTLE_STATUS_AURABREAK    = 0x20; // オーラブレイク

	// フィールド定義ビット
	static constexpr unsigned int BATTLE_FIELD_ELECTRIC = 0x1; // エレキフィールド
	static constexpr unsigned int BATTLE_FIELD_GRASSY   = 0x2; // グラスフィールド
	static constexpr unsigned int BATTLE_FIELD_MISTY    = 0x4; // ミストフィールド
	static constexpr unsigned int BATTLE_FIELD_PSYCHIC  = 0x8; // サイコフィールド

	// ↓PokemonData側に移動させたんだけど、コンパイル通らなくなるので、修正完了まではこのままで
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

				// var[0] : ID			var[1] : 技名		var[2] : タイプ		var[3] : 分類
				// var[4] : 威力		var[5] : 命中		var[6] : PP			var[7] : 接触判定
				// var[8] : かみつき技	var[9] : パンチ技	var[10] : 急所技	var[11] : 波動技
				// var[12] : 小さくなる	var[13] : 音		var[14] : 範囲技	var[15] : 説明
				m_moveDB[*var[1].m_pstring] = PokeMove( *var[1].m_pstring, *var[2].m_pstring, PokeMove::getCategory( *var[3].m_pstring ),
											   var[4].m_lVal, var[5].m_lVal, var[7].m_boolVal, var[8].m_boolVal, var[9].m_boolVal,
											   var[10].m_iVal, var[11].m_boolVal, var[12].m_boolVal, var[13].m_boolVal, var[14].m_boolVal );

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

	int correctPower( const CString name, const PokemonData &atk, const PokemonData &def, CBattleSettings &option ) {
		// 技の威力が変わる場合に補正する処理
		int power = m_moveDB[name].m_power;

		// サイコフィールドでワイドフォースを撃つ場合は威力2倍かつ全体技
		// -> 技データベースの方を書き換えると面倒なのをどうするか…
		//  -> ここでは威力だけ補正して、ダブル判定etcは本体の関数でやる(たぶん)
		if ( option.m_fieldStatus & CBattleSettings::BATTLE_FIELD_PSYCHIC )
		{
			if ( name == _T( "ワイドフォース" ) )
			{
				return ( power * 2 );
			}
		}

		// エレキボール、ジャイロボールは素早さを比較して威力決定
		if ( name == _T( "エレキボール" ) )
		{
			int atkS = atk.m_status[PokemonData::Speed_Index];
			int defS = def.m_status[PokemonData::Speed_Index];
		}
		else if ( name == _T( "ジャイロボール" ) )
		{
			int atkS = atk.m_status[PokemonData::Speed_Index];
			int defS = def.m_status[PokemonData::Speed_Index];
		}

		// サイコブレイドはエレキフィールドで威力1.5倍
		if ( option.m_fieldStatus & CBattleSettings::BATTLE_FIELD_ELECTRIC )
		{
			if ( name == _T( "サイコブレイド" ) )
			{
			}
		}

		// イナズマドライブ/アクセルブレイクは弱点をつくと威力1.33倍
		// -> ここで弱点計算するのは面倒なので、「弱点をついた」フラグをONにするのが良いかも
		if ( name == _T( "アクセルブレイク" ) || name == _T( "イナズマドライブ" ) )
		{
			option.m_weekHit = true;
		}

		// 特性「テクニシャン」で威力60以下の技は威力1.5倍
		if ( atk.m_option.m_ability & PokemonAbility::ABILITY_TECHNICIAN )
		{
			if ( power <= 60 )
			{
				power *= ( 2048 + 4096 );
				power += 0; // 切り捨てだった気がする？
				power /= 4096;
			}
		}

		// ミストフィールドでドラゴン技を使うと威力半減（ダメージ半減？どっち？）
		if ( option.m_fieldStatus & CBattleSettings::BATTLE_FIELD_MISTY )
		{
			if ( m_moveDB[name].m_type == _T( "ドラゴン" ) )
			{
				power *= 2048;
				power /= 4096;
			}
		}

		// ヒートスタンプ、けたぐり、ヘビーボンバーは体重差によって威力決定
		if ( name == _T( "ヒートスタンプ" ) || name == _T( "けたぐり" ) || name == _T( "ヘビーボンバー" ) )
		{
		}

		// 無天候と晴れ以外の天候でのソーラービーム/ブレードは威力半減
		if ( name == _T( "ソーラービーム" ) || name == _T( "ソーラーブレード" ) )
		{
			if ( ( option.m_weather != 0 ) && ( option.m_weather != 1 ) )
			{
				power *= 2048;
				power /= 4096;
			}
		}

		// おはかまいりは仲間が倒された回数で威力変動(専用の入力欄が必要 or おはかまいり(0-10くらいまで別々の技として計算しても良いけど))
		// 同、ふんどのこぶしは攻撃を受けた回数で威力変動

		// テラスタイプが有効で、テラスタイプ一致であり、威力が60以下の技は威力を60に上げる
	}

	double calcCriticalProbability( const CString &name, const PokemonData &atk, const PokemonData &def ) {
		// option条件下で急所に当たる確率を計算する
		// -> 急所に当たりやすい技、急所ランク(作ってない気がする…)、持ち物などを考慮 -> option はPokemonData.opt の方にしないとダメだと思うけど、暫定で
		double result = 1.0;
		int rank = 0;
		rank += m_moveDB[name].m_critical; // 急所に当たりやすい技なら、急所ランクを上げる(確定急所技は+3、それ以外は+1）

		if ( atk.m_option.m_ability & PokemonAbility::ABILITY_SUPERLUCK ) // 攻撃側の特性が強運
		{
			++rank;
		}
		if ( ( atk.m_option.m_ability & PokemonAbility::ABILITY_MERCILESS ) // 攻撃側の特性が人でなしで、
			&& ( def.m_option.m_conditionAbnormaly & PokemonDataSub::CONDITION_POISON ) ) // 防御側が毒/猛毒状態
		{
			rank += 3;
		}
		if ( atk.m_option.m_item & PokemonDataSub::ITEM_SCOPELENS ) // ピントレンズ/するどいツメを持っている
		{
			++rank;
		}

		// rank >= 3 なら確定急所
		if ( rank >= 2 )
		{
			result /= 2.0;
		}
		else if ( rank >= 1 )
		{
			result /= 8.0;
		}
		else
		{
			result /= 24.0;
		}

		return ( result );
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

			// ↓↓↓ダメージ計算式にフィールドの補正が入ってないけど、どこで補正されるんだ…？？？

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
			// 乱数補正 = 85 〜 100の乱数をかけ、その後100で割る
			// 相性補正は全ての相性倍率を出して、掛け算したあと切り捨てる
			// 壁補正は、防御側の場に1匹なら0.5倍、2匹以上出していれば2732/4096倍
			// 特定タイプの火力を上げるアイテム(神秘のしずく等)は、威力を4915/4096倍する

			// サイコショック等の計算が特殊な技は、A/D/M等を独自計算する必要があるので、あとで実装する
			// 4096は12bit固定小数点演算のため（整数で扱うと、1.0＝4096となる）
			std::vector<long long> tmpresult( 32 ); // 急所の有無それぞれについて、乱数による16パターンのダメージを算出する
			long long damage = 4096;
			long long A = 1, D = 1, M = 1;
			long long Mhalf = 1, Mfilter = 1, MTwice = 1;

			/* STEP1. A/Dを決定 */ // --> 要確認！！！　ランク補正ってここのA/Dを直接いじる？ -> もう一個、こだわり系はステータス1.5倍だよね？ここ？？
			auto calcAD = []( long long &A, long long &D, const PokemonData &atk, const PokemonData &def, const int category ) {
				if ( category & PokeMove::PHYSICS_CHECK )
				{
					// 物理技の時は、攻撃側の「攻撃」と防御側の「防御」を使う
					A *= atk.m_status[PokemonData::Attack_Index]; D *= def.m_status[PokemonData::Block_Index];
					if ( ( atk.m_option.m_ability & PokemonAbility::ABILITY_HUGEPOWER )
						 || ( atk.m_option.m_ability & PokemonAbility::ABILITY_PUREPOWER )
//						 || ( atk.m_option.m_ability & PokemonAbility::ABILITY_XXXXX ) // 張り込みを入れるべきか否か… でも張り込みは特攻も上がるらしいから別枠か
						 )
					{
						A *= 2; // 力持ち or ヨガパワーなら攻撃を2倍にする
					}
					if ( atk.m_option.m_item & PokemonDataSub::ITEM_CHOICEBAND )
					{
						// 持ち物がこだわりハチマキなら攻撃を1.5倍(四捨五入)する
						A *= 6144;
						A += 2048;
						A /= 4096;
					}
				}
				if ( category & PokeMove::SPECIAL_CHECK )
				{
					// 特殊技の時は、攻撃側の「特攻」と防御側の「特防」を使う
					A *= atk.m_status[PokemonData::Contact_Index]; D *= def.m_status[PokemonData::Diffence_Index];
					if ( atk.m_option.m_item & PokemonDataSub::ITEM_CHOICESPECS )
					{
						// 持ち物がこだわりメガネなら特攻を1.5倍(四捨五入)する
						A *= 6144;
						A += 2048;
						A /= 4096;
					}
				}
			};
			calcAD( A, D, atk, def, m_moveDB[atkmove].m_category );

			// STEP1-1. サイコショックとサイコブレイクは攻撃側の特攻、防御側の防御を使う
			// categoryを物理・特殊・変化だけじゃなくて、物理(特殊計算)、特殊(物理計算)みたいなものも入れたら良いかも…
			if ( ( atkmove == _T( "サイコショック" ) ) || ( atkmove == _T( "サイコブレイク" ) ) )
			{
				A = atk.m_status[PokemonData::Contact_Index]; D = def.m_status[PokemonData::Block_Index];
			}

			// STEP1-2. フォトンゲイザーとシェルアームズはここで補正？
			// 攻撃・特攻と防御・特防を比較して、一番ダメージが大きくなるようにA/Dを決めるんだっけ？

			// STEP1-3. ワンダールームの場合はDを再計算する処理を入れる（防御と特防を入れ替える）
			if ( option.m_battleStatus & CBattleSettings::BATTLE_STATUS_WONDERROOM )
			{
				long long A_dummy = 1;
				D = 1; // Aは変わらないのでダミーで計算して結果は捨て、Dはここでの結果を採用する
				calcAD( A_dummy, D, atk, def, m_moveDB[atkmove].m_category ^ 0x3 ); // 物理/特殊の判定を入れ替えてDだけ再計算する
			}

			// ソーラービームは威力が変わるから、範囲補正より先にそっちかも…？
			// 威力変化系の技は、別途専用関数作って計算した方が良さそう

			/* STEP2. 最初の()内を計算 */
			/* STEP2-1. 威力を決定 */
			int power = m_moveDB[atkmove].m_power;
			/* 以下、サイコフィールドでワイドフォースとか、ジャイロボールとか、そういうやつも計算する */
			// ↓これも関数に入れた方が良い？？
			if ( atk.m_option.m_item & PokemonDataSub::ITEM_TYPE_ENHANCE )
			{
				// タイプ強化アイテムなら威力4915/4096倍
				power *= 4915; power /= 4096;
			}
			if ( ( m_moveDB[atkmove].m_category & PokeMove::PHYSICS_CHECK )
				 && ( atk.m_option.m_item & PokemonDataSub::ITEM_MUSCLEBAND ) )
			{
				// 物理技でちからのハチマキを持っている時は威力4505/4096倍
				power *= 4505; power /= 4096;
			}
			if ( ( m_moveDB[atkmove].m_category & PokeMove::SPECIAL_CHECK )
				 && ( atk.m_option.m_item & PokemonDataSub::ITEM_WISEGLASSES ) )
			{
				// 特殊技でものしりメガネを持っている時は威力4505/4096倍
				power *= 4505; power /= 4096;
			}

			/* STEP2-2. A/Dにランク補正を入れるのはここ？ */
			int rank1 = 2, rank2 = 2;
			int A_critical = A, D_critical = D;
			if ( atk.m_option.m_rank > 0 )
			{
				rank1 += atk.m_option.m_rank;
			}
			else if ( atk.m_option.m_rank < 0 )
			{
				rank2 += atk.m_option.m_rank;
			}
			A = A * rank1; A = A / rank2;
			if ( (double)rank1 / rank2 > 1.0 )
			{
				A_critical = A; // 急所に当たる場合、有利な効果(攻撃側の攻撃ランク上昇)だけ残す
			}

			if ( def.m_option.m_rank > 0 )
			{
				rank1 += def.m_option.m_rank;
			}
			else if ( def.m_option.m_rank < 0 )
			{
				rank2 += def.m_option.m_rank;
			}
			D = D * rank1; D = D / rank2;
			if ( (double)rank1 / rank2 < 1.0 )
			{
				D_critical = D; // 急所に当たる場合、有利(防御側の防御ランク低下)な効果だけ残す
			}

			/* STEP2-3. ランク補正とは別のステータス上昇(総大将、クォークチャージ、古代活性、ハドロンエンジン、ヒヒイロの鼓動) */
			// -> これはPokemonDataの数値でもらう仕様にしたんだっけ？

			/* STEP2-LAST. 計算した威力を使って残りを計算 */
			auto damage_base = [&]( const long long a, const long long d, const int p, long long &dmg ) {
				dmg = dmg * ( p * a ) / d; dmg = ( dmg / 4096 ) * 4096;
				dmg /= 50; dmg = ( dmg / 4096 ) * 4096;
				dmg += 8192; dmg = ( dmg / 4096 ) * 4096;
				/* STEP3. 範囲補正 */
				// 切り捨て、四捨五入、五捨五超入は関数化したいね
				if ( option.m_range && m_moveDB[atkmove].m_range )
				{
					// ダブル補正があり、範囲技でもある場合、ダメージを75％にする
					dmg *= ( 2048 + 1024 );
					dmg /= 4096;
					dmg += 2047;
					dmg /= 4096; dmg *= 4096;
				}
				else if ( 0 ) // サイコフィールドでワイドフォースを使った場合は m_moveDB[atkmove].m_rangeはfalseだがダブル補正する必要あり
				{
				}

				/* STEP4. 親子愛補正は第九世代には存在しない */

				/* STEP5. 天気補正 */
				if ( option.m_weather == 1 )
				{
					// 晴れの時、炎技は1.5倍、水技は0.5倍
					if ( m_moveDB[atkmove].m_type == _T( "ほのお" ) )
					{
						dmg *= ( 4096 + 2048 );
						dmg += 2047;
						dmg /= 4096;
					}
					else if ( m_moveDB[atkmove].m_type == _T( "みず" ) ) // -> ウネルミナモの専用技は晴れでも威力1.5倍だった気がする -> 威力？ダメージ？ここで補正して良い？
					{
						if ( atkmove == _T( "ハイドロスチーム" ) )
						{
							dmg *= ( 4096 + 2048 );
							dmg += 2047;
							dmg /= 4096;
						}
						else
						{
							dmg *= 2048;
							dmg += 2047;
							dmg /= 4096;
						}
					}
				}
				else if ( option.m_weather == 2 )
				{
					// 雨の時、炎技は0.5倍、水技は1.5倍
					// 晴れの時、炎技は1.5倍、水技は0.5倍
					if ( m_moveDB[atkmove].m_type == _T( "みず" ) )
					{
						dmg *= ( 4096 + 2048 );
						dmg += 2047;
						dmg /= 4096;
					}
					else if ( m_moveDB[atkmove].m_type == _T( "ほのお" ) )
					{
						dmg *= 2048;
						dmg += 2047;
						dmg /= 4096;
					}
				}
			};

			// -> 急所に当たる場合は不利な効果を無視するので、別々に計算する
			long long damage_critical;
			damage *= ( ( atk.m_Level * 2 ) / 5 ); damage = ( damage / 4096 ) * 4096; damage += 8192;
			damage_critical = damage;
			damage_base( A, D, power, damage );
			damage_base( A_critical, D_critical, power, damage_critical );

			/* STEP6. 急所補正 */
			damage_critical = damage_critical * ( 2048 + 4096 ) / 4096;
			damage_critical += 2047; damage_critical /= 4096; damage_critical *= 4096;

			/* STEP7. 乱数補正 */
			for ( int i = 0; i < 16; ++i )
			{
				tmpresult[i] = damage * ( 85 + i ); tmpresult[i] /= 100; tmpresult[i] /= 4096; tmpresult[i] *= 4096;
				tmpresult[i + 16] = damage_critical * ( 85 + i ); tmpresult[i + 16] /= 100; tmpresult[i + 16] /= 4096; tmpresult[i + 16] *= 4096;
			}

			/* STEP8. タイプ一致補正 */
			// -> テラスタイプ一致の計算もここでやる？
			// テラバーストはテラスタルしている場合は必ずタイプ一致(未実装)、テラスタルしていなければノーマルでタイプ一致、ノーマルタイプがノーマルにテラスタルした時は…？
			// そういえば、フライングプレスは「格闘」でタイプ一致判定するんだっけ？(ルチャブル専用技だった気がするから、いずれにせよタイプ一致だが、飛行にテラスタルすると事情が変わる…）
			atk.m_type.emplace_back( atk.m_option.m_teraType ); // テラスタイプも追加して判定する
			long long type_match_attack = 0;
			for ( auto &&type : atk.m_type )
			{
				if ( type == m_moveDB[atkmove].m_type )
				{
					type_match_attack += 2048;
				}
			}

			for ( int i = 0; i < 32; ++i )
			{
				tmpresult[i] *= ( 4096 + type_match_attack ); // タイプ不一致なら1.0倍、タイプ一致なら1.5倍、テラスタイプ一致なら2.0倍になる
				tmpresult[i] /= 4096;
				tmpresult[i] += 2047;
				tmpresult[i] /= 4096; tmpresult[i] *= 4096;
			}
			atk.m_type.pop_back(); // 追加したテラスタイプを一応削除しておく

			/* STEP9. 相性補正 */
			double typecomp_res = 1.0;
			if ( def.m_option.m_teraType.IsEmpty() == FALSE )
			{
				// 防御側にテラスタイプが設定されている場合は、相性はテラスタイプを使って計算する
				typecomp_res *= m_typecomp.check( m_moveDB[atkmove].m_type, def.m_option.m_teraType );
			}
			else
			{
				// テラスタイプ未設定の場合は、本来持つタイプで計算する
				for ( auto &&type : def.m_type )
				{
					typecomp_res *= m_typecomp.check( m_moveDB[atkmove].m_type, type );
				}
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
			if ( m_moveDB[atkmove].m_category & def.m_option.m_barrier )
			{
				// 分類と壁の有無が一致
				// →テラバーストとかフォトンゲイザーが困るか…
				//   bitには空きがあるし、専用bit入れるか。テラバースト物理、テラバースト特殊(壁)、みたいな
				for ( int i = 0; i < 16; ++i ) // 急所に当たったら壁は無視されるので、前半16パターンだけ補正する
				{
					if ( option.m_range )
					{
						// ダブル補正がある時は2732/4096倍
						// これって相手が2体いれば単体攻撃でも補正変わるんだっけ？
						// 相手が1体の時はシングルと同じ扱いだっけ？
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
			if ( atk.m_option.m_ability & PokemonAbility::ABILITY_SNIPER )
			{
				for ( int i = 16; i < 32; ++i ) // 急所に当たった時、更に威力が1.5倍
				{
					tmpresult[i] *= ( 2048 + 4096 );
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-4. いろめがね補正 */
			if ( ( atk.m_option.m_ability & PokemonAbility::ABILITY_TINTLENS )
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
			if ( ( def.m_option.m_ability & PokemonAbility::ABILITY_FLUFFY )
				&& ( m_moveDB[atkmove].m_type == _T( "ほのお" ) ) )
			{
				for ( int i = 0; i < 32; ++i )
				{
					// 特性もふもふで炎技を被弾した場合はダメージ2倍(ただし弱点ではない)
					// これは防御側の特性を参照するので実装に注意！！！！！
					tmpresult[i] *= 8192;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-6. Mhalf補正 */
			/* STEP11-6-1. 氷の鱗粉補正 */
			if ( ( def.m_option.m_ability & PokemonAbility::ABILITY_ICE_SCALES )
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
			if ( def.m_option.m_ability & PokemonAbility::ABILITY_SHADOWSHIELD )
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
			if ( ( def.m_option.m_ability & PokemonAbility::ABILITY_PUNKROCK )
				&& ( m_moveDB[atkmove].m_sound ) ) // 音の技の時
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
			if ( ( def.m_option.m_ability & PokemonAbility::ABILITY_FLUFFY )
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
			if ( ( def.m_option.m_ability & PokemonAbility::ABILITY_FILTER )
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
			if ( ( def.m_option.m_ability & PokemonAbility::ABILITY_PRISMARMOR )
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
			if ( def.m_option.m_ability & PokemonAbility::ABILITY_FRIENDGUARD )
			{
				// フレンドガードが発動する時はダメージ0.75倍
				// -> ツールとしてはチェックボックスのON/OFFで切り替える
				//  -> じゃあ↑この判定じゃダメじゃんｗ
				for ( int i = 0; i < 32; ++i )
				{
					tmpresult[i] *= ( 2048 + 1024 );
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-9. 達人の帯補正 */
			if ( ( atk.m_option.m_item & CBattleSettings::ABILITY_SNIPER )
				&& ( typecomp_res > 1.0 ) )
			{
				// 達人の帯が発動する時はダメージ1.2倍 -> 正確にはいくつ？4915？4916？
			}

			/* STEP11-10. メトロノーム補正 */
			if ( atk.m_option.m_item & CBattleSettings::ITEM_METRONOME )
			{
				// メトロノームで同じ技をN回使ったらダメージ上昇
				std::vector<int> gain = { 4096, 4096, 4096, 4096, 4096, 8192 };
				for ( int i = 0; i < 6; ++i )
				{
					if ( atk.m_option.m_item & ( 1 << i ) )
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
			if ( atk.m_option.m_item & PokemonDataSub::ITEM_LIFEORB )
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
			if ( ( atk.m_option.m_item & PokemonDataSub::ITEM_HALFDAMAGEBERRY )
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
			// -> 守る状態に対するZ技、ダイマックス技など

			/* STEP13. 計算結果を4096で割る */
			// ここまでlong longで計算したのでint型に変換(別に全部long longにしても良いと思うんだけど…)
			std::vector<int> tmpres2( 33 );
			for ( int i = 0; i < 32; ++i )
			{
				tmpres2[i] = tmpresult[i] / 4096;
			}

			/* STEP14. 期待値を計算する */
			double tmp_exp = 0.0;
			for ( int i = 0; i < 16; ++i )
			{
				// 基本ダメージは、計算結果 × 急所に"当たらない"確率 × 技の命中率
				tmp_exp += ( tmpres2[i] / 16.0 ) * ( 1.0 - calcCriticalProbability( atkmove, atk, def ) ) * ( m_moveDB[atkmove].m_accuracy / 100.0 );
			}
			for ( int i = 16; i < 32; ++i )
			{
				// 急所に当たった場合のダメージは、計算結果 × 急所に"当たる"確率 × 技の命中率
				tmp_exp += ( tmpres2[i] / 16.0 ) * calcCriticalProbability( atkmove, atk, def ) * ( m_moveDB[atkmove].m_accuracy / 100.0 );
			}
			tmpres2[32] = (int)tmp_exp;

			/* LAST STEP. 計算結果を結果配列に突っ込む */
			// 同じ技を重複してデータベースに登録してる問題をこっち側で解決する
			result[atkmove] = tmpres2;

			/* LAST STEP2. 後始末 */
			// 特殊な計算をしたフラグをクリアする
			option.specialCheckReset();
		}

		return ( result );
	}

private:
	CDatabase *m_pDatabase;
	std::map<CString, PokeMove> m_moveDB;

	TypeCompatibility m_typecomp;
};

