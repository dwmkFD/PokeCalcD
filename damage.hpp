#pragma once

/* ダメージ計算メインヘッダ */
#include <Windows.h>
#include <afxdb.h>

#include <vector>
#include <map>
#include <memory>

#include "pokemove.hpp"
#include "pokemon.hpp"

class CCalcDamage{
public:
	CCalcDamage( CDatabase *db )
	{
		m_pDatabase = db;
		CRecordset rs( db );

		try {
			CString strSQL;
			strSQL.Format( _T( "SELECT * FROM move" ) );
			auto res = rs.Open( CRecordset::forwardOnly, strSQL );
			CODBCFieldInfo fi;
			short nFields = rs.GetODBCFieldCount();
			std::vector<CDBVariant> var( nFields );
			while ( rs.IsEOF() != FALSE )
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
				m_move.emplace_back( PokeMove( *var[1].m_pstring, *var[2].m_pstring, PokeMove::getCategory( *var[3].m_pstring ),
											   var[4].m_lVal, var[5].m_lVal, var[7].m_boolVal ) );

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

	std::vector<std::pair<CString, std::vector<int>>> calc( PokemonData atk, PokemonData def ) {
		// 攻撃側が覚える全ての攻撃技でダメージ計算する
		// 戻り値は、「技名：ダメージパターン(乱数と急所により全32パターン)」を覚える技全てで計算した結果
		for ( auto &&atkmove : atk.m_move )
		{
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
		}
	}

private:
	CDatabase *m_pDatabase;
	std::vector<PokeMove> m_move;
};

