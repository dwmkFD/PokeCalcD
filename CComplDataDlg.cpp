// CComplDataDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "PokeCalcD.h"
#include "CComplDataDlg.h"
#include "afxdialogex.h"


// CComplDataDlg ダイアログ

IMPLEMENT_DYNAMIC(CComplDataDlg, CDialogEx)

CComplDataDlg::CComplDataDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POPUP_COMPLDATA, pParent)
{

}

CComplDataDlg::~CComplDataDlg()
{
}

void CComplDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_LIST1, m_lboxComplName );
}


BEGIN_MESSAGE_MAP(CComplDataDlg, CDialogEx)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



void CComplDataDlg::setListBox( std::vector<CString> nameList )
{
	for ( auto &&name : nameList )
	{
		m_lboxComplName.AddString( name );
	}
}

// CComplDataDlg メッセージ ハンドラー


void CComplDataDlg::OnKillFocus( CWnd *pNewWnd )
{
	CDialogEx::OnKillFocus( pNewWnd );

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	// フォーカスを失ったらダイアログを非表示にする
	ShowWindow( SW_HIDE );

	// リストの中身をクリアする
	for ( int i = 0; i < m_lboxComplName.GetCount(); ++i )
	{
		m_lboxComplName.DeleteString( 0 );
	}
}
