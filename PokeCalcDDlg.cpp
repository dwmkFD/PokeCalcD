
// PokeCalcDDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "PokeCalcD.h"
#include "PokeCalcDDlg.h"
#include "afxdialogex.h"

#include "pokemon.hpp"
#include "pokemove.hpp"

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
	, m_editLv( _T( "50" ) )
	, m_editStatus( StatusKind * 3 )   // いわゆる3値なので×3
	, m_scrollStatus( StatusKind * 3 )

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
	DDX_Text( pDX, IDC_EDIT2, m_editLv );
	DDX_Text( pDX, IDC_EDIT3, m_editStatus[0] );
	DDX_Text( pDX, IDC_EDIT4, m_editStatus[1] );
	DDX_Text( pDX, IDC_EDIT5, m_editStatus[2] );
	DDX_Text( pDX, IDC_EDIT6, m_editStatus[3] );
	DDX_Text( pDX, IDC_EDIT7, m_editStatus[4] );
	DDX_Text( pDX, IDC_EDIT8, m_editStatus[5] );

	DDX_Text( pDX, IDC_EDIT9, m_editStatus[6] );
	DDX_Text( pDX, IDC_EDIT10, m_editStatus[7] );
	DDX_Text( pDX, IDC_EDIT11, m_editStatus[8] );
	DDX_Text( pDX, IDC_EDIT12, m_editStatus[9] );
	DDX_Text( pDX, IDC_EDIT13, m_editStatus[10] );
	DDX_Text( pDX, IDC_EDIT14, m_editStatus[11] );

	DDX_Text( pDX, IDC_EDIT15, m_editStatus[12] );
	DDX_Text( pDX, IDC_EDIT16, m_editStatus[13] );
	DDX_Text( pDX, IDC_EDIT17, m_editStatus[14] );
	DDX_Text( pDX, IDC_EDIT18, m_editStatus[15] );
	DDX_Text( pDX, IDC_EDIT19, m_editStatus[16] );
	DDX_Text( pDX, IDC_EDIT20, m_editStatus[17] );

	DDX_Control( pDX, IDC_SCROLLBAR1, m_scrollStatus[0] );
	DDX_Control( pDX, IDC_SCROLLBAR2, m_scrollStatus[1] );
	DDX_Control( pDX, IDC_SCROLLBAR3, m_scrollStatus[2] );
	DDX_Control( pDX, IDC_SCROLLBAR4, m_scrollStatus[3] );
	DDX_Control( pDX, IDC_SCROLLBAR5, m_scrollStatus[4] );
	DDX_Control( pDX, IDC_SCROLLBAR6, m_scrollStatus[5] );

	DDX_Control( pDX, IDC_SCROLLBAR7, m_scrollStatus[6] );
	DDX_Control( pDX, IDC_SCROLLBAR8, m_scrollStatus[7] );
	DDX_Control( pDX, IDC_SCROLLBAR9, m_scrollStatus[8] );
	DDX_Control( pDX, IDC_SCROLLBAR10, m_scrollStatus[9] );
	DDX_Control( pDX, IDC_SCROLLBAR11, m_scrollStatus[10] );
	DDX_Control( pDX, IDC_SCROLLBAR12, m_scrollStatus[11] );

	DDX_Control( pDX, IDC_SCROLLBAR13, m_scrollStatus[12] );
	DDX_Control( pDX, IDC_SCROLLBAR14, m_scrollStatus[13] );
	DDX_Control( pDX, IDC_SCROLLBAR15, m_scrollStatus[14] );
	DDX_Control( pDX, IDC_SCROLLBAR16, m_scrollStatus[15] );
	DDX_Control( pDX, IDC_SCROLLBAR17, m_scrollStatus[16] );
	DDX_Control( pDX, IDC_SCROLLBAR18, m_scrollStatus[17] );

	DDX_Radio( pDX, IDC_RADIO1, m_radioBattle );
	DDX_Radio( pDX, IDC_RADIO3, m_radioWeather );
	DDX_Radio( pDX, IDC_RADIO8, m_radioField );

	DDX_Check( pDX, IDC_CHECK1, m_checkGravity );
	DDX_Check( pDX, IDC_CHECK2, m_checkWonderRoom );
	DDX_Check( pDX, IDC_CHECK3, m_checkPlasmaShower );
	DDX_Check( pDX, IDC_CHECK4, m_checkFairyAura );
	DDX_Check( pDX, IDC_CHECK5, m_checkDarkAura );
	DDX_Check( pDX, IDC_CHECK6, m_checkAuraBreak );

	DDX_Check( pDX, IDC_CHECK7, m_checkReflecter );
	DDX_Check( pDX, IDC_CHECK8, m_checkLightScreen );
	DDX_Check( pDX, IDC_CHECK9, m_checkHelpingHand );
	DDX_Check( pDX, IDC_CHECK10, m_checkKiaidame );
	DDX_Check( pDX, IDC_CHECK11, m_checkJuden );
	DDX_Check( pDX, IDC_CHECK12, m_checkHaganenoseisin );
}

BEGIN_MESSAGE_MAP( CPokeCalcDDlg, CDialogEx )
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE( BN_CLICKED, IDC_RADIO1, IDC_RADIO12, &CPokeCalcDDlg::OnBnClickedRadioBase )
	ON_NOTIFY( NM_THEMECHANGED, IDC_SCROLLBAR1, &CPokeCalcDDlg::OnNMThemeChangedScrollbar )

	ON_CONTROL_RANGE( BN_CLICKED, IDC_BUTTON1, IDC_BUTTON48, &CPokeCalcDDlg::OnBnClickedStatusButton )
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

	// 個体値と努力値の初期値を入れておく
	for ( int i = 0; i < StatusKind; ++i )
	{
		m_editStatus[i + StatusKind] = _T( "31" );
		m_editStatus[i + StatusKind * 2] = _T( "0" );
	}
	UpdateData( FALSE ); // 画面側に反映させる

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


// 値チェックと補正
void CPokeCalcDDlg::AllEditCheck()
{
	// レベルチェック 1 ～ 100
	int lv = _tcstol( m_editLv, nullptr, 10 );
	lv = std::clamp( lv, 1, 100 );
	m_editLv.Format( _T( "%d" ), lv );

	for ( int i = 0; i < StatusKind; ++i )
	{
		// 個体値チェック 0 ～ 31
		int ind = _tcstol( m_editStatus[StatusKind + i], nullptr, 10 );
		ind = std::clamp( ind, 0, 31 );
		m_editStatus[StatusKind + i].Format( _T( "%d" ), ind );

		// 努力値チェック 0 ～ 252
		int eff = _tcstol( m_editStatus[StatusKind * 2 + i], nullptr, 10 );
		eff = std::clamp( eff, 0, 252 );
		m_editStatus[StatusKind * 2 + i].Format( _T( "%d" ), eff );
	}
}

void CPokeCalcDDlg::AllCalcStatus()
{
}

// ラジオボタン制御のベース関数
void CPokeCalcDDlg::OnBnClickedRadioBase( UINT id )
{
	UpdateData( TRUE );
}

void CPokeCalcDDlg::OnNMThemeChangedScrollbar( NMHDR *pNMHDR, LRESULT *pResult )
{
	// この機能は Windows XP それ以降のバージョンを必要とします。
	// シンボル _WIN32_WINNT は >= 0x0501にならなければなりません。
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData( TRUE );

	*pResult = 0;
	if ( pNMHDR->code == SB_LINEUP )
	{
		// 上ボタンが押された時
		UINT_PTR id = pNMHDR->idFrom - IDC_SCROLLBAR1;
		unsigned int val = _tcstol( m_editStatus[id], nullptr, 10 );
		++val;
		m_editStatus[id].Format( _T( "%d" ), val );
	}
	else if ( pNMHDR->code == SB_LINEDOWN )
	{
		// 下ボタンが押された時
		UINT_PTR id = pNMHDR->idFrom - IDC_SCROLLBAR1;
		unsigned int val = _tcstol( m_editStatus[id], nullptr, 10 );
		--val;
		m_editStatus[id].Format( _T( "%d" ), val );
	}
	else
	{
		// それ以外のイベントは処理しない
		return;
	}

	UpdateData( FALSE );

	AllEditCheck(); // 入力結果が怪しい場合は補正する
	AllCalcStatus(); // ステータスを再計算

	UpdateData( FALSE );
}


void CPokeCalcDDlg::OnBnClickedStatusButton( UINT id )
{
	UpdateData( TRUE );

	// id(つまり押されたボタン)によって振り分ける
	int inputId = id - IDC_BUTTON1;

	auto update = [&]( int idx, int input ) {
		int val = _tcstol( m_editStatus[idx], nullptr, 10 );
		val += input;
		m_editStatus[idx].Format( _T( "%d" ), val );
	};

	if ( inputId < 12 )	// 最初の12個はステータスの実数値を増減する(けど、実質努力値ボタンと一緒の扱いになると思う)

	{
		if ( inputId % 2 )
		{
			// 奇数番目は + ボタン
			update( StatusKind * 2 + inputId / 2, 1 ); // 努力値を修正 -> Lvによって1増えるのに必要な努力値が違うので注意！（あとで直す！！！）
			UpdateData( FALSE );

			AllCalcStatus(); // ステータスを再計算
		}
		else
		{
			// 偶数番目は - ボタン
			update( StatusKind * 2 + inputId / 2, -1 );
			UpdateData( FALSE );

			AllCalcStatus(); // ステータスを再計算
		}
	}
	else if ( inputId < 18 ) // 次の6個は努力値の数値を0/252で切り替える
	{
		int val = _tcstol( m_editStatus[inputId], nullptr, 10 );
		if ( val != 252 ) { val = 252; } // 252じゃない時は問答無用で252にする
		else { val = 0; }
		m_editStatus[inputId].Format( _T( "%d" ), val );
		UpdateData( FALSE );

		AllCalcStatus(); // ここで入力がおかしくなることは無いので、そのままステータスを再計算する（努力値溢れは警告だけして受け入れる）
	}
	else if ( inputId < 28 ) // 次の10個は性格補正
	{
	}
	else if ( inputId < 38 ) // 次の10個はランク補正
	{
	}
	else if ( inputId < 48 ) // 次の10個は特性補正
	{
		// 自分で入れておいてアレだけど、特性補正ってなんだ？
		// ランク変化じゃない、古代活性とかそういうやつかな…？
		// 総大将みたいに、値が変わるパターンがあるから、一律1.3倍みたいなことはできないか…。
		// ↑特性欄を選んだ時点で、上下する値が固定の子たちは自動的に入れてあげたいね
	}
	else
	{
		// 不正なIDの時は何もしない
	}

	UpdateData( FALSE );
}
