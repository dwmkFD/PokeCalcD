
// PokeCalcDDlg.h : ヘッダー ファイル
//

#pragma once

#include <afxdb.h>

#include <vector>
#include <map>
#include <memory>

#include "CPokeDataDlg.h"
#include "CComplDataDlg.h"

#include "util.hpp"
#include "pokemon.hpp"
#include "damage.hpp"


// メッセージID定義(自動ではやってくれないみたい…)
#define PCD_STATUS_RECALCULATE ( WM_USER + 1 )
#define PCD_STATUS_ADDNAMECHAR ( PCD_STATUS_RECALCULATE + 1 )
#define PCD_DAMAGECALC_REQUEST ( PCD_STATUS_ADDNAMECHAR + 1 )


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
	CPokeDataDlg m_dlgPokeData[2];

protected:
	CDatabase m_database; // データベース

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


public:
	CDatabase *getDatabase() { return ( &m_database ); } // 子ダイアログでデータベースを参照する時用
	afx_msg void OnBnClickedRadioBase( UINT id );
	virtual BOOL PreTranslateMessage( MSG *pMsg );
protected:
	afx_msg LRESULT OnPcdStatusRecalculate( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnPcdAddNameChar( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnPcdDamageCalcRequest( WPARAM wParam, LPARAM lParam );
};
