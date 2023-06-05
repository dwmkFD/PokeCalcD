#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <map>

struct CTransrateRomaKana {
public:
	CTransrateRomaKana() :
		m_mapping(
			{ std::make_pair( _T( "a" ), _T( "ア" ) ), std::make_pair( _T( "ba" ), _T( "バ" ) ),
				std::make_pair( _T( "be" ), _T( "ベ" ) ), std::make_pair( _T( "bi" ), _T( "ビ" ) ),
				std::make_pair( _T( "bo" ), _T( "ボ" ) ), std::make_pair( _T( "bu" ), _T( "ブ" ) ),
				std::make_pair( _T( "bya" ), _T( "ビャ" ) ), std::make_pair( _T( "bye" ), _T( "ビェ" ) ),
				std::make_pair( _T( "byi" ), _T( "ビィ" ) ), std::make_pair( _T( "byo" ), _T( "ビョ" ) ),
				std::make_pair( _T( "byu" ), _T( "ビュ" ) ), std::make_pair( _T( "ca" ), _T( "カ" ) ),
				std::make_pair( _T( "ce" ), _T( "セ" ) ), std::make_pair( _T( "cha" ), _T( "チャ" ) ),
				std::make_pair( _T( "che" ), _T( "チェ" ) ), std::make_pair( _T( "chi" ), _T( "チ" ) ),
				std::make_pair( _T( "cho" ), _T( "チョ" ) ), std::make_pair( _T( "chu" ), _T( "チュ" ) ),
				std::make_pair( _T( "ci" ), _T( "シ" ) ), std::make_pair( _T( "co" ), _T( "コ" ) ),
				std::make_pair( _T( "cu" ), _T( "ク" ) ), std::make_pair( _T( "cya" ), _T( "チャ" ) ),
				std::make_pair( _T( "cye" ), _T( "チェ" ) ), std::make_pair( _T( "cyi" ), _T( "チィ" ) ),
				std::make_pair( _T( "cyo" ), _T( "チョ" ) ), std::make_pair( _T( "cyu" ), _T( "チュ" ) ),
				std::make_pair( _T( "da" ), _T( "ダ" ) ), std::make_pair( _T( "de" ), _T( "デ" ) ),
				std::make_pair( _T( "dha" ), _T( "デャ" ) ), std::make_pair( _T( "dhe" ), _T( "デェ" ) ),
				std::make_pair( _T( "dhi" ), _T( "ディ" ) ), std::make_pair( _T( "dho" ), _T( "デョ" ) ),
				std::make_pair( _T( "dhu" ), _T( "デュ" ) ), std::make_pair( _T( "di" ), _T( "ヂ" ) ),
				std::make_pair( _T( "do" ), _T( "ド" ) ), std::make_pair( _T( "du" ), _T( "ヅ" ) ),
				std::make_pair( _T( "dya" ), _T( "ヂャ" ) ), std::make_pair( _T( "dye" ), _T( "ヂェ" ) ),
				std::make_pair( _T( "dyi" ), _T( "ヂィ" ) ), std::make_pair( _T( "dyo" ), _T( "ヂョ" ) ),
				std::make_pair( _T( "dyu" ), _T( "デュ" ) ), std::make_pair( _T( "e" ), _T( "エ" ) ),
				std::make_pair( _T( "fa" ), _T( "ファ" ) ), std::make_pair( _T( "fe" ), _T( "フェ" ) ),
				std::make_pair( _T( "fi" ), _T( "フィ" ) ), std::make_pair( _T( "fo" ), _T( "フォ" ) ),
				std::make_pair( _T( "fu" ), _T( "フ" ) ), std::make_pair( _T( "ga" ), _T( "ガ" ) ),
				std::make_pair( _T( "ge" ), _T( "ゲ" ) ), std::make_pair( _T( "gi" ), _T( "ギ" ) ),
				std::make_pair( _T( "go" ), _T( "ゴ" ) ), std::make_pair( _T( "gu" ), _T( "グ" ) ),
				std::make_pair( _T( "gwa" ), _T( "グァ" ) ), std::make_pair( _T( "gwe" ), _T( "グェ" ) ),
				std::make_pair( _T( "gwi" ), _T( "グィ" ) ), std::make_pair( _T( "gwo" ), _T( "グォ" ) ),
				std::make_pair( _T( "gwu" ), _T( "グ" ) ), std::make_pair( _T( "gya" ), _T( "ギャ" ) ),
				std::make_pair( _T( "gye" ), _T( "ギェ" ) ), std::make_pair( _T( "gyi" ), _T( "ギィ" ) ),
				std::make_pair( _T( "gyo" ), _T( "ギョ" ) ), std::make_pair( _T( "gyu" ), _T( "ギュ" ) ),
				std::make_pair( _T( "ha" ), _T( "ハ" ) ), std::make_pair( _T( "he" ), _T( "ヘ" ) ),
				std::make_pair( _T( "hi" ), _T( "ヒ" ) ), std::make_pair( _T( "ho" ), _T( "ホ" ) ),
				std::make_pair( _T( "hu" ), _T( "フ" ) ), std::make_pair( _T( "hya" ), _T( "ヒャ" ) ),
				std::make_pair( _T( "hye" ), _T( "ヒェ" ) ), std::make_pair( _T( "hyi" ), _T( "ヒィ" ) ),
				std::make_pair( _T( "hyo" ), _T( "ヒョ" ) ), std::make_pair( _T( "hyu" ), _T( "ヒュ" ) ),
				std::make_pair( _T( "i" ), _T( "イ" ) ), std::make_pair( _T( "ja" ), _T( "ジャ" ) ),
				std::make_pair( _T( "je" ), _T( "ジェ" ) ), std::make_pair( _T( "ji" ), _T( "ジ" ) ),
				std::make_pair( _T( "jo" ), _T( "ジョ" ) ), std::make_pair( _T( "ju" ), _T( "ジュ" ) ),
				std::make_pair( _T( "jya" ), _T( "ジャ" ) ), std::make_pair( _T( "jye" ), _T( "ジェ" ) ),
				std::make_pair( _T( "jyi" ), _T( "ジィ" ) ), std::make_pair( _T( "jyo" ), _T( "ジョ" ) ),
				std::make_pair( _T( "jyu" ), _T( "ジュ" ) ), std::make_pair( _T( "ka" ), _T( "カ" ) ),
				std::make_pair( _T( "ke" ), _T( "ケ" ) ), std::make_pair( _T( "ki" ), _T( "キ" ) ),
				std::make_pair( _T( "ko" ), _T( "コ" ) ), std::make_pair( _T( "ku" ), _T( "ク" ) ),
				std::make_pair( _T( "kwa" ), _T( "クヮ" ) ), std::make_pair( _T( "kwe" ), _T( "クェ" ) ),
				std::make_pair( _T( "kwi" ), _T( "クィ" ) ), std::make_pair( _T( "kwo" ), _T( "クォ" ) ),
				std::make_pair( _T( "kwu" ), _T( "ク" ) ), std::make_pair( _T( "kya" ), _T( "キャ" ) ),
				std::make_pair( _T( "kye" ), _T( "キェ" ) ), std::make_pair( _T( "kyi" ), _T( "キィ" ) ),
				std::make_pair( _T( "kyo" ), _T( "キョ" ) ), std::make_pair( _T( "kyu" ), _T( "キュ" ) ),
				std::make_pair( _T( "la" ), _T( "ァ" ) ), std::make_pair( _T( "le" ), _T( "ェ" ) ),
				std::make_pair( _T( "li" ), _T( "ィ" ) ), std::make_pair( _T( "lo" ), _T( "ォ" ) ),
				std::make_pair( _T( "lu" ), _T( "ゥ" ) ), std::make_pair( _T( "lwa" ), _T( "ヮ" ) ),
				std::make_pair( _T( "lya" ), _T( "ャ" ) ), std::make_pair( _T( "lye" ), _T( "ェ" ) ),
				std::make_pair( _T( "lyi" ), _T( "ィ" ) ), std::make_pair( _T( "lyo" ), _T( "ョ" ) ),
				std::make_pair( _T( "lyu" ), _T( "ュ" ) ), std::make_pair( _T( "ma" ), _T( "マ" ) ),
				std::make_pair( _T( "me" ), _T( "メ" ) ), std::make_pair( _T( "mi" ), _T( "ミ" ) ),
				std::make_pair( _T( "mo" ), _T( "モ" ) ), std::make_pair( _T( "mu" ), _T( "ム" ) ),
				std::make_pair( _T( "mya" ), _T( "ミャ" ) ), std::make_pair( _T( "mye" ), _T( "ミェ" ) ),
				std::make_pair( _T( "myi" ), _T( "ミィ" ) ), std::make_pair( _T( "myo" ), _T( "ミョ" ) ),
				std::make_pair( _T( "myu" ), _T( "ミュ" ) ), std::make_pair( _T( "na" ), _T( "ナ" ) ),
				std::make_pair( _T( "ne" ), _T( "ネ" ) ), std::make_pair( _T( "ni" ), _T( "ニ" ) ),
				std::make_pair( _T( "nn" ), _T( "ン" ) ), std::make_pair( _T( "no" ), _T( "ノ" ) ),
				std::make_pair( _T( "nu" ), _T( "ヌ" ) ), std::make_pair( _T( "nya" ), _T( "ニャ" ) ),
				std::make_pair( _T( "nye" ), _T( "ニェ" ) ), std::make_pair( _T( "nyi" ), _T( "ニィ" ) ),
				std::make_pair( _T( "nyo" ), _T( "ニョ" ) ), std::make_pair( _T( "nyu" ), _T( "ニュ" ) ),
				std::make_pair( _T( "o" ), _T( "オ" ) ), std::make_pair( _T( "pa" ), _T( "パ" ) ),
				std::make_pair( _T( "pe" ), _T( "ペ" ) ), std::make_pair( _T( "pi" ), _T( "ピ" ) ),
				std::make_pair( _T( "po" ), _T( "ポ" ) ), std::make_pair( _T( "pu" ), _T( "プ" ) ),
				std::make_pair( _T( "pya" ), _T( "ピャ" ) ), std::make_pair( _T( "pye" ), _T( "ピェ" ) ),
				std::make_pair( _T( "pyi" ), _T( "ピィ" ) ), std::make_pair( _T( "pyo" ), _T( "ピョ" ) ),
				std::make_pair( _T( "pyu" ), _T( "ピュ" ) ), std::make_pair( _T( "qa" ), _T( "クァ" ) ),
				std::make_pair( _T( "qe" ), _T( "クェ" ) ), std::make_pair( _T( "qi" ), _T( "クィ" ) ),
				std::make_pair( _T( "qo" ), _T( "クォ" ) ), std::make_pair( _T( "qu" ), _T( "ク" ) ),
				std::make_pair( _T( "qya" ), _T( "クャ" ) ), std::make_pair( _T( "qye" ), _T( "クェ" ) ),
				std::make_pair( _T( "qyi" ), _T( "クィ" ) ), std::make_pair( _T( "qyo" ), _T( "クョ" ) ),
				std::make_pair( _T( "qyu" ), _T( "クュ" ) ), std::make_pair( _T( "ra" ), _T( "ラ" ) ),
				std::make_pair( _T( "re" ), _T( "レ" ) ), std::make_pair( _T( "ri" ), _T( "リ" ) ),
				std::make_pair( _T( "ro" ), _T( "ロ" ) ), std::make_pair( _T( "ru" ), _T( "ル" ) ),
				std::make_pair( _T( "rya" ), _T( "リャ" ) ), std::make_pair( _T( "rye" ), _T( "リェ" ) ),
				std::make_pair( _T( "ryi" ), _T( "リィ" ) ), std::make_pair( _T( "ryo" ), _T( "リョ" ) ),
				std::make_pair( _T( "ryu" ), _T( "リュ" ) ), std::make_pair( _T( "sa" ), _T( "サ" ) ),
				std::make_pair( _T( "se" ), _T( "セ" ) ), std::make_pair( _T( "sha" ), _T( "シャ" ) ),
				std::make_pair( _T( "she" ), _T( "シェ" ) ), std::make_pair( _T( "shi" ), _T( "シ" ) ),
				std::make_pair( _T( "sho" ), _T( "ショ" ) ), std::make_pair( _T( "shu" ), _T( "シュ" ) ),
				std::make_pair( _T( "si" ), _T( "シ" ) ), std::make_pair( _T( "so" ), _T( "ソ" ) ),
				std::make_pair( _T( "su" ), _T( "ス" ) ), std::make_pair( _T( "sya" ), _T( "シャ" ) ),
				std::make_pair( _T( "sye" ), _T( "シェ" ) ), std::make_pair( _T( "syi" ), _T( "シィ" ) ),
				std::make_pair( _T( "syo" ), _T( "ショ" ) ), std::make_pair( _T( "syu" ), _T( "シュ" ) ),
				std::make_pair( _T( "ta" ), _T( "タ" ) ), std::make_pair( _T( "te" ), _T( "テ" ) ),
				std::make_pair( _T( "tha" ), _T( "テャ" ) ), std::make_pair( _T( "the" ), _T( "テェ" ) ),
				std::make_pair( _T( "thi" ), _T( "ティ" ) ), std::make_pair( _T( "tho" ), _T( "テョ" ) ),
				std::make_pair( _T( "thu" ), _T( "テュ" ) ), std::make_pair( _T( "ti" ), _T( "チ" ) ),
				std::make_pair( _T( "to" ), _T( "ト" ) ), std::make_pair( _T( "tsa" ), _T( "ツァ" ) ),
				std::make_pair( _T( "tse" ), _T( "ツェ" ) ), std::make_pair( _T( "tsi" ), _T( "ツィ" ) ),
				std::make_pair( _T( "tsu" ), _T( "ツ" ) ), std::make_pair( _T( "tu" ), _T( "ツ" ) ),
				std::make_pair( _T( "tso" ), _T( "ツォ" ) ), std::make_pair( _T( "tya" ), _T( "チャ" ) ),
				std::make_pair( _T( "tye" ), _T( "チェ" ) ), std::make_pair( _T( "tyi" ), _T( "チィ" ) ),
				std::make_pair( _T( "tyo" ), _T( "チョ" ) ), std::make_pair( _T( "tyu" ), _T( "チュ" ) ),
				std::make_pair( _T( "u" ), _T( "ウ" ) ), std::make_pair( _T( "va" ), _T( "ヴァ" ) ),
				std::make_pair( _T( "ve" ), _T( "ヴェ" ) ), std::make_pair( _T( "vi" ), _T( "ヴィ" ) ),
				std::make_pair( _T( "vo" ), _T( "ヴォ" ) ), std::make_pair( _T( "vu" ), _T( "ヴ" ) ),
				std::make_pair( _T( "wa" ), _T( "ワ" ) ), std::make_pair( _T( "we" ), _T( "ウェ" ) ),
				std::make_pair( _T( "wi" ), _T( "ウィ" ) ), std::make_pair( _T( "wo" ), _T( "ヲ" ) ),
				std::make_pair( _T( "wu" ), _T( "ウ" ) ), std::make_pair( _T( "xa" ), _T( "ァ" ) ),
				std::make_pair( _T( "xe" ), _T( "ェ" ) ), std::make_pair( _T( "xi" ), _T( "ィ" ) ),
				std::make_pair( _T( "xo" ), _T( "ォ" ) ), std::make_pair( _T( "xtu" ), _T( "ッ" ) ),
				std::make_pair( _T( "xtsu" ), _T( "ッ" ) ), std::make_pair( _T( "xu" ), _T( "ゥ" ) ),
				std::make_pair( _T( "xwa" ), _T( "ヮ" ) ), std::make_pair( _T( "xya" ), _T( "ャ" ) ),
				std::make_pair( _T( "xye" ), _T( "ェ" ) ), std::make_pair( _T( "xyi" ), _T( "ィ" ) ),
				std::make_pair( _T( "xyo" ), _T( "ョ" ) ), std::make_pair( _T( "xyu" ), _T( "ュ" ) ),
				std::make_pair( _T( "ya" ), _T( "ヤ" ) ), std::make_pair( _T( "ye" ), _T( "イェ" ) ),
				std::make_pair( _T( "yi" ), _T( "イ" ) ), std::make_pair( _T( "yo" ), _T( "ヨ" ) ),
				std::make_pair( _T( "yu" ), _T( "ユ" ) ), std::make_pair( _T( "za" ), _T( "ザ" ) ),
				std::make_pair( _T( "ze" ), _T( "ゼ" ) ), std::make_pair( _T( "zi" ), _T( "ジ" ) ),
				std::make_pair( _T( "zo" ), _T( "ゾ" ) ), std::make_pair( _T( "zu" ), _T( "ズ" ) ),
				std::make_pair( _T( "zya" ), _T( "ジャ" ) ), std::make_pair( _T( "zye" ), _T( "ジェ" ) ),
				std::make_pair( _T( "zyi" ), _T( "ジィ" ) ), std::make_pair( _T( "zyo" ), _T( "ジョ" ) ),
				std::make_pair( _T( "zyu" ), _T( "ジュ" ) ), std::make_pair( _T( "-" ), _T( "ー" ) ),
				}
			){}

	CString exec( const CString &str ) {
		CString res = _T( "" );

		auto judge_consonant = []( CString str ) {
			if ( str.GetLength() < 2 )
			{
				return ( false );
			}
			else if ( str[0] == str[1] )
			{
				return ( true );
			}
			else
			{
				return ( false );
			}
		};

		// 文字列が短いことがわかってるので普通に全探索する
		for ( int i = 0; i < str.GetLength(); i++ )
		{
			for ( int j = i + 1; j <= str.GetLength(); ++j )
			{
				CString tmp = m_mapping[str.Mid( i, j - i )];
				if ( tmp.IsEmpty() == FALSE )
				{
					res += tmp;
					i = j - 1; break;
				}
				else if ( judge_consonant( str.Mid( i, j - 1 ) ) )
				{
					res += _T( "ッ" );
					i = j; break; // 子音を一つ残す
				}
			}
		}

		return ( res );
	};
private:
	std::map<CString, CString> m_mapping;
};

struct CalcUtil {
public:
	template<typename T> bool chmax( T &a, const T b ) { if ( a <= b ) { a = b; return ( true ); } else { return ( false ); } }
	template<typename T> bool chmin( T &a, const T b ) { if ( a >= b ) { a = b; return ( true ); } else { return ( false ); } }
};
