// CPokeDataDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "PokeCalcD.h"
#include "CPokeDataDlg.h"
#include "afxdialogex.h"

#include "util.hpp"
#include "pokemon.hpp"
#include "pokemove.hpp"
#include "damage.hpp"

#include <algorithm>


// CPokeDataDlg ダイアログ

IMPLEMENT_DYNAMIC(CPokeDataDlg, CDialogEx)

CPokeDataDlg::CPokeDataDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POKEMON_DIALOG1, pParent)
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

	, m_cmbRank( PokemonData::StatusKind ) // HPはランク補正かけられないから要らないけど、領域だけ確保する
{

}

CPokeDataDlg::~CPokeDataDlg()
{
}

void CPokeDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	// ポケモン1側
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

	DDX_Check( pDX, IDC_CHECK7, m_checkReflecter );
	DDX_Check( pDX, IDC_CHECK8, m_checkLightScreen );
	DDX_Check( pDX, IDC_CHECK9, m_checkHelpingHand );
	DDX_Check( pDX, IDC_CHECK10, m_checkKiaidame );
	DDX_Check( pDX, IDC_CHECK11, m_checkJuden );
	DDX_Check( pDX, IDC_CHECK12, m_checkHaganenoseisin );

	DDX_Control( pDX, IDC_COMBO1, m_cmbNature );
	DDX_Control( pDX, IDC_COMBO2, m_cmbRank[1] );
	DDX_Control( pDX, IDC_COMBO3, m_cmbRank[2] );
	DDX_Control( pDX, IDC_COMBO4, m_cmbRank[3] );
	DDX_Control( pDX, IDC_COMBO5, m_cmbRank[4] );
	DDX_Control( pDX, IDC_COMBO6, m_cmbRank[5] );
	DDX_Control( pDX, IDC_COMBO12, m_cmbAbility );
	DDX_Control( pDX, IDC_COMBO13, m_cmbItem );
	DDX_Control( pDX, IDC_COMBO14, m_cmbTeraType );
	DDX_Control( pDX, IDC_STATIC_EFFTVAL1, m_strEfftTotal );
}


BEGIN_MESSAGE_MAP(CPokeDataDlg, CDialogEx)
	ON_CONTROL_RANGE( BN_CLICKED, IDC_RADIO1, IDC_RADIO12, &CPokeDataDlg::OnBnClickedRadioBase )
	ON_CONTROL_RANGE( CBN_SELCHANGE, IDC_COMBO2, IDC_COMBO6, &CPokeDataDlg::OnCbnSelChangeComboBox )

	ON_CONTROL_RANGE( BN_CLICKED, IDC_BUTTON1, IDC_BUTTON48, &CPokeDataDlg::OnBnClickedStatusButton )
	ON_EN_CHANGE( IDC_EDIT1, &CPokeDataDlg::OnChangeEditName )
	ON_EN_CHANGE( IDC_EDIT2, &CPokeDataDlg::OnChangeEditLevel )
	ON_CBN_SELCHANGE( IDC_COMBO1, &CPokeDataDlg::OnCbnSelchangeCombo )
	ON_MESSAGE( PCD_STATUS_RECALCULATE, &CPokeDataDlg::OnPcdStatusRecalculate )
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CPokeDataDlg メッセージ ハンドラー

BOOL CPokeDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 初期化をここに追加します。

	m_complDlg.Create( IDD_POPUP_COMPLDATA, this ); // 補完ダイアログボックスを初期化する
	// -> 親ダイアログにメッセージを実装しろ！

	initNature();	// 性格コンボボックスを初期化して「頑張り屋」を選んでおく
	initAbility();	// 特性コンボボックスを初期化
	initItem();		// 持ち物コンボボックスを初期化
	initTeraType(); // テラスタイプコンボボックスを初期化
	initRankCorrect(); // ランク補正コンボボックスを初期化

	// 個体値と努力値の初期値を入れておく
	for ( int i = 0; i < PokemonData::StatusKind; ++i )
	{
		m_editStatus[i + PokemonData::StatusKind] = _T( "31" );
		m_editStatus[i + PokemonData::StatusKind * 2] = _T( "0" );
	}

	UpdateData( FALSE ); // 画面側に反映させる

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}


// ReturnキーやESCキーでダイアログが閉じると困るので
BOOL CPokeDataDlg::PreTranslateMessage( MSG *pMsg )
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
void CPokeDataDlg::initNature()
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
void CPokeDataDlg::initAbility()
{
	m_cmbAbility.AddString( _T( "(未発動)" ) );
	m_cmbAbility.SetCurSel( 0 );
}

// 持ち物コンボボックスの初期化
void CPokeDataDlg::initItem()
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

// テラスタイプコンボボックスの初期化
void CPokeDataDlg::initTeraType()
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

// ランク補正コンボボックスの初期化
void CPokeDataDlg::initRankCorrect()
{
	CString strInput;
	for ( int i = 6; i > 0; --i )
	{
		strInput.Format( _T( "+%d" ), i );
		m_cmbRank[PokemonData::Attack_Index].AddString( strInput );
		m_cmbRank[PokemonData::Block_Index].AddString( strInput );
		m_cmbRank[PokemonData::Contact_Index].AddString( strInput );
		m_cmbRank[PokemonData::Diffence_Index].AddString( strInput );
		m_cmbRank[PokemonData::Speed_Index].AddString( strInput );
	}
	m_cmbRank[PokemonData::Attack_Index].AddString( _T( "-" ) );
	m_cmbRank[PokemonData::Block_Index].AddString( _T( "-" ) );
	m_cmbRank[PokemonData::Contact_Index].AddString( _T( "-" ) );
	m_cmbRank[PokemonData::Diffence_Index].AddString( _T( "-" ) );
	m_cmbRank[PokemonData::Speed_Index].AddString( _T( "-" ) );
	for ( int i = -1; i >= -6; --i )
	{
		strInput.Format( _T( "%d" ), i );
		m_cmbRank[PokemonData::Attack_Index].AddString( strInput );
		m_cmbRank[PokemonData::Block_Index].AddString( strInput );
		m_cmbRank[PokemonData::Contact_Index].AddString( strInput );
		m_cmbRank[PokemonData::Diffence_Index].AddString( strInput );
		m_cmbRank[PokemonData::Speed_Index].AddString( strInput );
	}

	m_cmbRank[PokemonData::Attack_Index].SetCurSel( 6 );
	m_cmbRank[PokemonData::Block_Index].SetCurSel( 6 );
	m_cmbRank[PokemonData::Contact_Index].SetCurSel( 6 );
	m_cmbRank[PokemonData::Diffence_Index].SetCurSel( 6 );
	m_cmbRank[PokemonData::Speed_Index].SetCurSel( 6 );
}


// 努力値を増減させる
bool CPokeDataDlg::addEffortVal( UINT id, bool isGain = true )
{
	// 引数が true なら増加、false なら減少させる
	int realval = _tcstol( m_editStatus[id], nullptr, 10 );
	int efftval = _tcstol( m_editStatus[id + PokemonData::StatusKind * 2], nullptr, 10 );

	efftval += ( isGain ? 1 : -1 ) * 4;
	m_editStatus[id + PokemonData::StatusKind * 2].Format( _T( "%d" ), efftval );
	AllEditCheck();  // 範囲チェック
	AllCalcStatus(); // ステータス再計算

	int realval2 = _tcstol( m_editStatus[id], nullptr, 10 );
	if ( realval2 == realval ) // 努力値を4だけ増減させてステータスが変わらなかった場合
	{
		// さらに4だけ増減させる
		efftval += ( isGain ? 1 : -1 ) * 4;
		m_editStatus[id + PokemonData::StatusKind * 2].Format( _T( "%d" ), efftval );
		AllEditCheck();
		AllCalcStatus();
	}

	realval2 = _tcstol( m_editStatus[id], nullptr, 10 );

	return ( realval != realval2 ); // ステータスを増減させることができたら true を返す
}


// 値チェックと補正
void CPokeDataDlg::AllEditCheck()
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

// ステータス再計算
void CPokeDataDlg::AllCalcStatus()
{
	// 種族値も必要だがどうやって持ってくる…？
	// -> m_editStatusの4つ目に入れておく？
	//    -> 1匹2匹程度なら、毎回データベースから拾ってきても良いかも
	CRecordset rs( m_database );
	CString strSQL;
	strSQL.Format( _T( "SELECT * FROM pokemon WHERE 名前='%s'" ), m_editValName ); // 2回のループにしないとダメ！！！！！！
	auto res = rs.Open( CRecordset::forwardOnly, strSQL );
	short nFields = rs.GetODBCFieldCount();

	m_pokemon.clear(); // 前に持っていた可能性のある情報をクリアする

	// ステータス計算式：
	// HPの場合：(種族値×2+個体値+努力値÷4)×レベル÷100+レベル+10
	// それ以外：{(種族値×2+個体値+努力値÷4)×レベル÷100+5}×せいかく補正

	try {
		CString strValue;
		for ( int i = 4; i < 10; ++i ) // 何番目のフィールドかはデータベース見て直値で入れておく（本当は良くないけど…）
		{
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

		// 名前を保存する
		m_pokemon.m_name = m_editValName;

		// Lvを保存する
		m_pokemon.m_Level = lv;

		// HPを計算する
		m_pokemon.m_status[PokemonData::HP_Index] = ( status[PokemonData::HP_Index] * 2 + status[6 + PokemonData::HP_Index] + status[12 + PokemonData::HP_Index] / 4 ) * lv / 100 + lv + 10;
		m_editStatus[PokemonData::HP_Index].Format( _T( "%d" ), m_pokemon.m_status[PokemonData::HP_Index] );

		// それ以外のステータスを計算する
		for ( int i = 1; i < PokemonData::StatusKind; ++i )
		{
			m_pokemon.m_status[PokemonData::HP_Index + i] = ( status[PokemonData::HP_Index + i] * 2 + status[6 + PokemonData::HP_Index + i] + status[12 + PokemonData::HP_Index + i] / 4 ) * lv / 100 + 5;
			m_editStatus[PokemonData::HP_Index + i].Format( _T( "%d" ), m_pokemon.m_status[PokemonData::HP_Index + i] );

			// 性格補正する
			// ちょっと実装保留で…
		}

		// 努力値表示更新
		for ( int j = 0; j < 2; ++j )
		{
			int val = 0;
			CString strEfftVal;
			for ( int i = 0; i < PokemonData::StatusKind; ++i )
			{
				val += status[12 + i];
			}
			strEfftVal.Format( _T( "%d%s" ), ( val > 510 ? val - 510 : val ), ( val > 510 ? _T( "over" ) : _T( "/510" ) ) );
			m_strEfftTotal.SetWindowText( strEfftVal );
		}

		// データベースから拾った情報も保存
		rs.GetFieldValue( 11, strValue );
		m_pokemon.m_Height = _tcstol( strValue, nullptr, 10 ); // 高さ
		rs.GetFieldValue( 12, strValue );
		m_pokemon.m_Weight = _tcstol( strValue, nullptr, 10 ); // 重さ

		// 特性コンボボックスを空にする
		while ( m_cmbAbility.GetCount() > 0 )
		{
			m_cmbAbility.DeleteString( 0 );
		}
		m_cmbAbility.AddString( _T( "(未発動)" ) ); // 未発動を入れる
		for ( int i = 0; i < 3; ++i )
		{
			rs.GetFieldValue( 13 + i, strValue );
			if ( strValue.IsEmpty() == FALSE )
			{
				m_pokemon.m_ability.emplace_back( strValue ); // 特性
				m_cmbAbility.AddString( strValue ); // コンボボックスにも反映
			}
		}
		for ( int i = 0; i < 2; ++i )
		{
			rs.GetFieldValue( 2 + i, strValue );
			if ( strValue.IsEmpty() == FALSE )
			{
				m_pokemon.m_type.emplace_back( strValue ); // タイプ
			}
		}
		for ( int i = 0; i < rs.GetODBCFieldCount(); ++i )
		{
			rs.GetFieldValue( 16 + i, strValue );
			if ( strValue.IsEmpty() == FALSE )
			{
				m_pokemon.m_move.emplace_back( strValue ); // 覚える技
			}
			else
			{
				break;
			}
		}

		UpdateData( FALSE );
	}
	catch ( ... ) {}
}


// ラジオボタン制御のベース関数
void CPokeDataDlg::OnBnClickedRadioBase( UINT id )
{
	UpdateData( TRUE );
}

// コンボボックス制御のベース関数
void CPokeDataDlg::OnCbnSelChangeComboBox( UINT id )
{
	UpdateData( TRUE );
}

// ステータス計算のベース関数
void CPokeDataDlg::statusCalcBase( UINT id, bool isGain )
{
	if ( isGain )
	{
		unsigned int val = _tcstol( m_editStatus[id], nullptr, 10 );
		if ( id >= PokemonData::StatusKind * 2 )
		{
			// 努力値を操作された時
			addEffortVal( id - PokemonData::StatusKind * 2 );
		}
		else if ( id >= PokemonData::StatusKind )
		{
			// 個体値は1ずつ増減させる
			++val;
			m_editStatus[id].Format( _T( "%d" ), val );
			AllEditCheck();
		}
		else
		{
			// 実数値を操作された時は、まず努力値を増減、それができない時は個体値を増減させる
			if ( addEffortVal( id ) == false )
			{
				++val;
				m_editStatus[id].Format( _T( "%d" ), val );
				AllEditCheck();
			}
		}
	}
	else
	{
		// 下ボタンが押された時
		unsigned int val = _tcstol( m_editStatus[id], nullptr, 10 );
		if ( id >= PokemonData::StatusKind * 2 )
		{
			// 努力値を操作された時
			addEffortVal( id - PokemonData::StatusKind * 2, false );
		}
		else if ( id >= PokemonData::StatusKind )
		{
			// 個体値は1ずつ増減させる
			--val;
			m_editStatus[id].Format( _T( "%d" ), val );
			AllEditCheck();
		}
		else
		{
			// 実数値を操作された時は、まず努力値を増減、それができない時は個体値を増減させる
			if ( addEffortVal( id, false ) == false )
			{
				--val;
				m_editStatus[id].Format( _T( "%d" ), val );
				AllEditCheck();
			}
		}
	}
}

void CPokeDataDlg::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar )
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	UpdateData( TRUE );

	UINT_PTR id = pScrollBar->GetDlgCtrlID() - IDC_SCROLLBAR1;
	if ( nSBCode == SB_LINEUP )
	{
		// 上ボタンが押された時
		statusCalcBase( id, true );
	}
	else if ( nSBCode == SB_LINEDOWN )
	{
		// 下ボタンが押された時
		statusCalcBase( id, false );
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


void CPokeDataDlg::OnBnClickedStatusButton( UINT id )
{
	UpdateData( TRUE );

	// id(つまり押されたボタン)によって振り分ける
	int inputId = id - IDC_BUTTON1;

	if ( inputId < 12 )	// 最初の12個はステータスの実数値を増減する(けど、実質努力値ボタンと一緒の扱いになると思う)
	{
		if ( inputId % 2 )
		{
			// 奇数番目は + ボタン
			statusCalcBase( inputId / 2, true );
		}
		else
		{
			// 偶数番目は - ボタン
			statusCalcBase( inputId / 2, false );
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
		// -> どちらかというと、、、
		//    攻撃 or 特攻を+-した場合→もう一方を-+する
		//    素早さを+-した場合→攻撃 or 特攻のうち低い/高い方(一緒なら攻撃)を-+する
		//    っていう感じ？
		//    でもそれは「無補正」から変える時か「今+-のやつを-+に変える時」の話なんだよね…(+-のうち一方がユーザの意図通りだったら動かしちゃダメ)
		// getMaxMinStatus(); // 的なやつを実装したい
	}
	else if ( inputId < 38 ) // 次の10個はランク補正
	{
		int cur = static_cast<CComboBox *>( GetDlgItem( IDC_COMBO2 + ( inputId - 28 ) / 2 ) )->GetCurSel();
		if ( inputId % 2 )
		{
			// 奇数番目は + ボタン
			--cur;
			if ( cur >= 0 )
			{
				static_cast<CComboBox *>( GetDlgItem( IDC_COMBO2 + ( inputId - 28 ) / 2 ) )->SetCurSel( cur );
			}
		}
		else
		{
			// 偶数番目は - ボタン
			++cur;
			if ( cur < 13 )
			{
				static_cast<CComboBox *>( GetDlgItem( IDC_COMBO2 + ( inputId - 28 ) / 2 ) )->SetCurSel( cur );
			}
		}
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
	GetParent()->SendMessage( PCD_DAMAGECALC_REQUEST ); // ステータスを修正したらダメージを再計算
}


void CPokeDataDlg::OnChangeEditBase( CEdit &editCtrl, CString &editVal )
{
	/* 入力された文字からデータベースを検索する */
	UpdateData( TRUE ); // エディットボックスの入力中の文字を変数側に反映させる
	CRecordset rs( m_database );
	try {
		CString strSQL;
		CString tmpTrans = m_trans.exec( editVal );
		if ( tmpTrans.IsEmpty() == FALSE )
		{
			strSQL.Format( _T( "SELECT * FROM pokemon WHERE 名前 Like '%%%s%%'" ), m_trans.exec( editVal ) );
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
			m_complDlg.clearListBox(); // まずリストを空にする
			m_complDlg.setListBox( nameList );
			m_complDlg.setID( m_id );

			CRect rect;
			editCtrl.GetWindowRect( &rect );
			rect.top = rect.top += 24; // エディットボックスが隠れないようにする
			rect.bottom = rect.top + ( nameList.size() + 1 ) * 24; // 24px × ポケモンの数くらいにしてみる
			m_complDlg.MoveWindow( &rect );
			m_complDlg.ShowWindow( SW_SHOW );
		}

		// エディットボックス（にするかコンボボックスにするかは要検討）に反映させて閉じる -> 補完ダイアログからの入力を受けて反映させたい
		// 反映させる処理
		UpdateData( FALSE );
		rs.Close();
	}
	catch ( CDBException &e ) {
		TCHAR msg[1024];
		e.GetErrorMessage( msg, sizeof( msg ) );
		MessageBox( msg, _T( "error" ), MB_ICONERROR );
	}
}


void CPokeDataDlg::OnChangeEditName()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
	OnChangeEditBase( m_editCtrl_Name, m_editValName ); // ダイアログ統一により関数化する必要はなくなったのだが…
}

void CPokeDataDlg::OnChangeEditLevel()
{
	UpdateData( TRUE );

	// レベルを変更したらステータスを再計算する
	OnPcdStatusRecalculate( 0, 0 );
}

void CPokeDataDlg::OnCbnSelchangeCombo()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	// 変更した性格に合わせてラジオボタンのON/OFFを変更する

	// 性格を変更したらステータスを再計算する
	if ( m_editValName.IsEmpty() == FALSE )
	{
		AllCalcStatus();
	}
}

// ステータス再計算要求
afx_msg LRESULT CPokeDataDlg::OnPcdStatusRecalculate( WPARAM wParam, LPARAM lParam )
{
	AllCalcStatus();
	return ( 0 );
}