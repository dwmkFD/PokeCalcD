// CDamageWindow.cpp : 実装ファイル
//

#include "pch.h"
#include "PokeCalcD.h"
#include "CDamageWindow.h"
#include "afxdialogex.h"


// CDamageWindow ダイアログ

IMPLEMENT_DYNAMIC(CDamageWindow, CDialogEx)

CDamageWindow::CDamageWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DAMAGE_WINDOW, pParent),
	m_img( IMAGENAME_ALLIMAGE_SIZE )
{
}

CDamageWindow::~CDamageWindow()
{
}

void CDamageWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
//	DDX_Control( pDX, IDC_SCROLLBAR1, m_scrollDamage );
}


BEGIN_MESSAGE_MAP(CDamageWindow, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDamageWindow メッセージ ハンドラー


BOOL CDamageWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	// 表示に必要なコントロールを初期化する

	// スクロールバーの初期設定
	SCROLLINFO scrollinfo = { 0 };
	scrollinfo.fMask = SIF_PAGE | SIF_RANGE;
	m_scrollDamage.GetScrollInfo( &scrollinfo );
	scrollinfo.nPage = 1;
	scrollinfo.nMin = 0;
	scrollinfo.nMax = 0;
	m_scrollDamage.SetScrollInfo( &scrollinfo );

	// 表示に必要な画像をロードする
	std::vector<CString> picname = {
			_T( "normal.png" ), _T( "flare.png" ), _T( "water.png" ), _T( "electric.png" ),
			_T( "grass.png" ), _T( "ice.png" ), _T( "fighting.png" ), _T( "poison.png" ),
			_T( "ground.png" ), _T( "flying.png" ), _T( "psychic.png" ), _T( "bug.png" ),
			_T( "rock.png" ), _T( "ghost.png" ), _T( "dragon.png" ), _T( "dark.png" ),
			_T( "steel.png" ), _T( "fairy.png" ),

			_T( "normal_tera.png" ), _T( "flare_tera.png" ), _T( "water_tera.png" ), _T( "electric_tera.png" ),
			_T( "grass_tera.png" ), _T( "ice_tera.png" ), _T( "fighting_tera.png" ), _T( "poison_tera.png" ),
			_T( "ground_tera.png" ), _T( "flying_tera.png" ), _T( "psychic_tera.png" ), _T( "bug_tera.png" ),
			_T( "rock_tera.png" ), _T( "ghost_tera.png" ), _T( "dragon_tera.png" ), _T( "dark_tera.png" ),
			_T( "steel_tera.png" ), _T( "fairy_tera.png" ),

			_T( "gray.bmp" ),
			_T( "red.bmp" ), _T( "red_random.bmp" ),
			_T( "yellow.bmp" ), _T( "yellow_random.bmp" ),
			_T( "green.bmp" ), _T( "green_random.bmp" ),
	};
	CString strPath;
	TCHAR buf[2048] = { 0 };
	int cnt = 0;
	GetCurrentDirectory( sizeof( buf ), buf );
	for ( auto &&filename : picname )
	{
		strPath.Format( _T( "%s\\pic\\%s" ), buf, filename );

		auto ret = m_img[cnt++].Load( strPath );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CDamageWindow::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar )
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	switch ( nSBCode )
	{
		case SB_LINEUP:
//			ScrollWindow( 0, -10 );
			break;

		case SB_LINEDOWN:
//			ScrollWindow( 0, 10 );
			break;

		case SB_THUMBPOSITION:
			break;

		case SB_PAGEUP:
			break;

		case SB_PAGEDOWN:
			break;

		default:
			break;
	}

	CDialogEx::OnVScroll( nSBCode, nPos, pScrollBar );
}


BOOL CDamageWindow::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if ( zDelta > 0 )
	{
		// 上にスクロール
	}
	else if ( zDelta < 0 )
	{
		// 下にスクロール
	}

	return CDialogEx::OnMouseWheel( nFlags, zDelta, pt );
}


// ダメージ計算結果をsize個表示するためのスクロールバー設定
void CDamageWindow::setScrollInfo( unsigned int size )
{
	// ここはむしろスクロール量の調整の方をやりたい
	// 技候補が少ない時はスライダーは長く、技候補が多い時はスライダーは短くなるはず…

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
		tmpMoveName.emplace_back( std::make_pair( it.first, it.second[32] ) ); // 期待値が大きい順にソートする(命中率や急所率込）
	}
	sort( tmpMoveName.begin(), tmpMoveName.end(),
		[]( std::pair<CString, int> a, std::pair<CString, int> b ) {
		return ( a.second > b.second );
	} );
	for ( auto &&it : tmpMoveName )
	{
		m_printData.emplace_back( std::make_pair( it.first, damage[it.first] ) );
	}

	m_defHP = defHP;
}

void CDamageWindow::printDamage( UINT startPos )
{
}


void CDamageWindow::OnPaint()
{
	CPaintDC dc( this ); // device context for painting
						 // TODO: ここにメッセージ ハンドラー コードを追加します。
						 // 描画メッセージで CDialogEx::OnPaint() を呼び出さないでください。

	// 計算してない時は処理しない
	size_t sz = m_printData.size();

	if ( sz <= 0 )
	{
		return;
	}

	// タイプ名称テーブルを取得
	PokeType pt;
	auto typetable = pt.getTypeTable();

	// bitmap
	CDC bmpDC;
	auto ret = bmpDC.CreateCompatibleDC( &dc );
	std::vector<CBitmap *> bitmaptable( IMAGENAME_ALLIMAGE_SIZE );
	CBitmap *oldbmp = nullptr;

	// cbmp を何度もFromHandleしてるせいか、2回目以降に同じ画像を表示するとバグるので、直す
	// -> cbmpもvectorかmapにして最初に全部読み出し→保存しておく？
	for ( int i = 0; i < m_img.size(); ++i )
	{
		bitmaptable[i] = CBitmap::FromHandle( m_img[i] );
	}

	// そもそも全部描画してスクロールさせるなら、サイズ気にせず全部描画しちゃえば…？
	for ( int i = 0; i < sz; ++i )
	{
		CRecordset rs( m_database );
		CString strSQL;
		strSQL.Format( _T( "select タイプ from move where 技名='%s'" ), m_printData[i].first ); // 技データベースの検索
		rs.Open( CRecordset::forwardOnly, strSQL );
		CString strType;
		rs.GetFieldValue( (short)0, strType );

		// メンバ変数にスクロール位置とかを保存しておいて表示位置を計算しないとダメ！！！！！！！！！！！
		// -> と思ったけど、スクロール位置はm_scrollDamageが持ってるんじゃないの？
		//    m_scrollDamage.nPos * -40 みたいな補正すれば良いように思われる

		/* 技のタイプアイコンを表示 */
		int iWidth = 20;  // 幅、あとでちゃんと直す
		int iHeight = 20; // 高さ、あとでちゃんと直す

		// テラスタイプと一致する場合はアイコン変えたい（つまりテラバーストは常にテラスタイプアイコンになるね、別に良いけど）
		// -> 元タイプとも一致する、完全なテラスタイプ一致はもうちょっと強調してあげたい気もする…（一致補正2倍だから）
		if ( oldbmp == nullptr )
		{
			oldbmp = bmpDC.SelectObject( bitmaptable[typetable[strType]] );
		}
		else
		{
			bmpDC.SelectObject( bitmaptable[typetable[strType]] );
		}
		dc.SetStretchBltMode( STRETCH_HALFTONE );
		dc.StretchBlt( 10, 10 + i * 40, iWidth, iHeight, &bmpDC, 0, 0, m_img[typetable[strType]].GetWidth(), m_img[typetable[strType]].GetHeight(), SRCCOPY );

		/* 技名のテキストを表示 */
		CRect rect;
		rect.SetRect( 35, 10 + i * 40, 170, 26 + i * 40 );
		dc.DrawText( m_printData[i].first, rect, 0 );

		/* ダメージゲージのベース部分を表示 */
		iWidth = 220;
		iHeight = 16;
		bmpDC.SelectObject( bitmaptable[IMAGENAME_GAUGE_GRAY] );
		dc.SetStretchBltMode( STRETCH_HALFTONE );
		dc.StretchBlt( 180, 10 + i * 40, iWidth, iHeight, &bmpDC, 0, 0, m_img[IMAGENAME_GAUGE_GRAY].GetWidth(), m_img[IMAGENAME_GAUGE_GRAY].GetHeight(), SRCCOPY );

		/* ダメージゲージの乱数幅部分を表示 */ // -> ゲージの色はWikiを見て確認！！
		// 乱数幅の方から描画して上から残りHP部分で上書きした方が楽だよね
		UINT imgIndex = 0;
		if ( m_defHP * 0.5 >= m_printData[i].second[7] ) // だいたい真ん中辺り＝平均ダメージとして、これをベースにゲージの色を決める
		{
			// ダメージ40％以下の場合は緑ゲージ
			imgIndex = IMAGENAME_GAUGE_GREEN;
		}
		else if ( m_defHP * 0.75 >= m_printData[i].second[7] )
		{
			// ダメージ75％以下の場合は黄色ゲージ
			imgIndex = IMAGENAME_GAUGE_YELLOW;
		}
		else
		{
			// ダメージが75％を超えたら赤ゲージ
			imgIndex = IMAGENAME_GAUGE_RED;
		}

		iWidth = 220 * ( max( m_defHP - m_printData[i].second[0], 0 ) / (double)m_defHP ); // 表示する長さは残りHPによって変わるはず
		iHeight = 14;
		bmpDC.SelectObject( bitmaptable[imgIndex + 1] );
		dc.SetStretchBltMode( STRETCH_HALFTONE );
		dc.StretchBlt( 181, 11 + i * 40, iWidth, iHeight, &bmpDC, 0, 0, m_img[imgIndex + 1].GetWidth(), m_img[imgIndex + 1].GetHeight(), SRCCOPY );

		/* ダメージゲージの残りHP部分を表示 */
		iWidth = 220 * ( max( m_defHP - m_printData[i].second[15], 0 ) / (double)m_defHP ); // 確定で残る量を算出するので最大ダメージでゲージ量を計算
		iHeight = 14;
		bmpDC.SelectObject( bitmaptable[imgIndex] );
		dc.SetStretchBltMode( STRETCH_HALFTONE );
		dc.StretchBlt( 181, 11 + i * 40, iWidth, iHeight, &bmpDC, 0, 0, m_img[imgIndex].GetWidth(), m_img[imgIndex].GetHeight(), SRCCOPY );

		/* 急所に当たらなかった場合のダメージ範囲をゲージの下に出したい */
		rect.SetRect( 180, 30 + i * 40, 450, 46 + i * 40 );
		CString strDamageRange;
		strDamageRange.Format( _T( "%.1lf％ ～ %.1lf％（期待値：%.1lf）" ),
							   m_printData[i].second[0] / (double)m_defHP * 100,
							   m_printData[i].second[15] / (double)m_defHP * 100,
							   m_printData[i].second[32] / (double)m_defHP * 100 );
		dc.DrawText( strDamageRange, rect, 0 );
	}

	for ( int i = 0; i < bitmaptable.size(); ++i )
	{
		bitmaptable[i]->DeleteObject();
	}
	bmpDC.SelectObject( oldbmp );
	bmpDC.DeleteDC();
}
