﻿
// PokeCalcDDlg.h : ヘッダー ファイル
//

#pragma once

#include <afxdb.h>

#include <vector>
#include <map>
#include <memory>

#include "CPokeDataDlg.h"
#include "CComplDataDlg.h"
#include "CDamageWindow.h"

#include "util.hpp"
#include "pokemon.hpp"
#include "damage.hpp"



// CPokeCalcDDlg ダイアログ
class CPokeCalcDDlg : public CDialogEx
{
// コンストラクション
public:
	CPokeCalcDDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POKECALCD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

private:
	std::unique_ptr<CCalcDamage> m_damage; // ダメージ計算
	CPokeDataDlg m_dlgPokeData[2]; // ポケモンに関する設定ダイアログ
	CDamageWindow m_dlgDamageWindow[2]; // 計算結果表示ダイアログ

#if 0
	std::vector<std::pair<CString, std::vector<int>>> m_printData[2]; // 描画する計算結果
	int m_defHP[2]; // 攻撃を受ける側のHP実数値

	// ゲージの色
	static constexpr unsigned int IMAGENAME_GAUGE_GRAY = 36;
	static constexpr unsigned int IMAGENAME_GAUGE_RED = 37;
	static constexpr unsigned int IMAGENAME_GAUGE_RED_RANDOM = 38;
	static constexpr unsigned int IMAGENAME_GAUGE_YELLOW = 39;
	static constexpr unsigned int IMAGENAME_GAUGE_YELLOW_RANDOM = 40;
	static constexpr unsigned int IMAGENAME_GAUGE_GREEN = 41;
	static constexpr unsigned int IMAGENAME_GAUGE_GREEN_RANDOM = 42;

	//計算結果を表示する箇所のスクロールバー
	CScrollBar m_scrPokemon[2];
#endif

protected:
	CDatabase m_database; // データベース
	std::vector<CImage> m_img; // 画像の個数は決まってるので決め打ちの方が良い？(全18タイプ、テラスタイプ、ゲージの色）

protected:
	int m_radioBattle;	// シングル or ダブル
	int m_radioWeather;	// 天候
	int m_radioField;	// フィールド

	// 処理を統一するために、vectorかmapにしてindexを対応させた方がいいと思う
	BOOL m_checkGravity;		// 重力
	BOOL m_checkWonderRoom;		// ワンダールーム
	BOOL m_checkPlasmaShower;	// プラズマシャワー
	BOOL m_checkFairyAura;		// フェアリーオーラ
	BOOL m_checkDarkAura;		// ダークオーラ
	BOOL m_checkAuraBreak;		// オーラブレイク

	BOOL m_checkReflecter;		// リフレクター
	BOOL m_checkLightScreen;	// 光の壁
	BOOL m_checkHelpingHand;	// 手助け
	BOOL m_checkKiaidame;	// 気合溜め
	BOOL m_checkJuden;		// 充電
	BOOL m_checkHaganenoseisin;		// 鋼の精神


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	CDatabase *getDatabase() { return ( &m_database ); } // 子ダイアログでデータベースを参照する時用
	afx_msg void OnBnClickedRadioBase( UINT id );
	virtual BOOL PreTranslateMessage( MSG *pMsg );
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar );
protected:
	afx_msg LRESULT OnPcdStatusRecalculate( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnPcdAddNameChar( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnPcdDamageCalcRequest( WPARAM wParam, LPARAM lParam );
};
