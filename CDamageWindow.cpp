// CDamageWindow.cpp : 実装ファイル
//

#include "pch.h"
#include "PokeCalcD.h"
#include "CDamageWindow.h"
#include "afxdialogex.h"


// CDamageWindow ダイアログ

IMPLEMENT_DYNAMIC(CDamageWindow, CDialogEx)

CDamageWindow::CDamageWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DAMAGE_WINDOW, pParent)
	, m_picType( 256 )
	, m_strMove( 256 )
	, m_picDamage( 256 )
	, m_picRemain( 256 )
	, m_picDamageRand( 256 )

{

}

CDamageWindow::~CDamageWindow()
{
}

void CDamageWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_SCROLLBAR1, m_scrollDamage );
}


BEGIN_MESSAGE_MAP(CDamageWindow, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CDamageWindow メッセージ ハンドラー


BOOL CDamageWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	// 表示に必要な画像をロードする
	std::vector<CString> picname = {
			_T( "normal.bmp" ), _T( "flare.bmp" ), _T( "water.bmp" ), _T( "electric.bmp" ),
			_T( "grass.bmp" ), _T( "ice.bmp" ), _T( "fighting.bmp" ), _T( "poison.bmp" ),
			_T( "ground.bmp" ), _T( "flying.bmp" ), _T( "psychic.bmp" ), _T( "bug.bmp" ),
			_T( "rock.bmp" ), _T( "ghost.bmp" ), _T( "dragon.bmp" ), _T( "dark.bmp" ),
			_T( "steel.bmp" ), _T( "fairy.bmp" ),

			_T( "normal_tera.bmp" ), _T( "flare_tera.bmp" ), _T( "water_tera.bmp" ), _T( "electric_tera.bmp" ),
			_T( "grass_tera.bmp" ), _T( "ice_tera.bmp" ), _T( "fighting_tera.bmp" ), _T( "poison_tera.bmp" ),
			_T( "ground_tera.bmp" ), _T( "flying_tera.bmp" ), _T( "psychic_tera.bmp" ), _T( "bug_tera.bmp" ),
			_T( "rock_tera.bmp" ), _T( "ghost_tera.bmp" ), _T( "dragon_tera.bmp" ), _T( "dark_tera.bmp" ),
			_T( "steel_tera.bmp" ), _T( "fairy_tera.bmp" ),

			_T( "gray.bmp" ),
			_T( "red.bmp" ), _T( "red_random.bmp" ),
			_T( "yellow.bmp" ), _T( "yellow_random.bmp" ),
			_T( "green.bmp" ), _T( "green_random.bmp" ),
	};
	CString strPath;
	TCHAR buf[2048] = { 0 };
	GetModuleFileName( nullptr, buf, sizeof( buf ) / sizeof( TCHAR ) );
	for ( auto &&filename : picname )
	{
		CImage img;
		strPath.Format( _T( "%s\\pic\\%s" ), buf, filename );

		auto ret = img.Load( strPath );
		m_img.emplace_back( img );
	}

	// スクロールバーの初期設定
	SCROLLINFO scrollinfo = { 0 };
	scrollinfo.fMask = SIF_PAGE | SIF_RANGE;
	m_scrollDamage.GetScrollInfo( &scrollinfo );
	scrollinfo.nPage = 1;
	m_scrollDamage.SetScrollInfo( &scrollinfo );

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CDamageWindow::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar )
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if ( nSBCode == SB_LINEUP || nSBCode == SB_LINEDOWN )
	{
		// スクロールバーの↑↓を押下された時
		printDamage( nPos );
	}

	CDialogEx::OnVScroll( nSBCode, nPos, pScrollBar );
}


BOOL CDamageWindow::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	return CDialogEx::OnMouseWheel( nFlags, zDelta, pt );
}


// ダメージ計算結果をsize個表示するためのスクロールバー設定
void CDamageWindow::setScrollInfo( unsigned int size )
{
	SCROLLINFO scrollinfo = { 0 };
	m_scrollDamage.GetScrollInfo( &scrollinfo );
	scrollinfo.nMin = 0;
	scrollinfo.nMax = size;	// ここの値は個数分で良いのか…？
	m_scrollDamage.SetScrollInfo( &scrollinfo );
}

// ダメージが大きい順に計算結果を格納し直して描画を準備する
void CDamageWindow::setDamageInfo( std::map<CString, std::vector<int>> &damage, int defHP )
{
	// mapの時点でソートしておくのは難しそうだから、ここで一回詰め直したい
	// →出力を、ダメージが大きい順にしてあげた方が良いよね、というお気持ち
	// もしこっちのダイアログでダメージ計算するなら、この処理も表示処理の方に移動させるべし
	std::vector<std::pair<CString, int>> tmpMoveName;
	for ( auto &&it : damage )
	{
		tmpMoveName.emplace_back( std::make_pair( it.first, it.second[15] ) ); // 急所に当たらなかった場合の一番ダメージが大きい結果を元にソートしたい
	}
	sort( tmpMoveName.begin(), tmpMoveName.end(),
		[]( std::pair<CString, int> a, std::pair<CString, int> b ) {
		return ( a.second > b.second );
	} );
	for ( auto &&it : tmpMoveName )
	{
		m_printData.emplace_back( std::make_pair( it.first, damage[it.first] ) );
	}
}

void CDamageWindow::printDamage( UINT startPos )
{
	// タイプ名称テーブルを取得
	PokeType pt;
	auto typetable = pt.getTypeTable();

	// この関数では、全ての技に対して描画準備をしておくが、実際は画面上には5つくらいだけ表示したい
	// で、スクロールバーを上下に動かした時、nPosの前後2つずつくらいを出す、みたいにしたい
	// →毎回、全部の技に対してゲージを描画すると遅くなりそうだから、まとめて読むのはここだけにしたいけど、言うほど気にしなくて良いか…？
	// 　→ほとんどの場合は関係ないけど、全部の技を覚えるやつとかいるからなぁ…。

	// 計算された技の個数分だけゲージを用意する
	size_t sz = m_printData.size();

	for ( int i = min( startPos, sz - 5 ); i < min( startPos + 5, sz ); ++i )
	{
		CRecordset rs( m_database );
		CString strSQL;
		strSQL.Format( _T( "select タイプ from move where 技名='%s'" ), m_printData[i].first ); // 技データベースの検索
		CString strType;
		rs.GetFieldValue( (short)0, strType ); // select文で1つしか指定しない時はインデックスは0で良い？？(要確認)

		// タイプ名称を数値(インデックス)に変換するテーブルを、pokemove.hppからutil.hppに移動した方が良い説
		// -> もしくは、poketype.hpp を新しく作ってそこに定義するとか…そっちの方が良いかな…

		auto dc = m_picDamage[i].GetDC(); // これもメンバ変数に保存か…？
		int iWidth = 250;  // 幅、あとでちゃんと直す
		int iHeight = 10; // 高さ、あとでちゃんと直す

		CRect rect;
		m_picDamage[i].MoveWindow( rect );

		// 与えるダメージによってロードする画像を変えることになるはず
		// 今更だけど、ゲージを表示するにはポケモンのHP実数値が必要なんだから、本体のダイアログじゃなくて
		// ここで計算するべきなのでは…？(でもオプションのチェックボックスを拾うのが面倒になるか…)
		// -> でも表示更新＝再計算なんだし、それでも良い気がしないでもない…
		// 引数にPokemonDataをもらうしかないか…それも何か違う気がするが……

		CDC bmpDC;
		CBitmap *cbmp = CBitmap::FromHandle( m_img[i] ); // img[i]じゃなくてimg[画像のインデックス]って感じになると思う
		bmpDC.CreateCompatibleDC( dc );
		CBitmap *oldbmp = bmpDC.SelectObject( cbmp );

		dc->SetStretchBltMode( STRETCH_HALFTONE );
		dc->SetBrushOrg( 0, 0 );
		dc->StretchBlt( 0, 0, iWidth, iHeight, &bmpDC, 0, 0, m_img[i].GetWidth(), m_img[i].GetHeight(), SRCCOPY );
		bmpDC.SelectObject( oldbmp );

		cbmp->DeleteObject();
		bmpDC.DeleteDC();
		ReleaseDC( dc );
	}
}
