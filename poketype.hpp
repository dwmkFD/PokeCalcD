#pragma once

#include <Windows.h>
#include <afxstr.h>

#include <vector>
#include <map>
#include <memory>

// タイプに関する定義

class PokeType {
public:
	PokeType() {
		// タイプ名を数値に変換するためのテーブル
		m_typetable[_T( "ノーマル" )] = 0; m_typetable[_T( "ほのお" )] = 1;
		m_typetable[_T( "みず" )] = 2; m_typetable[_T( "でんき" )] = 3;
		m_typetable[_T( "くさ" )] = 4; m_typetable[_T( "こおり" )] = 5;
		m_typetable[_T( "かくとう" )] = 6; m_typetable[_T( "どく" )] = 7;
		m_typetable[_T( "じめん" )] = 8; m_typetable[_T( "ひこう" )] = 9;
		m_typetable[_T( "エスパー" )] = 10; m_typetable[_T( "むし" )] = 11;
		m_typetable[_T( "いわ" )] = 12; m_typetable[_T( "ゴースト" )] = 13;
		m_typetable[_T( "ドラゴン" )] = 14; m_typetable[_T( "あく" )] = 15;
		m_typetable[_T( "はがね" )] = 16; m_typetable[_T( "フェアリー" )] = 17;
		m_typetable[_T( "テラスタイプ" )] = 18; // テラスタイプ未選択の場合、ノーマルと区別が付かなくなるので入れておく(使うことは無いと思う)
	}

	std::map<CString, int> &getTypeTable() { return ( m_typetable ); }

protected:
	std::map<CString, int> m_typetable; // タイプ名称変換テーブル
};
