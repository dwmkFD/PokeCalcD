#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <string>
#include <memory>

/* ポケモンのデータ定義 */

// 持ち物や特性に関するデータ
class PokemonDataSub {
public:
	int m_barrier; // bit0: リフレクター、 bit1: 光の壁
	uint64_t m_ability; // 特性ビットをセット
	uint64_t m_item; // 持ち物
	uint64_t m_rank; // ランク補正

	// 特性ビット定義
	static constexpr uint64_t ABILITY_SNIPER        = 0x0000000000000001; // スナイパー
	static constexpr uint64_t ABILITY_TINTLENS      = 0x0000000000000002; // 色眼鏡
	static constexpr uint64_t ABILITY_FLUFFY_FLARE  = 0x0000000000000004; // もふもふ(炎被弾)
	static constexpr uint64_t ABILITY_FRIENDGUARD   = 0x0000000000000008; // フレンドガード
	static constexpr uint64_t ABILITY_ICE_SCALES    = 0x0000000000000010; // 氷の鱗粉
	static constexpr uint64_t ABILITY_PUNKROCK_ATK  = 0x0000000000000020; // パンクロック(攻撃側)
	static constexpr uint64_t ABILITY_PUNKROCK_DEF  = 0x0000000000000040; // パンクロック(防御側)
	static constexpr uint64_t ABILITY_SHADOWSHIELD  = 0x0000000000000080; // ファントムガード
	static constexpr uint64_t ABILITY_MULTISCALE    = 0x0000000000000100; // マルチスケイル
	static constexpr uint64_t ABILITY_FLUFFY_DIRECT = 0x0000000000000200; // もふもふ(接触技)
	static constexpr uint64_t ABILITY_FILTER        = 0x0000000000000400; // ハードロック/フィルター
	static constexpr uint64_t ABILITY_PRISMARMOR    = 0x0000000000000800; // プリズムアーマー
	static constexpr uint64_t ABILITY_LONGREACH     = 0x0000000000001000; // 遠隔
	static constexpr uint64_t ABILITY_A = 0x0000000000002000; // ノーマルスキン
	static constexpr uint64_t ABILITY_B = 0x0000000000004000; // スカイスキン
	static constexpr uint64_t ABILITY_C = 0x0000000000008000; // エレキスキン
	static constexpr uint64_t ABILITY_D = 0x0000000000010000; // フリーズスキン
	static constexpr uint64_t ABILITY_E = 0x0000000000020000; // フェアリースキン
	static constexpr uint64_t ABILITY_F = 0x0000000000040000; // アナライズ
	static constexpr uint64_t ABILITY_G = 0x0000000000080000; // うるおいボイス
	static constexpr uint64_t ABILITY_H = 0x0000000000100000; // エアロック/ノー天気
	static constexpr uint64_t ABILITY_I = 0x0000000000200000; // 硬い爪
	static constexpr uint64_t ABILITY_J = 0x0000000000400000; // 頑丈顎
	static constexpr uint64_t ABILITY_K = 0x0000000000800000; // 肝っ玉
	static constexpr uint64_t ABILITY_L = 0x0000000000100000; // 強運
	static constexpr uint64_t ABILITY_M = 0x0000000000200000; // 激流
	static constexpr uint64_t ABILITY_N = 0x0000000000400000; // 新緑
	static constexpr uint64_t ABILITY_O = 0x0000000000800000; // 猛火
	static constexpr uint64_t ABILITY_P = 0x0000000001000000; // 変幻自在/リベロ
	static constexpr uint64_t ABILITY_Q = 0x0000000002000000; // 五里霧中
	static constexpr uint64_t ABILITY_R = 0x0000000004000000; // 根性
	static constexpr uint64_t ABILITY_S = 0x0000000008000000; // サンパワー
	static constexpr uint64_t ABILITY_T = 0x0000000001000000; // スキルリンク
	static constexpr uint64_t ABILITY_U = 0x0000000002000000; // 水泡
	static constexpr uint64_t ABILITY_V = 0x0000000004000000; // 捨て身
	static constexpr uint64_t ABILITY_W = 0x0000000008000000; // 砂の力

	// アイテムビット定義
	static constexpr uint64_t ITEM_METRONOME       = 0x000000000000003F; // メトロノームN回目
	static constexpr uint64_t ITEM_LIFEORB         = 0x0000000000000040; // 命の珠
	static constexpr uint64_t ITEM_TYPE_ENHANCE    = 0x0000000000000080; // タイプ強化アイテム
	static constexpr uint64_t ITEM_SOULDEW         = 0x0000000000000100; // こころのしずく
	static constexpr uint64_t ITEM_CHOICEBAND      = 0x0000000000000200; // こだわりハチマキ
	static constexpr uint64_t ITEM_CHOICESPECS     = 0x0000000000000400; // こだわりメガネ
	static constexpr uint64_t ITEM_EXPERTBELT      = 0x0000000000000800; // たつじんのおび
	static constexpr uint64_t ITEM_MUSCLEBAND      = 0x0000000000001000; // ちからのハチマキ
	static constexpr uint64_t ITEM_WISEGLASSES     = 0x0000000000002000; // ものしりメガネ
	static constexpr uint64_t ITEM_HALFDAMAGEBERRY = 0x0000000000004000; // 半減実
	static constexpr uint64_t ITEM_NORMALGEM       = 0x0000000000008000; // ノーマルジュエル
};

// ポケモンのデータ
class PokemonData {
public:
	int m_Level; // レベル

	// HABCDS
	int m_status[6];

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

	PokemonDataSub m_option; // バトル全体ではなくポケモン毎の設定

	void clear() {
		// 上書きされない情報をクリアする -> でないと、ポケモンを変えても前に持ってたタイプ等の情報を引き継いでしまう…
		m_zukkanNumLocal.clear();
		m_type.clear();
		m_ability.clear();
		m_move.clear();
	}

	static constexpr unsigned int HP_Index = 0;
	static constexpr unsigned int Attack_Index = 1;
	static constexpr unsigned int Block_Index = 2;
	static constexpr unsigned int Contact_Index = 3;
	static constexpr unsigned int Diffence_Index = 4;
	static constexpr unsigned int Speed_Index = 5;
	static constexpr unsigned int StatusKind = 6;
};

