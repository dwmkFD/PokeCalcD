#pragma once

#include <afxdb.h>

#include <vector>
#include <map>
#include <memory>

#include <algorithm>

#include "poketype.hpp"
#include "pokemon.hpp"
#include "pokemove.hpp"


// CDamageWindow ダイアログ

class CDamageWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CDamageWindow)

public:
	CDamageWindow(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CDamageWindow();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAMAGE_WINDOW };
#endif

private:
	CDatabase *m_database;
	CScrollBar m_scrollDamage;
	int m_scrollPos;

	// ゲージの色
	enum {
		IMAGENAME_GAUGE_GRAY = 36,
		IMAGENAME_GAUGE_RED,
		IMAGENAME_GAUGE_RED_RANDOM,
		IMAGENAME_GAUGE_YELLOW,
		IMAGENAME_GAUGE_YELLOW_RANDOM,
		IMAGENAME_GAUGE_GREEN,
		IMAGENAME_GAUGE_GREEN_RANDOM,
		IMAGENAME_ALLIMAGE_SIZE,

	};

	int m_defHP; // ダメージを与える相手の最大HP実数値
	CString m_atkTeraType; // 攻撃側テラスタイプ
	std::vector<std::pair<CString, std::vector<int>>> m_printData; // 描画する計算結果
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	void setDatabase( CDatabase *db ) { m_database = db; }
	void setScrollSize( unsigned int size );
	void setDamageInfo( std::map<CString, std::vector<int>> &damage, int defHP ); // ダメージ情報を設定する
	void printDamage( UINT startPos ); // ダメージゲージを描画する

	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar );
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	afx_msg void OnPaint();
};
