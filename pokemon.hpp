#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <map>
#include <string>
#include <memory>

#include "poketype.hpp"

/* ポケモンのデータ定義 */

// 特性は別管理した方が良いかも
class PokemonAbility {
public:
	PokemonAbility() {
		m_ability_map[_T( "スナイパー" )] = ABILITY_SNIPER;
		m_ability_map[_T( "いろめがね" )] = ABILITY_TINTLENS;
		m_ability_map[_T( "もふもふ" )] = ABILITY_FLUFFY; // 各ポケモンに情報持たせるようにしたから、攻撃側と防御側でそれぞれ作用するやつも分けなくても良いと思う
		m_ability_map[_T( "フレンドガード" )] = ABILITY_FRIENDGUARD;
		m_ability_map[_T( "こおりのりんぷん" )] = ABILITY_ICE_SCALES;
		m_ability_map[_T( "パンクロック" )] = ABILITY_PUNKROCK;
		m_ability_map[_T( "ファントムガード" )] = ABILITY_SHADOWSHIELD;
		m_ability_map[_T( "マルチスケイル" )] = ABILITY_MULTISCALE;
		m_ability_map[_T( "フィルター" )] = ABILITY_FILTER;
		m_ability_map[_T( "ハードロック" )] = ABILITY_SOLIDROCK;
		m_ability_map[_T( "プリズムアーマー" )] = ABILITY_PRISMARMOR;
		m_ability_map[_T( "えんかく" )] = ABILITY_LONGREACH;
		m_ability_map[_T( "ノーマルスキン" )] = ABILITY_NORMALIZE;
		m_ability_map[_T( "スカイスキン" )] = ABILITY_AERILATE;
		m_ability_map[_T( "エレキスキン" )] = ABILITY_GALVANIZE;
		m_ability_map[_T( "フリーズスキン" )] = ABILITY_REFRIGERATE;
		m_ability_map[_T( "フェアリースキン" )] = ABILITY_PIXILATE;
		m_ability_map[_T( "アナライズ" )] = ABILITY_ANALYTIC;
		m_ability_map[_T( "うるおいボイス" )] = ABILITY_LIQUIDVOICE;
		m_ability_map[_T( "エアロック" )] = ABILITY_AIRLOCK;
		m_ability_map[_T( "ノーてんき" )] = ABILITY_CLOUDNINE;
		m_ability_map[_T( "かたいツメ" )] = ABILITY_TOUGHCLAWS;
		m_ability_map[_T( "がんじょうあご" )] = ABILITY_STRONGJAW;
		m_ability_map[_T( "きもったま" )] = ABILITY_SCRAPPY;
		m_ability_map[_T( "きょううん" )] = ABILITY_SUPERLUCK;
		m_ability_map[_T( "げきりゅう" )] = ABILITY_TORRENT;
		m_ability_map[_T( "しんりょく" )] = ABILITY_OVERGROW;
		m_ability_map[_T( "もうか" )] = ABILITY_BLAZE;
		m_ability_map[_T( "へんげんじざい" )] = ABILITY_PROTEAN;
		m_ability_map[_T( "リベロ" )] = ABILITY_LIBERO;
		m_ability_map[_T( "ごりむちゅう" )] = ABILITY_GORILLATACTICS;
		m_ability_map[_T( "こんじょう" )] = ABILITY_GUTS;
		m_ability_map[_T( "サンパワー" )] = ABILITY_SOLARPOWER;
		m_ability_map[_T( "スキルリンク" )] = ABILITY_SKILLLINK;
		m_ability_map[_T( "すいほう" )] = ABILITY_WATERBUBBLE;
		m_ability_map[_T( "すてみ" )] = ABILITY_RECKLESS;
		m_ability_map[_T( "すなのちから" )] = ABILITY_SANDFORCE;
		m_ability_map[_T( "すりぬけ" )] = ABILITY_INFILTRATOR;
		m_ability_map[_T( "スロースタート" )] = ABILITY_SLOWSTART;
		m_ability_map[_T( "ちからづく" )] = ABILITY_SHEERFORCE;
		m_ability_map[_T( "ちからもち" )] = ABILITY_HUGEPOWER;
		m_ability_map[_T( "ヨガパワー" )] = ABILITY_PUREPOWER;
		m_ability_map[_T( "テクニシャン" )] = ABILITY_TECHNICIAN;
		m_ability_map[_T( "てきおうりょく" )] = ABILITY_ADAPTABILITY;
		m_ability_map[_T( "てつのこぶし" )] = ABILITY_IRONFIST;
		m_ability_map[_T( "てんねん" )] = ABILITY_UNAWARE;
		m_ability_map[_T( "どくぼうそう" )] = ABILITY_TOXICBOOST;
		m_ability_map[_T( "トランジスタ" )] = ABILITY_TRANSISTOR;
		m_ability_map[_T( "ねつぼうそう" )] = ABILITY_FLAREBOOST;
		m_ability_map[_T( "はがねつかい" )] = ABILITY_STEELWORKER;
		m_ability_map[_T( "はがねのせいしん" )] = ABILITY_STEELYSPIRIT;
		m_ability_map[_T( "はりきり" )] = ABILITY_HUSTLE;
		m_ability_map[_T( "プラス" )] = ABILITY_PLUSMINUS;
		m_ability_map[_T( "マイナス" )] = ABILITY_PLUSMINUS;
		m_ability_map[_T( "むしのしらせ" )] = ABILITY_SWARM;
		m_ability_map[_T( "メガランチャー" )] = ABILITY_MEGALAUNCHER;
		m_ability_map[_T( "もらいび" )] = ABILITY_FLASHFIRE;
		m_ability_map[_T( "よわき" )] = ABILITY_DEFEATIST;
		m_ability_map[_T( "りゅうのあぎと" )] = ABILITY_DRAGONSMAW;
		m_ability_map[_T( "いわはこび" )] = ABILITY_ROCKYPAYLOAD;
		m_ability_map[_T( "ひとでなし" )] = ABILITY_MERCILESS;
		m_ability_map[_T( "こだいかっせい" )] = ABILITY_PROTOSYNTHESIS;
		m_ability_map[_T( "クォークチャージ" )] = ABILITY_QUARKDRIVE;
		m_ability_map[_T( "ひひいろのこどう" )] = ABILITY_ORICHALCUMPULSE;
		m_ability_map[_T( "ハドロンエンジン" )] = ABILITY_HADRONENGINE;
	}

	std::map<CString, uint64_t> m_ability_map;

	// 特性ビット定義（PokemonDataSubから移植する）
	static constexpr uint64_t ABILITY_SNIPER          = 0x0000000000000001; // スナイパー
	static constexpr uint64_t ABILITY_TINTLENS        = 0x0000000000000002; // 色眼鏡
	static constexpr uint64_t ABILITY_FLUFFY          = 0x0000000000000004; // もふもふ
	static constexpr uint64_t ABILITY_FRIENDGUARD     = 0x0000000000000008; // フレンドガード
	static constexpr uint64_t ABILITY_ICE_SCALES      = 0x0000000000000010; // 氷の鱗粉
	static constexpr uint64_t ABILITY_PUNKROCK        = 0x0000000000000020; // パンクロック
	static constexpr uint64_t ABILITY_XXXXXXXXXXXXXX1 = 0x0000000000000040; // 空きビット
	static constexpr uint64_t ABILITY_SHADOWSHIELD    = 0x0000000000000080; // ファントムガード
	static constexpr uint64_t ABILITY_MULTISCALE      = 0x0000000000000100; // マルチスケイル
	static constexpr uint64_t ABILITY_XXXXXXXXXXXXXX2 = 0x0000000000000200; // 空きビット
	static constexpr uint64_t ABILITY_FILTER          = 0x0000000000000400; // フィルター
	static constexpr uint64_t ABILITY_SOLIDROCK       = 0x0000000000000400; // ハードロック
	static constexpr uint64_t ABILITY_PRISMARMOR      = 0x0000000000000800; // プリズムアーマー
	static constexpr uint64_t ABILITY_LONGREACH       = 0x0000000000001000; // 遠隔
	static constexpr uint64_t ABILITY_NORMALIZE       = 0x0000000000002000; // ノーマルスキン
	static constexpr uint64_t ABILITY_AERILATE        = 0x0000000000004000; // スカイスキン
	static constexpr uint64_t ABILITY_GALVANIZE       = 0x0000000000008000; // エレキスキン
	static constexpr uint64_t ABILITY_REFRIGERATE     = 0x0000000000010000; // フリーズスキン
	static constexpr uint64_t ABILITY_PIXILATE        = 0x0000000000020000; // フェアリースキン
	static constexpr uint64_t ABILITY_ANALYTIC        = 0x0000000000040000; // アナライズ
	static constexpr uint64_t ABILITY_LIQUIDVOICE     = 0x0000000000080000; // うるおいボイス
	static constexpr uint64_t ABILITY_AIRLOCK         = 0x0000000000100000; // エアロック
	static constexpr uint64_t ABILITY_CLOUDNINE       = 0x0000000000100000; // ノー天気
	static constexpr uint64_t ABILITY_TOUGHCLAWS      = 0x0000000000200000; // 硬い爪 // memo: 5325/4096
	static constexpr uint64_t ABILITY_STRONGJAW       = 0x0000000000400000; // 頑丈顎
	static constexpr uint64_t ABILITY_SCRAPPY         = 0x0000000000800000; // 肝っ玉
	static constexpr uint64_t ABILITY_SUPERLUCK       = 0x0000000000100000; // 強運
	static constexpr uint64_t ABILITY_TORRENT         = 0x0000000000200000; // 激流
	static constexpr uint64_t ABILITY_OVERGROW        = 0x0000000000400000; // 新緑
	static constexpr uint64_t ABILITY_BLAZE           = 0x0000000000800000; // 猛火
	static constexpr uint64_t ABILITY_PROTEAN         = 0x0000000001000000; // 変幻自在
	static constexpr uint64_t ABILITY_LIBERO          = 0x0000000001000000; // リベロ
	static constexpr uint64_t ABILITY_GORILLATACTICS  = 0x0000000002000000; // 五里霧中
	static constexpr uint64_t ABILITY_GUTS            = 0x0000000004000000; // 根性
	static constexpr uint64_t ABILITY_SOLARPOWER      = 0x0000000008000000; // サンパワー
	static constexpr uint64_t ABILITY_SKILLLINK       = 0x0000000001000000; // スキルリンク
	static constexpr uint64_t ABILITY_WATERBUBBLE     = 0x0000000002000000; // 水泡
	static constexpr uint64_t ABILITY_RECKLESS        = 0x0000000004000000; // 捨て身
	static constexpr uint64_t ABILITY_SANDFORCE       = 0x0000000008000000; // 砂の力
	static constexpr uint64_t ABILITY_INFILTRATOR     = 0x0000000010000000; // すり抜け
	static constexpr uint64_t ABILITY_SLOWSTART       = 0x0000000020000000; // スロースタート
	static constexpr uint64_t ABILITY_SHEERFORCE      = 0x0000000040000000; // 力づく
	static constexpr uint64_t ABILITY_HUGEPOWER       = 0x0000000080000000; // 力持ち
	static constexpr uint64_t ABILITY_PUREPOWER       = 0x0000000080000000; // ヨガパワー
	static constexpr uint64_t ABILITY_TECHNICIAN      = 0x0000000100000000; // テクニシャン
	static constexpr uint64_t ABILITY_ADAPTABILITY    = 0x0000000200000000; // 適応力 
	static constexpr uint64_t ABILITY_IRONFIST        = 0x0000000400000000; // てつのこぶし
	static constexpr uint64_t ABILITY_UNAWARE         = 0x0000000800000000; // 天然
	static constexpr uint64_t ABILITY_TOXICBOOST      = 0x0000001000000000; // 毒暴走
	static constexpr uint64_t ABILITY_TRANSISTOR      = 0x0000002000000000; // トランジスタ
	static constexpr uint64_t ABILITY_FLAREBOOST      = 0x0000004000000000; // 熱暴走
	static constexpr uint64_t ABILITY_STEELWORKER     = 0x0000008000000000; // 鋼使い
	static constexpr uint64_t ABILITY_STEELYSPIRIT    = 0x0000010000000000; // 鋼の精神
	static constexpr uint64_t ABILITY_HUSTLE          = 0x0000020000000000; // 張り切り
	static constexpr uint64_t ABILITY_PLUSMINUS       = 0x0000040000000000; // プラス/マイナス
	static constexpr uint64_t ABILITY_SWARM           = 0x0000080000000000; // むしのしらせ
	static constexpr uint64_t ABILITY_MEGALAUNCHER    = 0x0000100000000000; // メガランチャー
	static constexpr uint64_t ABILITY_FLASHFIRE       = 0x0000200000000000; // 貰い火
	static constexpr uint64_t ABILITY_DEFEATIST       = 0x0000400000000000; // 弱気
	static constexpr uint64_t ABILITY_DRAGONSMAW      = 0x0000800000000000; // 龍のあぎと
	static constexpr uint64_t ABILITY_ROCKYPAYLOAD    = 0x0001000000000000; // 岩運び
	static constexpr uint64_t ABILITY_MERCILESS       = 0x0002000000000000; // 人でなし
	static constexpr uint64_t ABILITY_PROTOSYNTHESIS  = 0x0004000000000000; // 古代活性 // -> 以下4つ、天気とかフィールドを見て自動的に補正するなら、ビット分けないとダメ
	static constexpr uint64_t ABILITY_QUARKDRIVE      = 0x0004000000000000; // クォークチャージ
	static constexpr uint64_t ABILITY_ORICHALCUMPULSE = 0x0004000000000000; // ヒヒイロの鼓動
	static constexpr uint64_t ABILITY_HADRONENGINE    = 0x0004000000000000; // ハドロンエンジン
};

// 持ち物や特性に関するデータ
class PokemonDataSub {
public:
	int m_barrier; // bit0: リフレクター、 bit1: 光の壁
	uint64_t m_ability; // 特性ビットをセット
	uint64_t m_item; // 持ち物
	uint64_t m_rank; // ランク補正 -> これ少なくとも物理/特殊の2つは必要なはず(攻守入れ替えがあるから、5つ持ってた方が良いと思う）
	CString m_teraType; // テラスタイプ
	uint64_t m_conditionAbnormaly; // 状態異常

	void clear() {
		m_barrier = 0;
		m_ability = 0;
		m_item = 0;
		m_rank = 0; // ↑合わせて直す
	}

	// ↓この辺も、ビット定義するの自体は良いけど、std::mapとかに入れておいた方が良いと思う…
	// 　データベースから読み出してポケモンにセットした特性からビット情報を拾うの無理でしょ…
	// 今更だけど、別にビットにしなくて良かったのでは？std::mapとかから拾って、一意に決めれば良いんだし
	// 特性ビット定義
	static constexpr uint64_t ABILITY_SNIPER          = 0x0000000000000001; // スナイパー
	static constexpr uint64_t ABILITY_TINTLENS        = 0x0000000000000002; // 色眼鏡
	static constexpr uint64_t ABILITY_FLUFFY_FLARE    = 0x0000000000000004; // もふもふ(炎被弾)
	static constexpr uint64_t ABILITY_FRIENDGUARD     = 0x0000000000000008; // フレンドガード
	static constexpr uint64_t ABILITY_ICE_SCALES      = 0x0000000000000010; // 氷の鱗粉
	static constexpr uint64_t ABILITY_PUNKROCK_ATK    = 0x0000000000000020; // パンクロック(攻撃側)
	static constexpr uint64_t ABILITY_PUNKROCK_DEF    = 0x0000000000000040; // パンクロック(防御側)
	static constexpr uint64_t ABILITY_SHADOWSHIELD    = 0x0000000000000080; // ファントムガード
	static constexpr uint64_t ABILITY_MULTISCALE      = 0x0000000000000100; // マルチスケイル
	static constexpr uint64_t ABILITY_FLUFFY_DIRECT   = 0x0000000000000200; // もふもふ(接触技)
	static constexpr uint64_t ABILITY_FILTER          = 0x0000000000000400; // フィルター
	static constexpr uint64_t ABILITY_SOLIDROCK       = 0x0000000000000400; // ハードロック
	static constexpr uint64_t ABILITY_PRISMARMOR      = 0x0000000000000800; // プリズムアーマー
	static constexpr uint64_t ABILITY_LONGREACH       = 0x0000000000001000; // 遠隔
	static constexpr uint64_t ABILITY_NORMALIZE       = 0x0000000000002000; // ノーマルスキン
	static constexpr uint64_t ABILITY_AERILATE        = 0x0000000000004000; // スカイスキン
	static constexpr uint64_t ABILITY_GALVANIZE       = 0x0000000000008000; // エレキスキン
	static constexpr uint64_t ABILITY_REFRIGERATE     = 0x0000000000010000; // フリーズスキン
	static constexpr uint64_t ABILITY_PIXILATE        = 0x0000000000020000; // フェアリースキン
	static constexpr uint64_t ABILITY_ANALYTIC        = 0x0000000000040000; // アナライズ
	static constexpr uint64_t ABILITY_LIQUIDVOICE     = 0x0000000000080000; // うるおいボイス
	static constexpr uint64_t ABILITY_AIRLOCK         = 0x0000000000100000; // エアロック
	static constexpr uint64_t ABILITY_CLOUDNINE       = 0x0000000000100000; // ノー天気
	static constexpr uint64_t ABILITY_TOUGHCLAWS      = 0x0000000000200000; // 硬い爪 // memo: 5325/4096
	static constexpr uint64_t ABILITY_STRONGJAW       = 0x0000000000400000; // 頑丈顎
	static constexpr uint64_t ABILITY_SCRAPPY         = 0x0000000000800000; // 肝っ玉
	static constexpr uint64_t ABILITY_SUPERLUCK       = 0x0000000000100000; // 強運
	static constexpr uint64_t ABILITY_TORRENT         = 0x0000000000200000; // 激流
	static constexpr uint64_t ABILITY_OVERGROW        = 0x0000000000400000; // 新緑
	static constexpr uint64_t ABILITY_BLAZE           = 0x0000000000800000; // 猛火
	static constexpr uint64_t ABILITY_PROTEAN         = 0x0000000001000000; // 変幻自在
	static constexpr uint64_t ABILITY_LIBERO          = 0x0000000001000000; // リベロ
	static constexpr uint64_t ABILITY_GORILLATACTICS  = 0x0000000002000000; // 五里霧中
	static constexpr uint64_t ABILITY_GUTS            = 0x0000000004000000; // 根性
	static constexpr uint64_t ABILITY_SOLARPOWER      = 0x0000000008000000; // サンパワー
	static constexpr uint64_t ABILITY_SKILLLINK       = 0x0000000001000000; // スキルリンク
	static constexpr uint64_t ABILITY_WATERBUBBLE     = 0x0000000002000000; // 水泡
	static constexpr uint64_t ABILITY_RECKLESS        = 0x0000000004000000; // 捨て身
	static constexpr uint64_t ABILITY_SANDFORCE       = 0x0000000008000000; // 砂の力
	static constexpr uint64_t ABILITY_INFILTRATOR     = 0x0000000010000000; // すり抜け
	static constexpr uint64_t ABILITY_SLOWSTART       = 0x0000000020000000; // スロースタート
	static constexpr uint64_t ABILITY_SHEERFORCE      = 0x0000000040000000; // 力づく
	static constexpr uint64_t ABILITY_HUGEPOWER       = 0x0000000080000000; // 力持ち
	static constexpr uint64_t ABILITY_PUREPOWER       = 0x0000000080000000; // ヨガパワー
	static constexpr uint64_t ABILITY_TECHNICIAN      = 0x0000000100000000; // テクニシャン
	static constexpr uint64_t ABILITY_ADAPTABILITY    = 0x0000000200000000; // 適応力 
	static constexpr uint64_t ABILITY_IRONFIST        = 0x0000000400000000; // てつのこぶし
	static constexpr uint64_t ABILITY_UNAWARE         = 0x0000000800000000; // 天然
	static constexpr uint64_t ABILITY_TOXICBOOST      = 0x0000001000000000; // 毒暴走
	static constexpr uint64_t ABILITY_TRANSISTOR      = 0x0000002000000000; // トランジスタ
	static constexpr uint64_t ABILITY_FLAREBOOST      = 0x0000004000000000; // 熱暴走
	static constexpr uint64_t ABILITY_STEELWORKER     = 0x0000008000000000; // 鋼使い
	static constexpr uint64_t ABILITY_STEELYSPIRIT    = 0x0000010000000000; // 鋼の精神
	static constexpr uint64_t ABILITY_HUSTLE          = 0x0000020000000000; // 張り切り
	static constexpr uint64_t ABILITY_PLUSMINUS       = 0x0000040000000000; // プラス/マイナス
	static constexpr uint64_t ABILITY_SWARM           = 0x0000080000000000; // むしのしらせ
	static constexpr uint64_t ABILITY_MEGALAUNCHER    = 0x0000100000000000; // メガランチャー
	static constexpr uint64_t ABILITY_FLASHFIRE       = 0x0000200000000000; // 貰い火
	static constexpr uint64_t ABILITY_DEFEATIST       = 0x0000400000000000; // 弱気
	static constexpr uint64_t ABILITY_DRAGONSMAW      = 0x0000800000000000; // 龍のあぎと
	static constexpr uint64_t ABILITY_ROCKYPAYLOAD    = 0x0001000000000000; // 岩運び
	static constexpr uint64_t ABILITY_MERCILESS       = 0x0002000000000000; // 人でなし
	static constexpr uint64_t ABILITY_PROTOSYNTHESIS  = 0x0004000000000000; // 古代活性 // -> 以下4つ、天気とかフィールドを見て自動的に補正するなら、ビット分けないとダメ
	static constexpr uint64_t ABILITY_QUARKDRIVE      = 0x0004000000000000; // クォークチャージ
	static constexpr uint64_t ABILITY_ORICHALCUMPULSE = 0x0004000000000000; // ヒヒイロの鼓動
	static constexpr uint64_t ABILITY_HADRONENGINE    = 0x0004000000000000; // ハドロンエンジン
	// まだある………？

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
	static constexpr uint64_t ITEM_LIGHTBALL       = 0x0000000000010000; // 電気玉
	static constexpr uint64_t ITEM_LEEK            = 0x0000000000020000; // 長ネギ
	static constexpr uint64_t ITEM_GRISEOUSORB     = 0x0000000000040000; // 白金玉
	static constexpr uint64_t ITEM_THICKCLUB       = 0x0000000000080000; // ふといホネ
	static constexpr uint64_t ITEM_LUCKYPUNCH      = 0x0000000000100000; // ラッキーパンチ
	static constexpr uint64_t ITEM_SITRUSBERRY     = 0x0000000000200000; // オボンのみ
	static constexpr uint64_t ITEM_FOCUSSASH       = 0x0000000000400000; // きあいのタスキ
	static constexpr uint64_t ITEM_IRONBALL        = 0x0000000000800000; // くろいてっきゅう
	static constexpr uint64_t ITEM_DEEPSEASCALE    = 0x0000000001000000; // しんかいの鱗
	static constexpr uint64_t ITEM_EVIOLITE        = 0x0000000002000000; // しんかのきせき
	static constexpr uint64_t ITEM_LEFTOVERS       = 0x0000000004000000; // 食べ残し
	static constexpr uint64_t ITEM_ASSAULTVEST     = 0x0000000008000000; // とつげきチョッキ
	static constexpr uint64_t ITEM_METALPOWDER     = 0x0000000010000000; // メタルパウダー
	static constexpr uint64_t ITEM_SCOPELENS       = 0x0000000020000000; // ピントレンズ
	static constexpr uint64_t ITEM_RAZORCLAW       = 0x0000000020000000; // するどいツメ

	// 状態異常ビット定義
	static constexpr uint64_t CONDITION_POISON    = 0x01; // 毒・猛毒
	static constexpr uint64_t CONDITION_BURN      = 0x02; // 火傷
	static constexpr uint64_t CONDITION_PARALYSIS = 0x04; // 麻痺
	static constexpr uint64_t CONDITION_SLEEP     = 0x08; // 眠り

};

// ポケモンのデータ
class PokemonData {
public:
	CString m_name; // 名前
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

