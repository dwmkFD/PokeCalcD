#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <string>
#include <memory>

/* ポケモンのデータ定義 */


// ポケモンのデータ
class PokemonData {
public:
	int m_Level; // レベル

	// HABCDS
	int m_HitPoint;
	int m_Attack;
	int m_Block;
	int m_Contact;
	int m_Diffence;
	int m_Speed;

	// 性別
	int m_gender; // メス、不明、オス → -1, 0, 1とか。闘争心とかの対応

	// 身長と体重
	int m_Height; // 身長だが、今のところ依存技はない？
	int m_Weight; // 体重は、ヘビーボンバーとか草結びとかに必要

	// 図鑑番号（全国、第N世代）
	// 同じバージョン内のリージョンフォーム、メガシンカ等は、とりあえず同じ番号にしておく
	int m_zukkanNum;
	std::vector<int> m_zukkanNumLocal; // 出現しない世代、図鑑に載らない世代は-1を入れる？

	// タイプ
	// ハロウィンとか森の呪いとかにも対応する(2つ以上に増える可能性がある)への対応のため、vectorにしておく
	std::vector<CString> m_type;

	std::vector<CString> m_ability;	// 特性

	std::vector<CString> m_move; // 覚える技

	static constexpr unsigned int HP_Index = 0;
	static constexpr unsigned int Attack_Index = 1;
	static constexpr unsigned int Block_Index = 2;
	static constexpr unsigned int Contact_Index = 3;
	static constexpr unsigned int Diffence_Index = 4;
	static constexpr unsigned int Speed_Index = 5;
	static constexpr unsigned int StatusKind = 6;
};

