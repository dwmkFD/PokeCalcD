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
	static constexpr unsigned int IMAGENAME_TYPE_FLARE = 0;
	/*
	static constexpr unsigned int IMAGENAME_TYPE_X = 1;
	static constexpr unsigned int IMAGENAME_TYPE_X = 2;
	static constexpr unsigned int IMAGENAME_TYPE_X = 3;
	static constexpr unsigned int IMAGENAME_TYPE_X = 4;
	static constexpr unsigned int IMAGENAME_TYPE_X = 5;
	static constexpr unsigned int IMAGENAME_TYPE_X = 6;
	static constexpr unsigned int IMAGENAME_TYPE_X = 7;
	static constexpr unsigned int IMAGENAME_TYPE_X = 8;
	static constexpr unsigned int IMAGENAME_TYPE_X = 9;
	static constexpr unsigned int IMAGENAME_TYPE_X = 10;
	static constexpr unsigned int IMAGENAME_TYPE_X = 11;
	static constexpr unsigned int IMAGENAME_TYPE_X = 12;
	static constexpr unsigned int IMAGENAME_TYPE_X = 13;
	static constexpr unsigned int IMAGENAME_TYPE_X = 14;
	static constexpr unsigned int IMAGENAME_TYPE_X = 15;
	static constexpr unsigned int IMAGENAME_TYPE_X = 16;
	static constexpr unsigned int IMAGENAME_TYPE_X = 17;
	static constexpr unsigned int IMAGENAME_TYPE_X = 18;
	*/
	// テラスタイプの場合はちょっとだけ変えた画像も用意したい…

	static constexpr unsigned int IMAGENAME_GAUGE_GRAY = 36; // テラスタイプも18種類あるので、続きから

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
