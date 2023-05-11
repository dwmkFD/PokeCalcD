
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
	, m_editValName( _T( "" ) )

	, m_editLv( _T( "50" ) )
	, m_editStatus( PokemonData::StatusKind * 3 )   // いわゆる3値なので×3
	, m_scrollStatus( PokemonData::StatusKind * 3 )

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

	DDX_Control( pDX, IDC_EDIT1, m_editCtrl_Name );
	DDX_Text( pDX, IDC_EDIT1, m_editValName );

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

	DDX_Control( pDX, IDC_COMBO1, m_cmbNature );
	DDX_Control( pDX, IDC_COMBO12, m_cmbAbility );
	DDX_Control( pDX, IDC_COMBO13, m_cmbItem );
	DDX_Control( pDX, IDC_COMBO14, m_cmbTeraType );
}

BEGIN_MESSAGE_MAP( CPokeCalcDDlg, CDialogEx )
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE( BN_CLICKED, IDC_RADIO1, IDC_RADIO12, &CPokeCalcDDlg::OnBnClickedRadioBase )

	ON_CONTROL_RANGE( BN_CLICKED, IDC_BUTTON1, IDC_BUTTON48, &CPokeCalcDDlg::OnBnClickedStatusButton )
	ON_EN_CHANGE( IDC_EDIT1, &CPokeCalcDDlg::OnChangeEdit1 )
	ON_CBN_SELCHANGE( IDC_COMBO1, &CPokeCalcDDlg::OnCbnSelchangeCombo )
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
	m_complDlg.Create( IDD_POPUP_COMPLDATA, this ); // 補完ダイアログボックスを初期化する

	initNature();	// 性格コンボボックスを初期化して「頑張り屋」を選んでおく
	initAbility();	// 特性コンボボックスを初期化
	initItem();		// 持ち物コンボボックスを初期化
	initTeraType(); // テラスタイプコンボボックスを初期化

	// データベース接続
	CString strConnection = _T( "Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=.\\PokeData.accdb;UID=;Pwd=" );
	m_database.OpenEx( strConnection, CDatabase::openReadOnly | CDatabase::noOdbcDialog );

	// ダメージ計算クラス初期化
	m_damage.reset( new CCalcDamage( &m_database ) );

	// 個体値と努力値の初期値を入れておく
	for ( int i = 0; i < PokemonData::StatusKind; ++i )
	{
		m_editStatus[i + PokemonData::StatusKind] = _T( "31" );
		m_editStatus[i + PokemonData::StatusKind * 2] = _T( "0" );
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


/* 初期化系 */
// 性格コンボボックスの初期化
void CPokeCalcDDlg::initNature()
{
	m_cmbNature.AddString( _T( "さみしがり A+ B-" ) );
	m_cmbNature.AddString( _T( "いじっぱり A+ C-" ) );
	m_cmbNature.AddString( _T( "やんちゃ A+ D-" ) );
	m_cmbNature.AddString( _T( "ゆうかん A+ S-" ) );
	m_cmbNature.AddString( _T( "ずぶとい B+ A-" ) );
	m_cmbNature.AddString( _T( "わんぱく B+ C-" ) );
	m_cmbNature.AddString( _T( "のうてんき B+ D-" ) );
	m_cmbNature.AddString( _T( "のんき B+ S-" ) );
	m_cmbNature.AddString( _T( "ひかえめ C+ A-" ) );
	m_cmbNature.AddString( _T( "おっとり C+ B-" ) );
	m_cmbNature.AddString( _T( "うっかりや C+ D-" ) );
	m_cmbNature.AddString( _T( "れいせい C+ S-" ) );
	m_cmbNature.AddString( _T( "おだやか D+ A-" ) );
	m_cmbNature.AddString( _T( "おとなしい D+ B-" ) );
	m_cmbNature.AddString( _T( "しんちょう D+ C-" ) );
	m_cmbNature.AddString( _T( "なまいき D+ S-" ) );
	m_cmbNature.AddString( _T( "おくびょう S+ A-" ) );
	m_cmbNature.AddString( _T( "せっかち S+ B-" ) );
	m_cmbNature.AddString( _T( "ようき S+ C-" ) );
	m_cmbNature.AddString( _T( "むじゃき S+ D-" ) );
	m_cmbNature.AddString( _T( "がんばりや" ) );
	m_cmbNature.AddString( _T( "すなお" ) );
	m_cmbNature.AddString( _T( "まじめ" ) );
	m_cmbNature.AddString( _T( "てれや" ) );
	m_cmbNature.AddString( _T( "きまぐれ" ) );

	m_cmbNature.SetCurSel( 20 ); // がんばり屋にしておく
}

// 特性コンボボックスの初期化
void CPokeCalcDDlg::initAbility()
{
	m_cmbAbility.AddString( _T( "(未発動)" ) );
	m_cmbAbility.SetCurSel( 0 );
}

// 持ち物コンボボックスの初期化
void CPokeCalcDDlg::initItem()
{
	m_cmbItem.AddString( _T( "(未発動)" ) );
	m_cmbItem.AddString( _T( "(攻撃系)" ) );
	m_cmbItem.AddString( _T( "タイプ強化" ) );
	m_cmbItem.AddString( _T( "ノーマルジュエル" ) );
	m_cmbItem.AddString( _T( "いのちのたま" ) );
	m_cmbItem.AddString( _T( "こころのしずく" ) );
	m_cmbItem.AddString( _T( "こだわりハチマキ" ) );
	m_cmbItem.AddString( _T( "こだわりメガネ" ) );
	m_cmbItem.AddString( _T( "こんごうだま" ) );
	m_cmbItem.AddString( _T( "しらたま" ) );
	m_cmbItem.AddString( _T( "しんかいのキバ" ) );
	m_cmbItem.AddString( _T( "するどいツメ" ) );
	m_cmbItem.AddString( _T( "たつじんのおび" ) );
	m_cmbItem.AddString( _T( "ちからのハチマキ" ) );
	m_cmbItem.AddString( _T( "でんきだま" ) );
	m_cmbItem.AddString( _T( "ながねぎ" ) );
	m_cmbItem.AddString( _T( "はっきんだま" ) );
	m_cmbItem.AddString( _T( "ピントレンズ" ) );
	m_cmbItem.AddString( _T( "ふといホネ" ) );
	m_cmbItem.AddString( _T( "メトロノーム(1回目)" ) );
	m_cmbItem.AddString( _T( "メトロノーム(2回目)" ) );
	m_cmbItem.AddString( _T( "メトロノーム(3回目)" ) );
	m_cmbItem.AddString( _T( "メトロノーム(4回目)" ) );
	m_cmbItem.AddString( _T( "メトロノーム(5回目)" ) );
	m_cmbItem.AddString( _T( "メトロノーム(6回目以降)" ) );
	m_cmbItem.AddString( _T( "ものしりメガネ" ) );
	m_cmbItem.AddString( _T( "ラッキーパンチ" ) );
	m_cmbItem.AddString( _T( "(防御系)" ) );
	m_cmbItem.AddString( _T( "半減木の実" ) );
	m_cmbItem.AddString( _T( "くろいてっきゅう" ) );
	m_cmbItem.AddString( _T( "しんかいのウロコ" ) );
	m_cmbItem.AddString( _T( "しんかのきせき" ) );
	m_cmbItem.AddString( _T( "とつげきチョッキ" ) );
	m_cmbItem.AddString( _T( "メタルパウダー" ) );
	m_cmbAbility.SetCurSel( 0 );
}

void CPokeCalcDDlg::initTeraType()
{
	m_cmbTeraType.AddString( _T( "テラスタイプ" ) );
	m_cmbTeraType.AddString( _T( "ノーマル" ) );
	m_cmbTeraType.AddString( _T( "ほのお" ) );
	m_cmbTeraType.AddString( _T( "みず" ) );
	m_cmbTeraType.AddString( _T( "でんき" ) );
	m_cmbTeraType.AddString( _T( "くさ" ) );
	m_cmbTeraType.AddString( _T( "こおり" ) );
	m_cmbTeraType.AddString( _T( "かくとう" ) );
	m_cmbTeraType.AddString( _T( "どく" ) );
	m_cmbTeraType.AddString( _T( "じめん" ) );
	m_cmbTeraType.AddString( _T( "ひこう" ) );
	m_cmbTeraType.AddString( _T( "エスパー" ) );
	m_cmbTeraType.AddString( _T( "むし" ) );
	m_cmbTeraType.AddString( _T( "いわ" ) );
	m_cmbTeraType.AddString( _T( "ゴースト" ) );
	m_cmbTeraType.AddString( _T( "ドラゴン" ) );
	m_cmbTeraType.AddString( _T( "あく" ) );
	m_cmbTeraType.AddString( _T( "はがね" ) );
	m_cmbTeraType.AddString( _T( "フェアリー" ) );
	m_cmbTeraType.SetCurSel( 0 );
}

// 値チェックと補正
void CPokeCalcDDlg::AllEditCheck()
{
	// レベルチェック 1 ～ 100
	int lv = _tcstol( m_editLv, nullptr, 10 );
	lv = std::clamp( lv, 1, 100 );
	m_editLv.Format( _T( "%d" ), lv );

	for ( int i = 0; i < PokemonData::StatusKind; ++i )
	{
		// 個体値チェック 0 ～ 31
		int ind = _tcstol( m_editStatus[PokemonData::StatusKind + i], nullptr, 10 );
		ind = std::clamp( ind, 0, 31 );
		m_editStatus[PokemonData::StatusKind + i].Format( _T( "%d" ), ind );

		// 努力値チェック 0 ～ 252
		int eff = _tcstol( m_editStatus[PokemonData::StatusKind * 2 + i], nullptr, 10 );
		eff = std::clamp( eff, 0, 252 );
		m_editStatus[PokemonData::StatusKind * 2 + i].Format( _T( "%d" ), eff );
	}
}

void CPokeCalcDDlg::AllCalcStatus()
{
	// 種族値も必要だがどうやって持ってくる…？
	// -> m_editStatusの4つ目に入れておく？
	//    -> 1匹2匹程度なら、毎回データベースから拾ってきても良いかも
	CRecordset rs( &m_database );
	CString strSQL;
	strSQL.Format( _T( "SELECT * FROM pokemon WHERE 名前='%s'" ), m_editValName );
	auto res = rs.Open( CRecordset::forwardOnly, strSQL );
	short nFields = rs.GetODBCFieldCount();

	// ステータス計算式：
	// HPの場合：(種族値×2+個体値+努力値÷4)×レベル÷100+レベル+10
	// それ以外：{(種族値×2+個体値+努力値÷4)×レベル÷100+5}×せいかく補正

	try {
		for ( int i = 4; i < 10; ++i ) // 何番目のフィールドかはデータベース見て直値で入れておく（本当は良くないけど…）
		{
			CString strValue;
			rs.GetFieldValue( i, strValue );
			m_editStatus[i - 4] = strValue; // 実数値には、まず種族値をそのまま入力する
		}

		int lv = _tcstol( m_editLv, nullptr, 10 );
		std::vector<int> status = {
			// 種族値
			_tcstol( m_editStatus[PokemonData::HP_Index], nullptr, 10 ),
			_tcstol( m_editStatus[PokemonData::Attack_Index], nullptr, 10 ),
			_tcstol( m_editStatus[PokemonData::Block_Index], nullptr, 10 ),
			_tcstol( m_editStatus[PokemonData::Contact_Index], nullptr, 10 ),
			_tcstol( m_editStatus[PokemonData::Diffence_Index], nullptr, 10 ),
			_tcstol( m_editStatus[PokemonData::Speed_Index], nullptr, 10 ),
			// 個体値
			_tcstol( m_editStatus[6 + PokemonData::HP_Index], nullptr, 10 ),
			_tcstol( m_editStatus[6 + PokemonData::Attack_Index], nullptr, 10 ),
			_tcstol( m_editStatus[6 + PokemonData::Block_Index], nullptr, 10 ),
			_tcstol( m_editStatus[6 + PokemonData::Contact_Index], nullptr, 10 ),
			_tcstol( m_editStatus[6 + PokemonData::Diffence_Index], nullptr, 10 ),
			_tcstol( m_editStatus[6 + PokemonData::Speed_Index], nullptr, 10 ),
			// 努力値
			_tcstol( m_editStatus[12 + PokemonData::HP_Index], nullptr, 10 ),
			_tcstol( m_editStatus[12 + PokemonData::Attack_Index], nullptr, 10 ),
			_tcstol( m_editStatus[12 + PokemonData::Block_Index], nullptr, 10 ),
			_tcstol( m_editStatus[12 + PokemonData::Contact_Index], nullptr, 10 ),
			_tcstol( m_editStatus[12 + PokemonData::Diffence_Index], nullptr, 10 ),
			_tcstol( m_editStatus[12 + PokemonData::Speed_Index], nullptr, 10 ),
		};

		// HPを計算する
		int val = ( status[PokemonData::HP_Index] * 2 + status[6 + PokemonData::HP_Index] + status[12 + PokemonData::HP_Index] / 4 ) * lv / 100 + lv + 10;
		m_editStatus[PokemonData::HP_Index].Format( _T( "%d" ), val );

		// それ以外のステータスを計算する
		for ( int i = 1; i < PokemonData::StatusKind; ++i )
		{
			val = ( status[PokemonData::HP_Index + i] * 2 + status[6 + PokemonData::HP_Index + i] + status[12 + PokemonData::HP_Index + i] / 4 ) * lv / 100 + 5;
			m_editStatus[PokemonData::HP_Index + i].Format( _T( "%d" ), val );

			// 性格補正する
			// ちょっと実装保留で…
		}

		UpdateData( FALSE );
	} catch ( ... ) {}
}

// ラジオボタン制御のベース関数
void CPokeCalcDDlg::OnBnClickedRadioBase( UINT id )
{
	UpdateData( TRUE );
}

void CPokeCalcDDlg::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar )
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	UpdateData( TRUE );

	if ( nSBCode == SB_LINEUP )
	{
		// 上ボタンが押された時
		UINT_PTR id = pScrollBar->GetDlgCtrlID() - IDC_SCROLLBAR1;
		unsigned int val = _tcstol( m_editStatus[id], nullptr, 10 );
		if ( id >= PokemonData::StatusKind * 2 )
		{
			// 努力値は4ずつ増減させる
			val += 4;
		}
		else
		{
			// 実数値と個体値は1ずつ増減させる
			++val;

			// 実数値を操作された時は、まず努力値を増減、それができない時は個体値を増減、それもダメならエラーとしたい
		}
		m_editStatus[id].Format( _T( "%d" ), val );
	}
	else if ( nSBCode == SB_LINEDOWN )
	{
		// 下ボタンが押された時
		UINT_PTR id = pScrollBar->GetDlgCtrlID() - IDC_SCROLLBAR1;
		unsigned int val = _tcstol( m_editStatus[id], nullptr, 10 );
		if ( id >= PokemonData::StatusKind * 2 )
		{
			// 努力値は4ずつ増減させる
			val -= 4;
		}
		else
		{
			// 実数値と個体値は1ずつ増減させる
			--val;
		}
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

	CDialogEx::OnVScroll( nSBCode, nPos, pScrollBar );
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
			update( PokemonData::StatusKind * 2 + inputId / 2, 1 ); // 努力値を修正 -> Lvによって1増えるのに必要な努力値が違うので注意！（あとで直す！！！）
			UpdateData( FALSE );

			AllCalcStatus(); // ステータスを再計算
		}
		else
		{
			// 偶数番目は - ボタン
			update( PokemonData::StatusKind * 2 + inputId / 2, -1 );
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
		// + あるいは - が押された時、最も低い / 高いステータスが - / + になるように性格を変えてあげたい
	}
	else if ( inputId < 38 ) // 次の10個はランク補正
	{
		// ステータスそのものは再計算不要だから、ここでやることは特にない…？
	}
	else if ( inputId < 48 ) // 次の10個は特性補正
	{
		// 同上
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



void CPokeCalcDDlg::OnChangeEdit1()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。

	// これもしかしてエディットボックスじゃなくてコンボボックスが良いのでは…？？
	// -> ポップアップウィンドウでなんとかならないか…？

	/* 入力された文字からデータベースを検索する */
	UpdateData( TRUE ); // エディットボックスの入力中の文字を変数側に反映させる
	CRecordset rs( &m_database );
	try {
		CString strSQL;
		CString tmpTrans = m_trans.exec( m_editValName );
		if ( tmpTrans.IsEmpty() == FALSE )
		{
			strSQL.Format( _T( "SELECT * FROM pokemon WHERE 名前 Like '%%%s%%'" ), m_trans.exec( m_editValName ) );
		}
		else
		{
			return;
		}
		auto res = rs.Open( CRecordset::forwardOnly, strSQL );
		CODBCFieldInfo fi;
		short nFields = rs.GetODBCFieldCount();
		std::vector<CString> nameList;
		while ( rs.IsEOF() == FALSE )
		{
			CString strValue;
			rs.GetFieldValue( 1, strValue );
			nameList.emplace_back( strValue ); // 名前をリストに突っ込む
			rs.MoveNext();
		}

		// ポケモンが見つかった場合
		if ( nameList.size() > 0 )
		{
			m_complDlg.setListBox( nameList );

			CRect rect;
			m_editCtrl_Name.GetWindowRect( &rect );
			rect.top = rect.top += 24; // エディットボックスが隠れないようにする
			rect.bottom = rect.top + ( nameList.size() + 1 ) * 24; // 24px × ポケモンの数くらいにしてみる
			m_complDlg.MoveWindow( &rect );
			m_complDlg.ShowWindow( SW_SHOW );
//			m_complDlg.RunModalLoop(); // ループで止まっちゃうと次の文字が入力できなくて困るのでは…？
		}

		// エディットボックス（にするかコンボボックスにするかは要検討）に反映させて閉じる -> 補完ダイアログからの入力を受けて反映させたい
		// 反映させる処理
		UpdateData( FALSE );
		rs.Close();

		// ステータスを計算する -> ポケモンを選択されてからやらないとダメ
//		AllCalcStatus();
	} catch ( CDBException &e ) {
		TCHAR msg[1024];
		e.GetErrorMessage( msg, sizeof( msg ) );
		MessageBox( msg, _T( "error" ), MB_ICONERROR );
	}
}


void CPokeCalcDDlg::OnCbnSelchangeCombo()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	// 性格を変更したらステータスを再計算する
	if ( m_editValName.IsEmpty() == FALSE )
	{
		AllCalcStatus();
	}
}

// ステータス再計算要求
afx_msg LRESULT CPokeCalcDDlg::OnPcdStatusRecalculate( WPARAM wParam, LPARAM lParam )
{
	AllCalcStatus();
	return 0;
}


