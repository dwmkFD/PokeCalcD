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
END_MESSAGE_MAP()


// CDamageWindow メッセージ ハンドラー


BOOL CDamageWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	// 表示に必要な画像をロードする
	std::vector<CString> picname = { // 残りのやつもロードするように書き換えるべし！
//			_T( "pic\\flare.bmp" ), _T( "pic\\water.bmp" ), // タイプ表示画像はpngかjpgにしたい…
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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CDamageWindow::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar *pScrollBar )
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	CDialogEx::OnVScroll( nSBCode, nPos, pScrollBar );
}

void CDamageWindow::printDamage( std::map<CString, std::vector<int>> damage )
{
	// 計算された技の個数分だけゲージを用意する
	size_t sz = damage.size();
	std::vector<CStatic> picType( sz );       // 技のタイプを示すアイコン
	std::vector<CStatic> strMove( sz );       // 技名
	std::vector<CStatic> picDamage( sz );     // ダメージゲージのベース部分（灰色？）
	std::vector<CStatic> picRemain( sz );     // 残りHP部分（緑だったり黄色だったり赤だったり、確1なら無し）
	std::vector<CStatic> picDamageRand( sz ); // ダメージの乱数でブレる部分(色は残りHP側に合わせた薄い色、確1なら無し)

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

	// この関数では、全ての技に対して描画準備をしておくが、実際は画面上には5つくらいだけ表示したい
	// で、スクロールバーを上下に動かした時、nPosの前後2つずつくらいを出す、みたいにしたい
	// →毎回、全部の技に対してゲージを描画すると遅くなりそうだから、まとめて読むのはここだけにしたいけど、言うほど気にしなくて良いか…？
	// 　→ほとんどの場合は関係ないけど、全部の技を覚えるやつとかいるからなぁ…。

	for ( int i = 0; i < sz; ++i )
	{
		auto dc = picDamage[i].GetDC();
		int iWidth = 100;  // 幅
		int iheight = 100; // 高さ、あとでちゃんと直す

		CRect rect;
		picDamage[i].MoveWindow( rect );

		ReleaseDC( dc );
	}
}
