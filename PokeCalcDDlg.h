﻿
// PokeCalcDDlg.h : ヘッダー ファイル
//

#pragma once

#include <afxdb.h>

#include <vector>
#include <map>
#include <memory>

#include "CComplDataDlg.h"

#include "util.hpp"
#include "pokemon.hpp"
#include "damage.hpp"


// メッセージID定義(自動ではやってくれないみたい…)
#define PCD_STATUS_RECALCULATE ( WM_USER + 1 )


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

protected:
	CComplDataDlg m_complDlg; // ポケモン名の補完に使うダイアログボックス

	CDatabase m_database; // データベース
	CTransrateRomaKana m_trans; // ローマ字をカタカナに変換するユーティリティ

	CEdit m_editCtrl_Name[2];	// 名前
	CString m_editValName[2];	// 名前(値型)
	CComboBox m_cmbNature;	// 性格
	CComboBox m_cmbAbility;	// 特性
	CComboBox m_cmbItem;	// 持ち物
	std::vector<CComboBox> m_cmbRank; // ランク補正

	// 実数値
	CString m_editLv;		// Lv
	std::vector<CString> m_editStatus; // HABCDSはこの順で、実数値、個体値、努力値の順に格納する
	std::vector<CScrollBar> m_scrollStatus; // エディットボックスの隣にくっついてるスクロールバー

	// 振った努力値の合計値表示
	CFont m_font;
	CStatic m_strEfftTotal[2];

	CComboBox m_cmbTeraType; // テラスタイプ
private:
	/* 初期化 */
	void initNature();      // 性格コンボボックスの初期化
	void initAbility();     // 特性コンボボックスの初期化
	void initItem();        // 持ち物コンボボックスの初期化
	void initTeraType();    // テラスタイプコンボボックスの初期化
	void initRankCorrect(); // ランク補正コンボボックスの初期化

protected:
	int m_radioBattle;	// シングル or ダブル
	int m_radioWeather;	// 天候
	int m_radioField;	// フィールド

	// 処理を統一するために、vectorかmapにしてindexを対応させた方がいいと思う
	// あと、これ全部2セット要るんだよね。。
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


private:
	bool addEffortVal( UINT id, bool isGain ); // 努力値を増減させる
	void statusCalcBase( UINT id, bool isGain ); // ステータス計算ベース関数
	void AllEditCheck(); // レベルや個体値、努力値が指定の範囲に収まっているか？をチェックし、溢れていたら丸める
	void AllCalcStatus(); // 個体値や努力値を修正された場合にステータスを再計算する
public:
	afx_msg void OnBnClickedRadioBase( UINT id );
	afx_msg void OnBnClickedStatusButton( UINT id );
	afx_msg void OnCbnSelChangeComboBox( UINT id );
	afx_msg void OnChangeEditBase( CEdit &editCtrl, CString &editVal, bool side );
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	virtual BOOL PreTranslateMessage( MSG *pMsg );
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar );
protected:
	afx_msg LRESULT OnPcdStatusRecalculate( WPARAM wParam, LPARAM lParam );
};
