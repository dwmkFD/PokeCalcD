#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

/* 技の定義 */


// [余談]わざは英語版では「move」なのだが、色々と競合しそうなので、PokeMoveにしておいた
class PokeMove {
public:
private:
	std::string m_name; // 技名
	std::string m_type; // 技のタイプ
	std::string m_category; // 技の分類（物理、特殊、変化技）
	int m_power; // 技の威力
	int m_accuracy; // 技の命中率
	int m_range; // 技の範囲（単体、全体、相手全体 → ダブルで威力の判定に使用する(後者は一つにまとめても良いかもしれない)）
	bool m_direct; // 接触攻撃か否か（鮫肌とかの反撃で落ちるかどうかを計算結果に含むなら）
};

// タイプ相性
struct TypeCompatibility {
	// 攻撃側(type1)から防御側(type2)への相性計算
	// 戻り値は倍率( 0、1/4、1/2、1、2、4、8）
	// →例えば、ランドロスが森の呪いを受けると氷は8倍になるので、一応8まであり得る
	double check( std::string &type1, std::string &type2 ) const {
	}

	TypeCompatibility() {
		// タイプ名を数値に変換するためのテーブル
		m_typetable["ノーマル"] = 0; m_typetable["ほのお"] = 1;
		m_typetable["みず"] = 2; m_typetable["でんき"] = 3;
		m_typetable["くさ"] = 4; m_typetable["こおり"] = 5;
		m_typetable["かくとう"] = 6; m_typetable["どく"] = 7;
		m_typetable["じめん"] = 8; m_typetable["ひこう"] = 9;
		m_typetable["エスパー"] = 10; m_typetable["むし"] = 11;
		m_typetable["いわ"] = 12; m_typetable["ゴースト"] = 13;
		m_typetable["ドラゴン"] = 14; m_typetable["あく"] = 15;
		m_typetable["はがね"] = 16; m_typetable["フェアリー"] = 17;

		// タイプ相性を計算するテーブル
		m_table.assign( 18, std::vector<double>( 18, 1 ) );

		// ノーマル（弱点：なし、半減：いわ・はがね、無効：ゴースト）
		m_table[m_typetable["ノーマル"]][m_typetable["いわ"]]
			= m_table[m_typetable["ノーマル"]][m_typetable["はがね"]] = 0.5;
		m_table[m_typetable["ノーマル"]][m_typetable["ゴースト"]] = 0;

		// ほのお（弱点：くさ・こおり・むし・はがね、半減：みず・いわ・ドラゴン、無効：なし）
		m_table[m_typetable["ほのお"]][m_typetable["くさ"]]
			= m_table[m_typetable["ほのお"]][m_typetable["こおり"]]
			= m_table[m_typetable["ほのお"]][m_typetable["むし"]]
			= m_table[m_typetable["ほのお"]][m_typetable["はがね"]] = 2;
		m_table[m_typetable["ほのお"]][m_typetable["みず"]]
			= m_table[m_typetable["ほのお"]][m_typetable["いわ"]]
			= m_table[m_typetable["ほのお"]][m_typetable["ドラゴン"]] = 0.5;

		// みず（弱点：ほのお・じめん・いわ、半減：みず・ドラゴン、無効：なし）
		m_table[m_typetable["みず"]][m_typetable["ほのお"]]
			= m_table[m_typetable["みず"]][m_typetable["じめん"]]
			= m_table[m_typetable["みず"]][m_typetable["いわ"]] = 2;
		m_table[m_typetable["みず"]][m_typetable["みず"]]
			= m_table[m_typetable["みず"]][m_typetable["ドラゴン"]] = 0.5;

		// でんき（弱点：みず・ひこう、半減：くさ・でんき・ドラゴン、無効：じめん）
		m_table[m_typetable["でんき"]][m_typetable["みず"]]
			= m_table[m_typetable["でんき"]][m_typetable["ひこう"]] = 2;
		m_table[m_typetable["でんき"]][m_typetable["くさ"]]
			= m_table[m_typetable["でんき"]][m_typetable["でんき"]]
			= m_table[m_typetable["でんき"]][m_typetable["ドラゴン"]] = 0.5;
		m_table[m_typetable["でんき"]][m_typetable["じめん"]] = 0;

		// くさ（弱点：みず・じめん・いわ、半減：ほのお・くさ・どく・ひこう・むし・ドラゴン・はがね、無効：なし）
		m_table[m_typetable["くさ"]][m_typetable["みず"]]
			= m_table[m_typetable["くさ"]][m_typetable["じめん"]]
			= m_table[m_typetable["くさ"]][m_typetable["いわ"]] = 2;
		m_table[m_typetable["くさ"]][m_typetable["ほのお"]]
			= m_table[m_typetable["くさ"]][m_typetable["くさ"]]
			= m_table[m_typetable["くさ"]][m_typetable["どく"]]
			= m_table[m_typetable["くさ"]][m_typetable["ひこう"]]
			= m_table[m_typetable["くさ"]][m_typetable["むし"]]
			= m_table[m_typetable["くさ"]][m_typetable["ドラゴン"]]
			= m_table[m_typetable["くさ"]][m_typetable["はがね"]] = 0.5;

		// こおり（弱点：くさ・じめん・ひこう・ドラゴン、半減：こおり、無効：なし）
		m_table[m_typetable["こおり"]][m_typetable["くさ"]]
			= m_table[m_typetable["こおり"]][m_typetable["じめん"]]
			= m_table[m_typetable["こおり"]][m_typetable["ひこう"]]
			= m_table[m_typetable["こおり"]][m_typetable["ドラゴン"]] = 2;
		m_table[m_typetable["こおり"]][m_typetable["こおり"]] = 0.5;

		// かくとう（弱点：ノーマル・こおり・いわ・あく・はがね、半減：どく・ひこう・エスパー・むし・フェアリー、無効：ゴースト）
		m_table[m_typetable["かくとう"]][m_typetable["ノーマル"]]
			= m_table[m_typetable["かくとう"]][m_typetable["こおり"]]
			= m_table[m_typetable["かくとう"]][m_typetable["いわ"]]
			= m_table[m_typetable["かくとう"]][m_typetable["あく"]]
			= m_table[m_typetable["かくとう"]][m_typetable["はがね"]] = 2;
		m_table[m_typetable["かくとう"]][m_typetable["どく"]]
			= m_table[m_typetable["かくとう"]][m_typetable["ひこう"]]
			= m_table[m_typetable["かくとう"]][m_typetable["エスパー"]]
			= m_table[m_typetable["かくとう"]][m_typetable["むし"]]
			= m_table[m_typetable["かくとう"]][m_typetable["フェアリー"]] = 0.5;
		m_table[m_typetable["かくとう"]][m_typetable["ゴースト"]] = 0;

		// どく（弱点：くさ・フェアリー、半減：どく・じめん・いわ・ゴースト、無効：はがね）
		m_table[m_typetable["どく"]][m_typetable["くさ"]]
			= m_table[m_typetable["どく"]][m_typetable["フェアリー"]] = 2;
		m_table[m_typetable["どく"]][m_typetable["どく"]]
			= m_table[m_typetable["どく"]][m_typetable["じめん"]]
			= m_table[m_typetable["どく"]][m_typetable["いわ"]]
			= m_table[m_typetable["どく"]][m_typetable["ゴースト"]] = 0.5;
		m_table[m_typetable["どく"]][m_typetable["はがね"]] = 0;

		// じめん（弱点：ほのお・でんき・どく・いわ・はがね、半減：くさ・むし、無効：ひこう）
		m_table[m_typetable["じめん"]][m_typetable["ほのお"]]
			= m_table[m_typetable["じめん"]][m_typetable["でんき"]]
			= m_table[m_typetable["じめん"]][m_typetable["どく"]]
			= m_table[m_typetable["じめん"]][m_typetable["いわ"]]
			= m_table[m_typetable["じめん"]][m_typetable["はがね"]] = 2;
		m_table[m_typetable["じめん"]][m_typetable["くさ"]]
			= m_table[m_typetable["じめん"]][m_typetable["むし"]] = 0.5;
		m_table[m_typetable["じめん"]][m_typetable["ひこう"]] = 0;

		// ひこう（弱点：くさ・かくとう・むし、半減：いわ・はがね、無効：なし）
		m_table[m_typetable["ひこう"]][m_typetable["くさ"]]
			= m_table[m_typetable["ひこう"]][m_typetable["かくとう"]]
			= m_table[m_typetable["ひこう"]][m_typetable["むし"]] = 2;
		m_table[m_typetable["ひこう"]][m_typetable["いわ"]]
			= m_table[m_typetable["ひこう"]][m_typetable["はがね"]] = 0.5;

		// エスパー（弱点：かくとう・どく、半減：エスパー・はがね、無効：あく）
		m_table[m_typetable["エスパー"]][m_typetable["かくとう"]]
			= m_table[m_typetable["エスパー"]][m_typetable["どく"]] = 2;
		m_table[m_typetable["エスパー"]][m_typetable["エスパー"]]
			= m_table[m_typetable["エスパー"]][m_typetable["はがね"]] = 0.5;
		m_table[m_typetable["エスパー"]][m_typetable["あく"]] = 0;

		// むし（弱点：くさ・エスパー・あく、半減：ほのお・かくとう・どく・ひこう・ゴースト・はがね・フェアリー、無効：なし）
		m_table[m_typetable["ひこう"]][m_typetable["くさ"]]
			= m_table[m_typetable["ひこう"]][m_typetable["かくとう"]]
			= m_table[m_typetable["ひこう"]][m_typetable["むし"]] = 2;
		m_table[m_typetable["ひこう"]][m_typetable["いわ"]]
			= m_table[m_typetable["ひこう"]][m_typetable["はがね"]] = 0.5;
	}

private:
	std::vector<std::vector<double>> m_table; // 相性変換テーブル
	std::map<std::string, int> m_typetable; // タイプ名称変換テーブル
};

// 特性相性
// →これ定義する？めっちゃ大変そう…ｗ