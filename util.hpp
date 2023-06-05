#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <map>

struct CTransrateRomaKana {
public:
	CTransrateRomaKana() :
		m_mapping(
			{ std::make_pair( _T( "a" ), _T( "�A" ) ), std::make_pair( _T( "ba" ), _T( "�o" ) ),
				std::make_pair( _T( "be" ), _T( "�x" ) ), std::make_pair( _T( "bi" ), _T( "�r" ) ),
				std::make_pair( _T( "bo" ), _T( "�{" ) ), std::make_pair( _T( "bu" ), _T( "�u" ) ),
				std::make_pair( _T( "bya" ), _T( "�r��" ) ), std::make_pair( _T( "bye" ), _T( "�r�F" ) ),
				std::make_pair( _T( "byi" ), _T( "�r�B" ) ), std::make_pair( _T( "byo" ), _T( "�r��" ) ),
				std::make_pair( _T( "byu" ), _T( "�r��" ) ), std::make_pair( _T( "ca" ), _T( "�J" ) ),
				std::make_pair( _T( "ce" ), _T( "�Z" ) ), std::make_pair( _T( "cha" ), _T( "�`��" ) ),
				std::make_pair( _T( "che" ), _T( "�`�F" ) ), std::make_pair( _T( "chi" ), _T( "�`" ) ),
				std::make_pair( _T( "cho" ), _T( "�`��" ) ), std::make_pair( _T( "chu" ), _T( "�`��" ) ),
				std::make_pair( _T( "ci" ), _T( "�V" ) ), std::make_pair( _T( "co" ), _T( "�R" ) ),
				std::make_pair( _T( "cu" ), _T( "�N" ) ), std::make_pair( _T( "cya" ), _T( "�`��" ) ),
				std::make_pair( _T( "cye" ), _T( "�`�F" ) ), std::make_pair( _T( "cyi" ), _T( "�`�B" ) ),
				std::make_pair( _T( "cyo" ), _T( "�`��" ) ), std::make_pair( _T( "cyu" ), _T( "�`��" ) ),
				std::make_pair( _T( "da" ), _T( "�_" ) ), std::make_pair( _T( "de" ), _T( "�f" ) ),
				std::make_pair( _T( "dha" ), _T( "�f��" ) ), std::make_pair( _T( "dhe" ), _T( "�f�F" ) ),
				std::make_pair( _T( "dhi" ), _T( "�f�B" ) ), std::make_pair( _T( "dho" ), _T( "�f��" ) ),
				std::make_pair( _T( "dhu" ), _T( "�f��" ) ), std::make_pair( _T( "di" ), _T( "�a" ) ),
				std::make_pair( _T( "do" ), _T( "�h" ) ), std::make_pair( _T( "du" ), _T( "�d" ) ),
				std::make_pair( _T( "dya" ), _T( "�a��" ) ), std::make_pair( _T( "dye" ), _T( "�a�F" ) ),
				std::make_pair( _T( "dyi" ), _T( "�a�B" ) ), std::make_pair( _T( "dyo" ), _T( "�a��" ) ),
				std::make_pair( _T( "dyu" ), _T( "�f��" ) ), std::make_pair( _T( "e" ), _T( "�G" ) ),
				std::make_pair( _T( "fa" ), _T( "�t�@" ) ), std::make_pair( _T( "fe" ), _T( "�t�F" ) ),
				std::make_pair( _T( "fi" ), _T( "�t�B" ) ), std::make_pair( _T( "fo" ), _T( "�t�H" ) ),
				std::make_pair( _T( "fu" ), _T( "�t" ) ), std::make_pair( _T( "ga" ), _T( "�K" ) ),
				std::make_pair( _T( "ge" ), _T( "�Q" ) ), std::make_pair( _T( "gi" ), _T( "�M" ) ),
				std::make_pair( _T( "go" ), _T( "�S" ) ), std::make_pair( _T( "gu" ), _T( "�O" ) ),
				std::make_pair( _T( "gwa" ), _T( "�O�@" ) ), std::make_pair( _T( "gwe" ), _T( "�O�F" ) ),
				std::make_pair( _T( "gwi" ), _T( "�O�B" ) ), std::make_pair( _T( "gwo" ), _T( "�O�H" ) ),
				std::make_pair( _T( "gwu" ), _T( "�O" ) ), std::make_pair( _T( "gya" ), _T( "�M��" ) ),
				std::make_pair( _T( "gye" ), _T( "�M�F" ) ), std::make_pair( _T( "gyi" ), _T( "�M�B" ) ),
				std::make_pair( _T( "gyo" ), _T( "�M��" ) ), std::make_pair( _T( "gyu" ), _T( "�M��" ) ),
				std::make_pair( _T( "ha" ), _T( "�n" ) ), std::make_pair( _T( "he" ), _T( "�w" ) ),
				std::make_pair( _T( "hi" ), _T( "�q" ) ), std::make_pair( _T( "ho" ), _T( "�z" ) ),
				std::make_pair( _T( "hu" ), _T( "�t" ) ), std::make_pair( _T( "hya" ), _T( "�q��" ) ),
				std::make_pair( _T( "hye" ), _T( "�q�F" ) ), std::make_pair( _T( "hyi" ), _T( "�q�B" ) ),
				std::make_pair( _T( "hyo" ), _T( "�q��" ) ), std::make_pair( _T( "hyu" ), _T( "�q��" ) ),
				std::make_pair( _T( "i" ), _T( "�C" ) ), std::make_pair( _T( "ja" ), _T( "�W��" ) ),
				std::make_pair( _T( "je" ), _T( "�W�F" ) ), std::make_pair( _T( "ji" ), _T( "�W" ) ),
				std::make_pair( _T( "jo" ), _T( "�W��" ) ), std::make_pair( _T( "ju" ), _T( "�W��" ) ),
				std::make_pair( _T( "jya" ), _T( "�W��" ) ), std::make_pair( _T( "jye" ), _T( "�W�F" ) ),
				std::make_pair( _T( "jyi" ), _T( "�W�B" ) ), std::make_pair( _T( "jyo" ), _T( "�W��" ) ),
				std::make_pair( _T( "jyu" ), _T( "�W��" ) ), std::make_pair( _T( "ka" ), _T( "�J" ) ),
				std::make_pair( _T( "ke" ), _T( "�P" ) ), std::make_pair( _T( "ki" ), _T( "�L" ) ),
				std::make_pair( _T( "ko" ), _T( "�R" ) ), std::make_pair( _T( "ku" ), _T( "�N" ) ),
				std::make_pair( _T( "kwa" ), _T( "�N��" ) ), std::make_pair( _T( "kwe" ), _T( "�N�F" ) ),
				std::make_pair( _T( "kwi" ), _T( "�N�B" ) ), std::make_pair( _T( "kwo" ), _T( "�N�H" ) ),
				std::make_pair( _T( "kwu" ), _T( "�N" ) ), std::make_pair( _T( "kya" ), _T( "�L��" ) ),
				std::make_pair( _T( "kye" ), _T( "�L�F" ) ), std::make_pair( _T( "kyi" ), _T( "�L�B" ) ),
				std::make_pair( _T( "kyo" ), _T( "�L��" ) ), std::make_pair( _T( "kyu" ), _T( "�L��" ) ),
				std::make_pair( _T( "la" ), _T( "�@" ) ), std::make_pair( _T( "le" ), _T( "�F" ) ),
				std::make_pair( _T( "li" ), _T( "�B" ) ), std::make_pair( _T( "lo" ), _T( "�H" ) ),
				std::make_pair( _T( "lu" ), _T( "�D" ) ), std::make_pair( _T( "lwa" ), _T( "��" ) ),
				std::make_pair( _T( "lya" ), _T( "��" ) ), std::make_pair( _T( "lye" ), _T( "�F" ) ),
				std::make_pair( _T( "lyi" ), _T( "�B" ) ), std::make_pair( _T( "lyo" ), _T( "��" ) ),
				std::make_pair( _T( "lyu" ), _T( "��" ) ), std::make_pair( _T( "ma" ), _T( "�}" ) ),
				std::make_pair( _T( "me" ), _T( "��" ) ), std::make_pair( _T( "mi" ), _T( "�~" ) ),
				std::make_pair( _T( "mo" ), _T( "��" ) ), std::make_pair( _T( "mu" ), _T( "��" ) ),
				std::make_pair( _T( "mya" ), _T( "�~��" ) ), std::make_pair( _T( "mye" ), _T( "�~�F" ) ),
				std::make_pair( _T( "myi" ), _T( "�~�B" ) ), std::make_pair( _T( "myo" ), _T( "�~��" ) ),
				std::make_pair( _T( "myu" ), _T( "�~��" ) ), std::make_pair( _T( "na" ), _T( "�i" ) ),
				std::make_pair( _T( "ne" ), _T( "�l" ) ), std::make_pair( _T( "ni" ), _T( "�j" ) ),
				std::make_pair( _T( "nn" ), _T( "��" ) ), std::make_pair( _T( "no" ), _T( "�m" ) ),
				std::make_pair( _T( "nu" ), _T( "�k" ) ), std::make_pair( _T( "nya" ), _T( "�j��" ) ),
				std::make_pair( _T( "nye" ), _T( "�j�F" ) ), std::make_pair( _T( "nyi" ), _T( "�j�B" ) ),
				std::make_pair( _T( "nyo" ), _T( "�j��" ) ), std::make_pair( _T( "nyu" ), _T( "�j��" ) ),
				std::make_pair( _T( "o" ), _T( "�I" ) ), std::make_pair( _T( "pa" ), _T( "�p" ) ),
				std::make_pair( _T( "pe" ), _T( "�y" ) ), std::make_pair( _T( "pi" ), _T( "�s" ) ),
				std::make_pair( _T( "po" ), _T( "�|" ) ), std::make_pair( _T( "pu" ), _T( "�v" ) ),
				std::make_pair( _T( "pya" ), _T( "�s��" ) ), std::make_pair( _T( "pye" ), _T( "�s�F" ) ),
				std::make_pair( _T( "pyi" ), _T( "�s�B" ) ), std::make_pair( _T( "pyo" ), _T( "�s��" ) ),
				std::make_pair( _T( "pyu" ), _T( "�s��" ) ), std::make_pair( _T( "qa" ), _T( "�N�@" ) ),
				std::make_pair( _T( "qe" ), _T( "�N�F" ) ), std::make_pair( _T( "qi" ), _T( "�N�B" ) ),
				std::make_pair( _T( "qo" ), _T( "�N�H" ) ), std::make_pair( _T( "qu" ), _T( "�N" ) ),
				std::make_pair( _T( "qya" ), _T( "�N��" ) ), std::make_pair( _T( "qye" ), _T( "�N�F" ) ),
				std::make_pair( _T( "qyi" ), _T( "�N�B" ) ), std::make_pair( _T( "qyo" ), _T( "�N��" ) ),
				std::make_pair( _T( "qyu" ), _T( "�N��" ) ), std::make_pair( _T( "ra" ), _T( "��" ) ),
				std::make_pair( _T( "re" ), _T( "��" ) ), std::make_pair( _T( "ri" ), _T( "��" ) ),
				std::make_pair( _T( "ro" ), _T( "��" ) ), std::make_pair( _T( "ru" ), _T( "��" ) ),
				std::make_pair( _T( "rya" ), _T( "����" ) ), std::make_pair( _T( "rye" ), _T( "���F" ) ),
				std::make_pair( _T( "ryi" ), _T( "���B" ) ), std::make_pair( _T( "ryo" ), _T( "����" ) ),
				std::make_pair( _T( "ryu" ), _T( "����" ) ), std::make_pair( _T( "sa" ), _T( "�T" ) ),
				std::make_pair( _T( "se" ), _T( "�Z" ) ), std::make_pair( _T( "sha" ), _T( "�V��" ) ),
				std::make_pair( _T( "she" ), _T( "�V�F" ) ), std::make_pair( _T( "shi" ), _T( "�V" ) ),
				std::make_pair( _T( "sho" ), _T( "�V��" ) ), std::make_pair( _T( "shu" ), _T( "�V��" ) ),
				std::make_pair( _T( "si" ), _T( "�V" ) ), std::make_pair( _T( "so" ), _T( "�\" ) ),
				std::make_pair( _T( "su" ), _T( "�X" ) ), std::make_pair( _T( "sya" ), _T( "�V��" ) ),
				std::make_pair( _T( "sye" ), _T( "�V�F" ) ), std::make_pair( _T( "syi" ), _T( "�V�B" ) ),
				std::make_pair( _T( "syo" ), _T( "�V��" ) ), std::make_pair( _T( "syu" ), _T( "�V��" ) ),
				std::make_pair( _T( "ta" ), _T( "�^" ) ), std::make_pair( _T( "te" ), _T( "�e" ) ),
				std::make_pair( _T( "tha" ), _T( "�e��" ) ), std::make_pair( _T( "the" ), _T( "�e�F" ) ),
				std::make_pair( _T( "thi" ), _T( "�e�B" ) ), std::make_pair( _T( "tho" ), _T( "�e��" ) ),
				std::make_pair( _T( "thu" ), _T( "�e��" ) ), std::make_pair( _T( "ti" ), _T( "�`" ) ),
				std::make_pair( _T( "to" ), _T( "�g" ) ), std::make_pair( _T( "tsa" ), _T( "�c�@" ) ),
				std::make_pair( _T( "tse" ), _T( "�c�F" ) ), std::make_pair( _T( "tsi" ), _T( "�c�B" ) ),
				std::make_pair( _T( "tsu" ), _T( "�c" ) ), std::make_pair( _T( "tu" ), _T( "�c" ) ),
				std::make_pair( _T( "tso" ), _T( "�c�H" ) ), std::make_pair( _T( "tya" ), _T( "�`��" ) ),
				std::make_pair( _T( "tye" ), _T( "�`�F" ) ), std::make_pair( _T( "tyi" ), _T( "�`�B" ) ),
				std::make_pair( _T( "tyo" ), _T( "�`��" ) ), std::make_pair( _T( "tyu" ), _T( "�`��" ) ),
				std::make_pair( _T( "u" ), _T( "�E" ) ), std::make_pair( _T( "va" ), _T( "���@" ) ),
				std::make_pair( _T( "ve" ), _T( "���F" ) ), std::make_pair( _T( "vi" ), _T( "���B" ) ),
				std::make_pair( _T( "vo" ), _T( "���H" ) ), std::make_pair( _T( "vu" ), _T( "��" ) ),
				std::make_pair( _T( "wa" ), _T( "��" ) ), std::make_pair( _T( "we" ), _T( "�E�F" ) ),
				std::make_pair( _T( "wi" ), _T( "�E�B" ) ), std::make_pair( _T( "wo" ), _T( "��" ) ),
				std::make_pair( _T( "wu" ), _T( "�E" ) ), std::make_pair( _T( "xa" ), _T( "�@" ) ),
				std::make_pair( _T( "xe" ), _T( "�F" ) ), std::make_pair( _T( "xi" ), _T( "�B" ) ),
				std::make_pair( _T( "xo" ), _T( "�H" ) ), std::make_pair( _T( "xtu" ), _T( "�b" ) ),
				std::make_pair( _T( "xtsu" ), _T( "�b" ) ), std::make_pair( _T( "xu" ), _T( "�D" ) ),
				std::make_pair( _T( "xwa" ), _T( "��" ) ), std::make_pair( _T( "xya" ), _T( "��" ) ),
				std::make_pair( _T( "xye" ), _T( "�F" ) ), std::make_pair( _T( "xyi" ), _T( "�B" ) ),
				std::make_pair( _T( "xyo" ), _T( "��" ) ), std::make_pair( _T( "xyu" ), _T( "��" ) ),
				std::make_pair( _T( "ya" ), _T( "��" ) ), std::make_pair( _T( "ye" ), _T( "�C�F" ) ),
				std::make_pair( _T( "yi" ), _T( "�C" ) ), std::make_pair( _T( "yo" ), _T( "��" ) ),
				std::make_pair( _T( "yu" ), _T( "��" ) ), std::make_pair( _T( "za" ), _T( "�U" ) ),
				std::make_pair( _T( "ze" ), _T( "�[" ) ), std::make_pair( _T( "zi" ), _T( "�W" ) ),
				std::make_pair( _T( "zo" ), _T( "�]" ) ), std::make_pair( _T( "zu" ), _T( "�Y" ) ),
				std::make_pair( _T( "zya" ), _T( "�W��" ) ), std::make_pair( _T( "zye" ), _T( "�W�F" ) ),
				std::make_pair( _T( "zyi" ), _T( "�W�B" ) ), std::make_pair( _T( "zyo" ), _T( "�W��" ) ),
				std::make_pair( _T( "zyu" ), _T( "�W��" ) ), std::make_pair( _T( "-" ), _T( "�[" ) ),
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

		// �����񂪒Z�����Ƃ��킩���Ă�̂ŕ��ʂɑS�T������
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
					res += _T( "�b" );
					i = j; break; // �q������c��
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
