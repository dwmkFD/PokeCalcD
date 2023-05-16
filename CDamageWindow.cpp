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
	std::vector<CString> picname = { // 残りのやつもロードするように書き換えるべし！
			_T( "pic\\normal.bmp" ), _T( "pic\\flare.bmp" ), _T( "pic\\water.bmp" ), _T( "pic\\electric.bmp" ),
			_T( "pic\\grass.bmp" ), _T( "pic\\ice.bmp" ), _T( "pic\\fighting.bmp" ), _T( "pic\\poison.bmp" ),

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
		m_img.emplace_back( img ); // 画像のインデックスは定義しなきゃダメだと思う
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
void CDamageWindow::setDamageInfo( std::map<CString, std::vector<int>> &damage )
{
	// mapの時点でソートしておくのは難しそうだから、ここで一回詰め直したい
	// →出力を、ダメージが大きい順にしてあげた方が良いよね、というお気持ち
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
	// この関数では、全ての技に対して描画準備をしておくが、実際は画面上には5つくらいだけ表示したい
	// で、スクロールバーを上下に動かした時、nPosの前後2つずつくらいを出す、みたいにしたい
	// →毎回、全部の技に対してゲージを描画すると遅くなりそうだから、まとめて読むのはここだけにしたいけど、言うほど気にしなくて良いか…？
	// 　→ほとんどの場合は関係ないけど、全部の技を覚えるやつとかいるからなぁ…。

	// 計算された技の個数分だけゲージを用意する
	size_t sz = m_printData.size();

	for ( int i = min( startPos, sz - 5 ); i < min( startPos + 5, sz ); ++i )
	{
		auto dc = m_picDamage[i].GetDC(); // これもメンバ変数に保存か…？
		int iWidth = 100;  // 幅
		int iHeight = 100; // 高さ、あとでちゃんと直す

		CRect rect;
		m_picDamage[i].MoveWindow( rect );

		// 与えるダメージによってロードする画像を変えることになるはず

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
