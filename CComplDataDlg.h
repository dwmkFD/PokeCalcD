#pragma once

#include <Windows.h>
#include <afxstr.h>

#include <vector>

// CComplDataDlg ダイアログ

class CComplDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CComplDataDlg)

public:
	CComplDataDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CComplDataDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POPUP_COMPLDATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

public:
	void setListBox( std::vector<CString> nameList ); // リストボックスに補完したポケモン名を設定する
	void clearListBox(); // リストボックスをクリアする
	void selSideSet( bool side ) {
		m_side = side;
	}

	afx_msg void OnKillFocus( CWnd *pNewWnd );
	virtual BOOL PreTranslateMessage( MSG *pMsg );
	afx_msg void OnShowWindow( BOOL bShow, UINT nStatus );

protected:

	DECLARE_MESSAGE_MAP()

private:
	bool m_side; // trueならポケモン1、falseならポケモン2の名前を補完する
	CListBox m_lboxComplName; // 補完用リストボックス
};
