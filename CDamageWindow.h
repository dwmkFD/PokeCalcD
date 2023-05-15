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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	void setDatabase( CDatabase *db ) { m_database = db; }
	void printDamage( std::map<CString, std::vector<int>> damage ); // ダメージゲージを描画する

	CScrollBar m_scrollDamage;
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar );
	virtual BOOL OnInitDialog();
};
