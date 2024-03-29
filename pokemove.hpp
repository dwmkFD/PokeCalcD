#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "poketype.hpp"

/* 技の定義 */


// [余談]わざは英語版では「move」なのだが、色々と競合しそうなので、PokeMoveにしておいた
class PokeMove {
public:
	PokeMove() = default;

	PokeMove( CString name, CString type, int category, int power, int accuracy, bool direct,
			  bool bite = false, bool punch = false, int critical = 0, bool pulse = false, bool minimize = false, bool sound = false, bool range = false )
	{
		m_name = name; m_type = type; m_category = category; m_power = power;
		m_accuracy = accuracy; m_direct = direct; m_range = range;
		m_bite = bite; m_punch = punch; m_critical = critical; m_pulse = pulse;
		m_minimize = minimize; m_sound = sound;
	}

	void setRange( int range ) { m_range = range; }
	static int getCategory( CString strCategory ) {
		if ( strCategory == _T( "物理" ) ) return ( PHYSICS_CHECK );
		else if ( strCategory == _T( "特殊" ) ) return ( SPECIAL_CHECK );
		else return ( 0 );
	}

	// 技分類チェック
	// -> TODO: テラバーストみたいな元の分類から変わるやつは、専用のビットを作る？（壁側の判定も -> 実数値とランク補正見て壁option切り替えないとね…）
	static constexpr unsigned int PHYSICS_CHECK = 0x1;
	static constexpr unsigned int SPECIAL_CHECK = 0x2;

	CString m_name; // 技名
	CString m_type; // 技のタイプ
	int m_category; // 技の分類（物理 bit0、特殊 bit1、変化技 bit0/1ともにOFF）
	int m_power; // 技の威力
	int m_accuracy; // 技の命中率
	bool m_range; // 範囲技か？
	// 技の範囲はデータベースの方も更新が必要、補正量が変わるわけじゃないし、true/falseで良いと思う（この変数もあとでbool型に直す）
	bool m_direct; // 接触攻撃か否か（鮫肌とかの反撃で落ちるかどうかを計算結果に含むなら＆もふもふ等の判定に）
	bool m_bite; // かみつき技か？
	bool m_punch; // パンチ技か？
	int m_critical; // 急所に当たりやすい技か？
	bool m_pulse; // 波動技か？
	bool m_minimize; // 小さくなるに対して効果がある技か？
	bool m_sound; // 音技か？
};

// タイプ相性
struct TypeCompatibility {
	// 攻撃側(type1)から防御側(type2)への相性計算
	// 戻り値は倍率( 0、1/4、1/2、1、2、4、8）
	// →例えば、ランドロスが森の呪いを受けると氷は8倍になるので、一応8まであり得る
	// 　→と思ったけど、ここではあくまで単タイプとしてしか比較してないから、0〜2までしかないか
	double check( const CString &type1, const CString &type2 ) const {
		return ( m_table[m_typetable.at( type1 )][m_typetable.at( type2 )] );
	}

	TypeCompatibility() {
		// タイプ名を数値に変換するためのテーブル
		PokeType pt;
		m_typetable = pt.getTypeTable();

		// タイプ相性を計算するテーブル
		m_table.assign( 19, std::vector<double>( 19, 1 ) );

		// ノーマル（弱点：なし、半減：いわ・はがね、無効：ゴースト）
		m_table[m_typetable[_T( "ノーマル" )]][m_typetable[_T( "いわ" )]]
			= m_table[m_typetable[_T( "ノーマル" )]][m_typetable[_T( "はがね" )]] = 0.5;
		m_table[m_typetable[_T( "ノーマル" )]][m_typetable[_T( "ゴースト" )]] = 0;

		// ほのお（弱点：くさ・こおり・むし・はがね、半減：みず・いわ・ドラゴン、無効：なし）
		m_table[m_typetable[_T( "ほのお" )]][m_typetable[_T( "くさ" )]]
			= m_table[m_typetable[_T( "ほのお" )]][m_typetable[_T( "こおり" )]]
			= m_table[m_typetable[_T( "ほのお" )]][m_typetable[_T( "むし" )]]
			= m_table[m_typetable[_T( "ほのお" )]][m_typetable[_T( "はがね" )]] = 2;
		m_table[m_typetable[_T( "ほのお" )]][m_typetable[_T( "みず" )]]
			= m_table[m_typetable[_T( "ほのお" )]][m_typetable[_T( "いわ" )]]
			= m_table[m_typetable[_T( "ほのお" )]][m_typetable[_T( "ドラゴン" )]] = 0.5;

		// みず（弱点：ほのお・じめん・いわ、半減：みず・ドラゴン、無効：なし）
		m_table[m_typetable[_T( "みず" )]][m_typetable[_T( "ほのお" )]]
			= m_table[m_typetable[_T( "みず" )]][m_typetable[_T( "じめん" )]]
			= m_table[m_typetable[_T( "みず" )]][m_typetable[_T( "いわ" )]] = 2;
		m_table[m_typetable[_T( "みず" )]][m_typetable[_T( "みず" )]]
			= m_table[m_typetable[_T( "みず" )]][m_typetable[_T( "ドラゴン" )]] = 0.5;

		// でんき（弱点：みず・ひこう、半減：くさ・でんき・ドラゴン、無効：じめん）
		m_table[m_typetable[_T( "でんき" )]][m_typetable[_T( "みず" )]]
			= m_table[m_typetable[_T( "でんき" )]][m_typetable[_T( "ひこう" )]] = 2;
		m_table[m_typetable[_T( "でんき" )]][m_typetable[_T( "くさ" )]]
			= m_table[m_typetable[_T( "でんき" )]][m_typetable[_T( "でんき" )]]
			= m_table[m_typetable[_T( "でんき" )]][m_typetable[_T( "ドラゴン" )]] = 0.5;
		m_table[m_typetable[_T( "でんき" )]][m_typetable[_T( "じめん" )]] = 0;

		// くさ（弱点：みず・じめん・いわ、半減：ほのお・くさ・どく・ひこう・むし・ドラゴン・はがね、無効：なし）
		m_table[m_typetable[_T( "くさ" )]][m_typetable[_T( "みず" )]]
			= m_table[m_typetable[_T( "くさ" )]][m_typetable[_T( "じめん" )]]
			= m_table[m_typetable[_T( "くさ" )]][m_typetable[_T( "いわ" )]] = 2;
		m_table[m_typetable[_T( "くさ" )]][m_typetable[_T( "ほのお" )]]
			= m_table[m_typetable[_T( "くさ" )]][m_typetable[_T( "くさ" )]]
			= m_table[m_typetable[_T( "くさ" )]][m_typetable[_T( "どく" )]]
			= m_table[m_typetable[_T( "くさ" )]][m_typetable[_T( "ひこう" )]]
			= m_table[m_typetable[_T( "くさ" )]][m_typetable[_T( "むし" )]]
			= m_table[m_typetable[_T( "くさ" )]][m_typetable[_T( "ドラゴン" )]]
			= m_table[m_typetable[_T( "くさ" )]][m_typetable[_T( "はがね" )]] = 0.5;

		// こおり（弱点：くさ・じめん・ひこう・ドラゴン、半減：ほのお、みず、こおり、はがね、無効：なし）
		m_table[m_typetable[_T( "こおり" )]][m_typetable[_T( "くさ" )]]
			= m_table[m_typetable[_T( "こおり" )]][m_typetable[_T( "じめん" )]]
			= m_table[m_typetable[_T( "こおり" )]][m_typetable[_T( "ひこう" )]]
			= m_table[m_typetable[_T( "こおり" )]][m_typetable[_T( "ドラゴン" )]] = 2;
		m_table[m_typetable[_T( "こおり" )]][m_typetable[_T( "ほのお" )]]
			= m_table[m_typetable[_T( "こおり" )]][m_typetable[_T( "みず" )]]
			= m_table[m_typetable[_T( "こおり" )]][m_typetable[_T( "こおり" )]]
			= m_table[m_typetable[_T( "こおり" )]][m_typetable[_T( "はがね" )]] = 0.5;

		// かくとう（弱点：ノーマル・こおり・いわ・あく・はがね、半減：どく・ひこう・エスパー・むし・フェアリー、無効：ゴースト）
		m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "ノーマル" )]]
			= m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "こおり" )]]
			= m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "いわ" )]]
			= m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "あく" )]]
			= m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "はがね" )]] = 2;
		m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "どく" )]]
			= m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "ひこう" )]]
			= m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "エスパー" )]]
			= m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "むし" )]]
			= m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "フェアリー" )]] = 0.5;
		m_table[m_typetable[_T( "かくとう" )]][m_typetable[_T( "ゴースト" )]] = 0;

		// どく（弱点：くさ・フェアリー、半減：どく・じめん・いわ・ゴースト、無効：はがね）
		m_table[m_typetable[_T( "どく" )]][m_typetable[_T( "くさ" )]]
			= m_table[m_typetable[_T( "どく" )]][m_typetable[_T( "フェアリー" )]] = 2;
		m_table[m_typetable[_T( "どく" )]][m_typetable[_T( "どく" )]]
			= m_table[m_typetable[_T( "どく" )]][m_typetable[_T( "じめん" )]]
			= m_table[m_typetable[_T( "どく" )]][m_typetable[_T( "いわ" )]]
			= m_table[m_typetable[_T( "どく" )]][m_typetable[_T( "ゴースト" )]] = 0.5;
		m_table[m_typetable[_T( "どく" )]][m_typetable[_T( "はがね" )]] = 0;

		// じめん（弱点：ほのお・でんき・どく・いわ・はがね、半減：くさ・むし、無効：ひこう）
		m_table[m_typetable[_T( "じめん" )]][m_typetable[_T( "ほのお" )]]
			= m_table[m_typetable[_T( "じめん" )]][m_typetable[_T( "でんき" )]]
			= m_table[m_typetable[_T( "じめん" )]][m_typetable[_T( "どく" )]]
			= m_table[m_typetable[_T( "じめん" )]][m_typetable[_T( "いわ" )]]
			= m_table[m_typetable[_T( "じめん" )]][m_typetable[_T( "はがね" )]] = 2;
		m_table[m_typetable[_T( "じめん" )]][m_typetable[_T( "くさ" )]]
			= m_table[m_typetable[_T( "じめん" )]][m_typetable[_T( "むし" )]] = 0.5;
		m_table[m_typetable[_T( "じめん" )]][m_typetable[_T( "ひこう" )]] = 0;

		// ひこう（弱点：くさ・かくとう・むし、半減：いわ・はがね、無効：なし）
		m_table[m_typetable[_T( "ひこう" )]][m_typetable[_T( "くさ" )]]
			= m_table[m_typetable[_T( "ひこう" )]][m_typetable[_T( "かくとう" )]]
			= m_table[m_typetable[_T( "ひこう" )]][m_typetable[_T( "むし" )]] = 2;
		m_table[m_typetable[_T( "ひこう" )]][m_typetable[_T( "いわ" )]]
			= m_table[m_typetable[_T( "ひこう" )]][m_typetable[_T( "はがね" )]] = 0.5;

		// エスパー（弱点：かくとう・どく、半減：エスパー・はがね、無効：あく）
		m_table[m_typetable[_T( "エスパー" )]][m_typetable[_T( "かくとう" )]]
			= m_table[m_typetable[_T( "エスパー" )]][m_typetable[_T( "どく" )]] = 2;
		m_table[m_typetable[_T( "エスパー" )]][m_typetable[_T( "エスパー" )]]
			= m_table[m_typetable[_T( "エスパー" )]][m_typetable[_T( "はがね" )]] = 0.5;
		m_table[m_typetable[_T( "エスパー" )]][m_typetable[_T( "あく" )]] = 0;

		// むし（弱点：くさ・エスパー・あく、半減：ほのお・かくとう・どく・ひこう・ゴースト・はがね・フェアリー、無効：なし）
		m_table[m_typetable[_T( "むし" )]][m_typetable[_T( "くさ" )]]
			= m_table[m_typetable[_T( "むし" )]][m_typetable[_T( "エスパー" )]]
			= m_table[m_typetable[_T( "むし" )]][m_typetable[_T( "あく" )]] = 2;
		m_table[m_typetable[_T( "むし" )]][m_typetable[_T( "ほのお" )]]
			= m_table[m_typetable[_T( "むし" )]][m_typetable[_T( "かくとう" )]]
			= m_table[m_typetable[_T( "むし" )]][m_typetable[_T( "どく" )]]
			= m_table[m_typetable[_T( "むし" )]][m_typetable[_T( "ひこう" )]]
			= m_table[m_typetable[_T( "むし" )]][m_typetable[_T( "ゴースト" )]]
			= m_table[m_typetable[_T( "むし" )]][m_typetable[_T( "はがね" )]]
			= m_table[m_typetable[_T( "むし" )]][m_typetable[_T( "フェアリー" )]] = 0.5;

		// いわ（弱点：ほのお・こおり・ひこう・むし、半減：かくとう・じめん・はがね、無効：なし）
		m_table[m_typetable[_T( "いわ" )]][m_typetable[_T( "ほのお" )]]
			= m_table[m_typetable[_T( "いわ" )]][m_typetable[_T( "こおり" )]]
			= m_table[m_typetable[_T( "いわ" )]][m_typetable[_T( "ひこう" )]]
			= m_table[m_typetable[_T( "いわ" )]][m_typetable[_T( "むし" )]] = 2;
		m_table[m_typetable[_T( "いわ" )]][m_typetable[_T( "かくとう" )]]
			= m_table[m_typetable[_T( "いわ" )]][m_typetable[_T( "じめん" )]]
			= m_table[m_typetable[_T( "いわ" )]][m_typetable[_T( "はがね" )]] = 0.5;

		// ゴースト（弱点：エスパー・ゴースト、半減：あく、無効：ノーマル）
		m_table[m_typetable[_T( "ゴースト" )]][m_typetable[_T( "ゴースト" )]]
			= m_table[m_typetable[_T( "ゴースト" )]][m_typetable[_T( "エスパー" )]] = 2;
		m_table[m_typetable[_T( "ゴースト" )]][m_typetable[_T( "あく" )]] = 0.5;
		m_table[m_typetable[_T( "ゴースト" )]][m_typetable[_T( "ノーマル" )]] = 0;

		// ドラゴン（弱点：ドラゴン、半減：はがね、無効：フェアリー）
		m_table[m_typetable[_T( "ドラゴン" )]][m_typetable[_T( "ドラゴン" )]] = 2;
		m_table[m_typetable[_T( "ドラゴン" )]][m_typetable[_T( "はがね" )]] = 0.5;
		m_table[m_typetable[_T( "ドラゴン" )]][m_typetable[_T( "フェアリー" )]] = 0;

		// あく（弱点：エスパー・ゴースト、半減：あく・フェアリー、無効：なし）
		m_table[m_typetable[_T( "あく" )]][m_typetable[_T( "エスパー" )]]
			= m_table[m_typetable[_T( "あく" )]][m_typetable[_T( "ゴースト" )]] = 2;
		m_table[m_typetable[_T( "あく" )]][m_typetable[_T( "あく" )]]
			= m_table[m_typetable[_T( "あく" )]][m_typetable[_T( "フェアリー" )]] = 0.5;

		// はがね（弱点：こおり・いわ・フェアリー、半減：ほのお・みず・でんき・はがね、無効：なし）
		m_table[m_typetable[_T( "はがね" )]][m_typetable[_T( "こおり" )]]
			= m_table[m_typetable[_T( "はがね" )]][m_typetable[_T( "いわ" )]]
			= m_table[m_typetable[_T( "はがね" )]][m_typetable[_T( "フェアリー" )]] = 2;
		m_table[m_typetable[_T( "はがね" )]][m_typetable[_T( "ほのお" )]]
			= m_table[m_typetable[_T( "はがね" )]][m_typetable[_T( "みず" )]]
			= m_table[m_typetable[_T( "はがね" )]][m_typetable[_T( "でんき" )]]
			= m_table[m_typetable[_T( "はがね" )]][m_typetable[_T( "はがね" )]] = 0.5;

		// フェアリー（弱点：かくとう・ドラゴン・あく、半減：ほのお・どく・はがね、無効：なし）
		m_table[m_typetable[_T( "フェアリー" )]][m_typetable[_T( "かくとう" )]]
			= m_table[m_typetable[_T( "フェアリー" )]][m_typetable[_T( "ドラゴン" )]]
			= m_table[m_typetable[_T( "フェアリー" )]][m_typetable[_T( "あく" )]] = 2;
		m_table[m_typetable[_T( "フェアリー" )]][m_typetable[_T( "ほのお" )]]
			= m_table[m_typetable[_T( "フェアリー" )]][m_typetable[_T( "どく" )]]
			= m_table[m_typetable[_T( "フェアリー" )]][m_typetable[_T( "はがね" )]] = 0.5;
	}

private:
	std::vector<std::vector<double>> m_table; // 相性変換テーブル
	std::map<CString, int> m_typetable; // タイプ名称変換テーブル
};

// 特性相性
// →これ定義する？めっちゃ大変そう…ｗ
