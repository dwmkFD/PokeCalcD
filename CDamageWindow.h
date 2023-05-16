#pragma once

#include <afxdb.h>

#include <vector>
#include <map>
#include <memory>

#include <algorithm>

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

	// 画像の種類分だけインデックスを定義
	static constexpr unsigned int IMAGENAME_TYPE_NORMAL = 0;
	static constexpr unsigned int IMAGENAME_TYPE_FLARE = 1;
	static constexpr unsigned int IMAGENAME_TYPE_WATER = 2;
	static constexpr unsigned int IMAGENAME_TYPE_ELECTRIC = 3;
	static constexpr unsigned int IMAGENAME_TYPE_GRASS = 4;
	static constexpr unsigned int IMAGENAME_TYPE_ICE = 5;
	static constexpr unsigned int IMAGENAME_TYPE_FIGHTING = 6;
	static constexpr unsigned int IMAGENAME_TYPE_POISON = 7;
	static constexpr unsigned int IMAGENAME_TYPE_GROUND = 8;
	static constexpr unsigned int IMAGENAME_TYPE_FLYING = 9;
	static constexpr unsigned int IMAGENAME_TYPE_PSYCHIC = 10;
	static constexpr unsigned int IMAGENAME_TYPE_BUG = 11;
	static constexpr unsigned int IMAGENAME_TYPE_ROCK = 12;
	static constexpr unsigned int IMAGENAME_TYPE_GHOST = 13;
	static constexpr unsigned int IMAGENAME_TYPE_DRAGON = 14;
	static constexpr unsigned int IMAGENAME_TYPE_DARK = 15;
	static constexpr unsigned int IMAGENAME_TYPE_STEEL = 16;
	static constexpr unsigned int IMAGENAME_TYPE_FAIRY = 17;

	// テラスタイプ用
	static constexpr unsigned int IMAGENAME_TYPE_NORMAL_TERA = 18;
	static constexpr unsigned int IMAGENAME_TYPE_FLARE_TERA = 19;
	static constexpr unsigned int IMAGENAME_TYPE_WATER_TERA = 20;
	static constexpr unsigned int IMAGENAME_TYPE_ELECTRIC_TERA = 21;
	static constexpr unsigned int IMAGENAME_TYPE_GRASS_TERA = 22;
	static constexpr unsigned int IMAGENAME_TYPE_ICE_TERA = 23;
	static constexpr unsigned int IMAGENAME_TYPE_FIGHTING_TERA = 24;
	static constexpr unsigned int IMAGENAME_TYPE_POISON_TERA = 25;
	static constexpr unsigned int IMAGENAME_TYPE_GROUND_TERA = 26;
	static constexpr unsigned int IMAGENAME_TYPE_FLYING_TERA = 27;
	static constexpr unsigned int IMAGENAME_TYPE_PSYCHIC_TERA = 28;
	static constexpr unsigned int IMAGENAME_TYPE_BUG_TERA = 29;
	static constexpr unsigned int IMAGENAME_TYPE_ROCK_TERA = 30;
	static constexpr unsigned int IMAGENAME_TYPE_GHOST_TERA = 31;
	static constexpr unsigned int IMAGENAME_TYPE_DRAGON_TERA = 32;
	static constexpr unsigned int IMAGENAME_TYPE_DARK_TERA = 33;
	static constexpr unsigned int IMAGENAME_TYPE_STEEL_TERA = 34;
	static constexpr unsigned int IMAGENAME_TYPE_FAIRY_TERA = 35;

	// ゲージの色
	static constexpr unsigned int IMAGENAME_GAUGE_GRAY = 36;
	static constexpr unsigned int IMAGENAME_GAUGE_RED = 37;
	static constexpr unsigned int IMAGENAME_GAUGE_RED_RANDOM = 38;
	static constexpr unsigned int IMAGENAME_GAUGE_YELLOW = 39;
	static constexpr unsigned int IMAGENAME_GAUGE_YELLOW_RANDOM = 40;
	static constexpr unsigned int IMAGENAME_GAUGE_GREEN = 41;
	static constexpr unsigned int IMAGENAME_GAUGE_GREEN_RANDOM = 42;

	std::vector<std::pair<CString, std::vector<int>>> m_printData; // 描画する計算結果
	std::vector<CStatic> m_picType;       // 技のタイプを示すアイコン
	std::vector<CStatic> m_strMove;       // 技名
	std::vector<CStatic> m_picDamage;     // ダメージゲージのベース部分（灰色？）
	std::vector<CStatic> m_picRemain;     // 残りHP部分（緑だったり黄色だったり赤だったり、確1なら無し）
	std::vector<CStatic> m_picDamageRand; // ダメージの乱数でブレる部分(色は残りHP側に合わせた薄い色、確1なら無し)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	void setDatabase( CDatabase *db ) { m_database = db; }
	void setScrollInfo( unsigned int size );
	void setDamageInfo( std::map<CString, std::vector<int>> &damage ); // ダメージ情報を設定する
	void printDamage( UINT startPos ); // ダメージゲージを描画する

	CScrollBar m_scrollDamage;
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar );
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
};
