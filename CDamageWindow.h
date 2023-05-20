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
	std::vector<CImage> m_img; // 画像の個数は決まってるので決め打ちの方が良い？(全18タイプ、テラスタイプ、ゲージの色）

	// ゲージの色
	static constexpr unsigned int IMAGENAME_GAUGE_GRAY = 36;
	static constexpr unsigned int IMAGENAME_GAUGE_RED = 37;
	static constexpr unsigned int IMAGENAME_GAUGE_RED_RANDOM = 38;
	static constexpr unsigned int IMAGENAME_GAUGE_YELLOW = 39;
	static constexpr unsigned int IMAGENAME_GAUGE_YELLOW_RANDOM = 40;
	static constexpr unsigned int IMAGENAME_GAUGE_GREEN = 41;
	static constexpr unsigned int IMAGENAME_GAUGE_GREEN_RANDOM = 42;

	int m_defHP; // ダメージを与える相手の最大HP実数値
	std::vector<std::pair<CString, std::vector<int>>> m_printData; // 描画する計算結果
	// ↓これ要らなさそう
	std::vector<CStatic> m_picType;       // 技のタイプを示すアイコン
	std::vector<CStatic> m_strMove;       // 技名
	std::vector<CStatic> m_picDamage;     // ダメージゲージのベース部分（灰色固定？）
	std::vector<CStatic> m_picRemain;     // 残りHP部分（緑だったり黄色だったり赤だったり、確1なら無し）
	std::vector<CStatic> m_picDamageRand; // ダメージの乱数でブレる部分(色は残りHP側に合わせた薄い色、確1なら無し)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	void setDatabase( CDatabase *db ) { m_database = db; }
	void setScrollInfo( unsigned int size );
	void setDamageInfo( std::map<CString, std::vector<int>> &damage, int defHP ); // ダメージ情報を設定する
	void printDamage( UINT startPos ); // ダメージゲージを描画する

	CScrollBar m_scrollDamage;
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar );
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	afx_msg void OnPaint();
};
