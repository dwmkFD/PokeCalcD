
// PokeCalcDDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "PokeCalcD.h"
#include "PokeCalcDDlg.h"
#include "afxdialogex.h"


#include "util.hpp"
#include "pokemon.hpp"
#include "pokemove.hpp"
#include "damage.hpp"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPokeCalcDDlg ダイアログ



CPokeCalcDDlg::CPokeCalcDDlg( CWnd *pParent /*=nullptr*/ )
	: CDialogEx( IDD_POKECALCD_DIALOG, pParent )
	, m_radioBattle( 0 )
	, m_radioWeather( 0 )
	, m_radioField( 0 )

	, m_checkGravity( FALSE )
	, m_checkWonderRoom( FALSE )
	, m_checkPlasmaShower( FALSE )
	, m_checkFairyAura( FALSE )
	, m_checkDarkAura( FALSE )
	, m_checkAuraBreak( FALSE )

	, m_checkReflecter( FALSE )
	, m_checkLightScreen( FALSE )
	, m_checkHelpingHand( FALSE )
	, m_checkKiaidame( FALSE )
	, m_checkJuden( FALSE )
	, m_checkHaganenoseisin( FALSE )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPokeCalcDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );

	DDX_Radio( pDX, IDC_RADIO1, m_radioBattle );
	DDX_Radio( pDX, IDC_RADIO3, m_radioWeather );
	DDX_Radio( pDX, IDC_RADIO8, m_radioField );

	DDX_Check( pDX, IDC_CHECK1, m_checkGravity );
	DDX_Check( pDX, IDC_CHECK2, m_checkWonderRoom );
	DDX_Check( pDX, IDC_CHECK3, m_checkPlasmaShower );
	DDX_Check( pDX, IDC_CHECK4, m_checkFairyAura );
	DDX_Check( pDX, IDC_CHECK5, m_checkDarkAura );
	DDX_Check( pDX, IDC_CHECK6, m_checkAuraBreak );

}

BEGIN_MESSAGE_MAP( CPokeCalcDDlg, CDialogEx )
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE( BN_CLICKED, IDC_RADIO1, IDC_RADIO12, &CPokeCalcDDlg::OnBnClickedRadioBase )
	ON_MESSAGE( PCD_STATUS_RECALCULATE, &CPokeCalcDDlg::OnPcdStatusRecalculate )
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CPokeCalcDDlg メッセージ ハンドラー

BOOL CPokeCalcDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	// データベース接続
	CString strConnection = _T( "Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=.\\PokeData.accdb;UID=;Pwd=" );
	m_database.OpenEx( strConnection, CDatabase::openReadOnly | CDatabase::noOdbcDialog );

	m_dlgPokeData[0].Create( IDD_POKEMON_DIALOG1, this ); // ポケモン1
	m_dlgPokeData[1].Create( IDD_POKEMON_DIALOG1, this ); // ポケモン2

	CRect rect;
	GetDlgItem( IDC_STATIC_GROUP_POKEMON1 )->GetWindowRect( rect );
	rect.left -= 7;
	rect.top -= 10;
	rect.right -= 15;
	rect.bottom -= 15;
	m_dlgPokeData[0].MoveWindow( rect );

	GetDlgItem( IDC_STATIC_GROUP_POKEMON2 )->GetWindowRect( rect );
	rect.left -= 7;
	rect.top -= 10;
	rect.right -= 15;
	rect.bottom -= 15;
	m_dlgPokeData[1].MoveWindow( rect );

	for ( int i = 0; i < 2; ++i )
	{
		m_dlgPokeData[i].ShowWindow( SW_SHOW );
		m_dlgPokeData[i].setDatabase( &m_database );
		m_dlgPokeData[i].setID( i );
	}

	// ダメージ計算クラス初期化
	m_damage.reset( new CCalcDamage( &m_database ) );

	// ポケモン1側のポケモン名を入力するエディットボックスにフォーカスを合わせる
	m_dlgPokeData[0].GetDlgItem( IDC_EDIT1 )->SetFocus();
	return ( FALSE );

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CPokeCalcDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CPokeCalcDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CPokeCalcDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CPokeCalcDDlg::PreTranslateMessage( MSG *pMsg )
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
	switch ( pMsg->message )
	{
		case WM_KEYDOWN:
		{
			switch ( pMsg->wParam )
			{
				case VK_RETURN:
				case VK_ESCAPE:
					return ( FALSE );
			}
		}
		break;

		default: break;
	}

	return CDialogEx::PreTranslateMessage( pMsg );
}


// ラジオボタン制御のベース関数
void CPokeCalcDDlg::OnBnClickedRadioBase( UINT id )
{
	UpdateData( TRUE );
}


// ステータス再計算要求
afx_msg LRESULT CPokeCalcDDlg::OnPcdStatusRecalculate( WPARAM wParam, LPARAM lParam )
{
	// wParam: ID, LPARAM: セットするテキスト
	int id = static_cast<int>( wParam );
	CString *strName = reinterpret_cast<CString *>( lParam );

	m_dlgPokeData[id].GetDlgItem( IDC_EDIT1 )->SetWindowTextW( *strName );
	m_dlgPokeData[id].SendMessage( PCD_STATUS_RECALCULATE );

	return 0;
}

// エディットボックスに1文字追加
afx_msg LRESULT CPokeCalcDDlg::OnPcdAddNameChar( WPARAM wParam, LPARAM lParam )
{
	// wParam: ID, LPARAM: セットする文字
	int id = static_cast<int>( wParam );
	CString strName;
	m_dlgPokeData[id].GetDlgItem( IDC_EDIT1 )->GetWindowText( strName );
	strName += static_cast<TCHAR>( lParam );
	m_dlgPokeData[id].GetDlgItem( IDC_EDIT1 )->SetWindowText( strName );
	m_dlgPokeData[id].GetDlgItem( IDC_EDIT1 )->SetFocus();
	static_cast<CEdit *>( m_dlgPokeData[id].GetDlgItem( IDC_EDIT1 ) )->SetSel( strName.GetLength(), strName.GetLength() );
	m_dlgPokeData[id].SendMessage( EN_SELCHANGE );

	return ( 0 );
}