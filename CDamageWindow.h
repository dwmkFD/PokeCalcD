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
