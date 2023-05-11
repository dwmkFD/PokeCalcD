// CComplDataDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "PokeCalcD.h"
#include "PokeCalcDDlg.h"
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


BOOL CComplDataDlg::PreTranslateMessage( MSG *pMsg )
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
	CString strName;
	switch ( pMsg->message )
	{
		case WM_KEYDOWN:
		{
			switch ( pMsg->wParam )
			{
				case VK_RETURN:
				{
					// Returnキーが入力されたら、カーソル位置にあるポケモンの名前を親ウィンドウ側に送る
					m_lboxComplName.GetText( m_lboxComplName.GetCurSel(), strName );
					GetParent()->GetDlgItem( IDC_EDIT1 )->SetWindowText( strName );
					GetParent()->SendMessage( PCD_STATUS_RECALCULATE );
				}
				break;

				case VK_ESCAPE:
					return ( FALSE );

				default:
				{
					if ( pMsg->wParam >= 'A' && pMsg->wParam <= 'Z' )
					{
						// アルファベットの入力なら、このダイアログを消してフォーカスを親ウィンドウに戻したい
						GetParent()->GetDlgItem( IDC_EDIT1 )->GetWindowText( strName );
						strName.AppendChar( _totlower( pMsg->wParam ) );
						GetParent()->GetDlgItem( IDC_EDIT1 )->SetWindowText( strName );
						clearListBox();
					}
				}
				break;
			}
		}
		break;

		default: break;
	}

	return CDialogEx::PreTranslateMessage( pMsg );
}


BEGIN_MESSAGE_MAP(CComplDataDlg, CDialogEx)
	ON_WM_KILLFOCUS()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



void CComplDataDlg::setListBox( std::vector<CString> nameList )
{
	for ( auto &&name : nameList )
	{
		m_lboxComplName.AddString( name );
	}
}

void CComplDataDlg::clearListBox()
{
	for ( int i = 0; i < m_lboxComplName.GetCount(); ++i )
	{
		m_lboxComplName.DeleteString( 0 );
	}
}

// CComplDataDlg メッセージ ハンドラー


void CComplDataDlg::OnKillFocus( CWnd *pNewWnd )
{
	CDialogEx::OnKillFocus( pNewWnd );

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	// フォーカスを失ったらダイアログを非表示にする
	ShowWindow( SW_HIDE );
}


void CComplDataDlg::OnShowWindow( BOOL bShow, UINT nStatus )
{
	CDialogEx::OnShowWindow( bShow, nStatus );

	// TODO: ここにメッセージ ハンドラー コードを追加します。

	// ウィンドウが非表示になった時はリストの中身をクリアする
	if ( bShow == SW_HIDE )
	{
		clearListBox();
	}
}
