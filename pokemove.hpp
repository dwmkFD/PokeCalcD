#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <string>
#include <memory>
#include <map>

/* �Z�̒�` */


// [�]�k]�킴�͉p��łł́umove�v�Ȃ̂����A�F�X�Ƌ����������Ȃ̂ŁAPokeMove�ɂ��Ă�����
class PokeMove {
public:
	PokeMove( CString name, CString type, int category, int power, int accuracy, bool direct )
	{
		m_name = name; m_type = type; m_category = category;
		m_power = power; m_accuracy = accuracy; m_direct = direct;
		m_range = -1;
	}

	void setRange( int range ) { m_range = range; }
	static int getCategory( CString strCategory ) {
		if ( strCategory == _T( "����" ) ) return ( -1 );
		else if ( strCategory == _T( "�ω�" ) ) return ( 0 );
		else return ( 1 );
	}

	CString m_name; // �Z��
	CString m_type; // �Z�̃^�C�v
	int m_category; // �Z�̕��ށi���� -1�A�ω��Z 0�A���� 1�j
	int m_power; // �Z�̈З�
	int m_accuracy; // �Z�̖�����
	int m_range; // �Z�͈̔́i�P�� -1�A�S�� 1�A����S�� 1 �� �_�u���ňЗ͂̔���Ɏg�p����(��҂͈�ɂ܂Ƃ߂Ă��ǂ���������Ȃ�)�j
	bool m_direct; // �ڐG�U�����ۂ��i�L���Ƃ��̔����ŗ����邩�ǂ������v�Z���ʂɊ܂ނȂ�j
};

// �^�C�v����
struct TypeCompatibility {
	// �U����(type1)����h�䑤(type2)�ւ̑����v�Z
	// �߂�l�͔{��( 0�A1/4�A1/2�A1�A2�A4�A8�j
	// ���Ⴆ�΁A�����h���X���X�̎􂢂��󂯂�ƕX��8�{�ɂȂ�̂ŁA�ꉞ8�܂ł��蓾��
	// �@���Ǝv�������ǁA�����ł͂����܂ŒP�^�C�v�Ƃ��Ă�����r���ĂȂ�����A0�`2�܂ł����Ȃ���
	double check( const std::string &type1, const std::string &type2 ) const {
		return ( m_table[m_typetable.at( type1 )][m_typetable.at( type2 )] );
	}

	TypeCompatibility() {
		// �^�C�v���𐔒l�ɕϊ����邽�߂̃e�[�u��
		m_typetable["�m�[�}��"] = 0; m_typetable["�ق̂�"] = 1;
		m_typetable["�݂�"] = 2; m_typetable["�ł�"] = 3;
		m_typetable["����"] = 4; m_typetable["������"] = 5;
		m_typetable["�����Ƃ�"] = 6; m_typetable["�ǂ�"] = 7;
		m_typetable["���߂�"] = 8; m_typetable["�Ђ���"] = 9;
		m_typetable["�G�X�p�["] = 10; m_typetable["�ނ�"] = 11;
		m_typetable["����"] = 12; m_typetable["�S�[�X�g"] = 13;
		m_typetable["�h���S��"] = 14; m_typetable["����"] = 15;
		m_typetable["�͂���"] = 16; m_typetable["�t�F�A���["] = 17;

		// �^�C�v�������v�Z����e�[�u��
		m_table.assign( 18, std::vector<double>( 18, 1 ) );

		// �m�[�}���i��_�F�Ȃ��A�����F����E�͂��ˁA�����F�S�[�X�g�j
		m_table[m_typetable["�m�[�}��"]][m_typetable["����"]]
			= m_table[m_typetable["�m�[�}��"]][m_typetable["�͂���"]] = 0.5;
		m_table[m_typetable["�m�[�}��"]][m_typetable["�S�[�X�g"]] = 0;

		// �ق̂��i��_�F�����E������E�ނ��E�͂��ˁA�����F�݂��E����E�h���S���A�����F�Ȃ��j
		m_table[m_typetable["�ق̂�"]][m_typetable["����"]]
			= m_table[m_typetable["�ق̂�"]][m_typetable["������"]]
			= m_table[m_typetable["�ق̂�"]][m_typetable["�ނ�"]]
			= m_table[m_typetable["�ق̂�"]][m_typetable["�͂���"]] = 2;
		m_table[m_typetable["�ق̂�"]][m_typetable["�݂�"]]
			= m_table[m_typetable["�ق̂�"]][m_typetable["����"]]
			= m_table[m_typetable["�ق̂�"]][m_typetable["�h���S��"]] = 0.5;

		// �݂��i��_�F�ق̂��E���߂�E����A�����F�݂��E�h���S���A�����F�Ȃ��j
		m_table[m_typetable["�݂�"]][m_typetable["�ق̂�"]]
			= m_table[m_typetable["�݂�"]][m_typetable["���߂�"]]
			= m_table[m_typetable["�݂�"]][m_typetable["����"]] = 2;
		m_table[m_typetable["�݂�"]][m_typetable["�݂�"]]
			= m_table[m_typetable["�݂�"]][m_typetable["�h���S��"]] = 0.5;

		// �ł񂫁i��_�F�݂��E�Ђ����A�����F�����E�ł񂫁E�h���S���A�����F���߂�j
		m_table[m_typetable["�ł�"]][m_typetable["�݂�"]]
			= m_table[m_typetable["�ł�"]][m_typetable["�Ђ���"]] = 2;
		m_table[m_typetable["�ł�"]][m_typetable["����"]]
			= m_table[m_typetable["�ł�"]][m_typetable["�ł�"]]
			= m_table[m_typetable["�ł�"]][m_typetable["�h���S��"]] = 0.5;
		m_table[m_typetable["�ł�"]][m_typetable["���߂�"]] = 0;

		// �����i��_�F�݂��E���߂�E����A�����F�ق̂��E�����E�ǂ��E�Ђ����E�ނ��E�h���S���E�͂��ˁA�����F�Ȃ��j
		m_table[m_typetable["����"]][m_typetable["�݂�"]]
			= m_table[m_typetable["����"]][m_typetable["���߂�"]]
			= m_table[m_typetable["����"]][m_typetable["����"]] = 2;
		m_table[m_typetable["����"]][m_typetable["�ق̂�"]]
			= m_table[m_typetable["����"]][m_typetable["����"]]
			= m_table[m_typetable["����"]][m_typetable["�ǂ�"]]
			= m_table[m_typetable["����"]][m_typetable["�Ђ���"]]
			= m_table[m_typetable["����"]][m_typetable["�ނ�"]]
			= m_table[m_typetable["����"]][m_typetable["�h���S��"]]
			= m_table[m_typetable["����"]][m_typetable["�͂���"]] = 0.5;

		// ������i��_�F�����E���߂�E�Ђ����E�h���S���A�����F������A�����F�Ȃ��j
		m_table[m_typetable["������"]][m_typetable["����"]]
			= m_table[m_typetable["������"]][m_typetable["���߂�"]]
			= m_table[m_typetable["������"]][m_typetable["�Ђ���"]]
			= m_table[m_typetable["������"]][m_typetable["�h���S��"]] = 2;
		m_table[m_typetable["������"]][m_typetable["������"]] = 0.5;

		// �����Ƃ��i��_�F�m�[�}���E������E����E�����E�͂��ˁA�����F�ǂ��E�Ђ����E�G�X�p�[�E�ނ��E�t�F�A���[�A�����F�S�[�X�g�j
		m_table[m_typetable["�����Ƃ�"]][m_typetable["�m�[�}��"]]
			= m_table[m_typetable["�����Ƃ�"]][m_typetable["������"]]
			= m_table[m_typetable["�����Ƃ�"]][m_typetable["����"]]
			= m_table[m_typetable["�����Ƃ�"]][m_typetable["����"]]
			= m_table[m_typetable["�����Ƃ�"]][m_typetable["�͂���"]] = 2;
		m_table[m_typetable["�����Ƃ�"]][m_typetable["�ǂ�"]]
			= m_table[m_typetable["�����Ƃ�"]][m_typetable["�Ђ���"]]
			= m_table[m_typetable["�����Ƃ�"]][m_typetable["�G�X�p�["]]
			= m_table[m_typetable["�����Ƃ�"]][m_typetable["�ނ�"]]
			= m_table[m_typetable["�����Ƃ�"]][m_typetable["�t�F�A���["]] = 0.5;
		m_table[m_typetable["�����Ƃ�"]][m_typetable["�S�[�X�g"]] = 0;

		// �ǂ��i��_�F�����E�t�F�A���[�A�����F�ǂ��E���߂�E����E�S�[�X�g�A�����F�͂��ˁj
		m_table[m_typetable["�ǂ�"]][m_typetable["����"]]
			= m_table[m_typetable["�ǂ�"]][m_typetable["�t�F�A���["]] = 2;
		m_table[m_typetable["�ǂ�"]][m_typetable["�ǂ�"]]
			= m_table[m_typetable["�ǂ�"]][m_typetable["���߂�"]]
			= m_table[m_typetable["�ǂ�"]][m_typetable["����"]]
			= m_table[m_typetable["�ǂ�"]][m_typetable["�S�[�X�g"]] = 0.5;
		m_table[m_typetable["�ǂ�"]][m_typetable["�͂���"]] = 0;

		// ���߂�i��_�F�ق̂��E�ł񂫁E�ǂ��E����E�͂��ˁA�����F�����E�ނ��A�����F�Ђ����j
		m_table[m_typetable["���߂�"]][m_typetable["�ق̂�"]]
			= m_table[m_typetable["���߂�"]][m_typetable["�ł�"]]
			= m_table[m_typetable["���߂�"]][m_typetable["�ǂ�"]]
			= m_table[m_typetable["���߂�"]][m_typetable["����"]]
			= m_table[m_typetable["���߂�"]][m_typetable["�͂���"]] = 2;
		m_table[m_typetable["���߂�"]][m_typetable["����"]]
			= m_table[m_typetable["���߂�"]][m_typetable["�ނ�"]] = 0.5;
		m_table[m_typetable["���߂�"]][m_typetable["�Ђ���"]] = 0;

		// �Ђ����i��_�F�����E�����Ƃ��E�ނ��A�����F����E�͂��ˁA�����F�Ȃ��j
		m_table[m_typetable["�Ђ���"]][m_typetable["����"]]
			= m_table[m_typetable["�Ђ���"]][m_typetable["�����Ƃ�"]]
			= m_table[m_typetable["�Ђ���"]][m_typetable["�ނ�"]] = 2;
		m_table[m_typetable["�Ђ���"]][m_typetable["����"]]
			= m_table[m_typetable["�Ђ���"]][m_typetable["�͂���"]] = 0.5;

		// �G�X�p�[�i��_�F�����Ƃ��E�ǂ��A�����F�G�X�p�[�E�͂��ˁA�����F�����j
		m_table[m_typetable["�G�X�p�["]][m_typetable["�����Ƃ�"]]
			= m_table[m_typetable["�G�X�p�["]][m_typetable["�ǂ�"]] = 2;
		m_table[m_typetable["�G�X�p�["]][m_typetable["�G�X�p�["]]
			= m_table[m_typetable["�G�X�p�["]][m_typetable["�͂���"]] = 0.5;
		m_table[m_typetable["�G�X�p�["]][m_typetable["����"]] = 0;

		// �ނ��i��_�F�����E�G�X�p�[�E�����A�����F�ق̂��E�����Ƃ��E�ǂ��E�Ђ����E�S�[�X�g�E�͂��ˁE�t�F�A���[�A�����F�Ȃ��j
		m_table[m_typetable["�Ђ���"]][m_typetable["����"]]
			= m_table[m_typetable["�Ђ���"]][m_typetable["�����Ƃ�"]]
			= m_table[m_typetable["�Ђ���"]][m_typetable["�ނ�"]] = 2;
		m_table[m_typetable["�Ђ���"]][m_typetable["����"]]
			= m_table[m_typetable["�Ђ���"]][m_typetable["�͂���"]] = 0.5;

		// ����i��_�F�ق̂��E������E�Ђ����E�ނ��A�����F�����Ƃ��E���߂�E�͂��ˁA�����F�Ȃ��j
		m_table[m_typetable["����"]][m_typetable["�ق̂�"]]
			= m_table[m_typetable["����"]][m_typetable["������"]]
			= m_table[m_typetable["����"]][m_typetable["�Ђ���"]]
			= m_table[m_typetable["����"]][m_typetable["�ނ�"]] = 2;
		m_table[m_typetable["����"]][m_typetable["�����Ƃ�"]]
			= m_table[m_typetable["����"]][m_typetable["���߂�"]]
			= m_table[m_typetable["����"]][m_typetable["�͂���"]] = 0.5;

		// �S�[�X�g�i��_�F�G�X�p�[�E�S�[�X�g�A�����F�����A�����F�m�[�}���j
		m_table[m_typetable["�S�[�X�g"]][m_typetable["�S�[�X�g"]]
			= m_table[m_typetable["�S�[�X�g"]][m_typetable["�G�X�p�["]] = 2;
		m_table[m_typetable["�S�[�X�g"]][m_typetable["����"]] = 0.5;
		m_table[m_typetable["�S�[�X�g"]][m_typetable["�m�[�}��"]] = 0;

		// �h���S���i��_�F�h���S���A�����F�͂��ˁA�����F�t�F�A���[�j
		m_table[m_typetable["�h���S��"]][m_typetable["�h���S��"]] = 2;
		m_table[m_typetable["�h���S��"]][m_typetable["�͂���"]] = 0.5;
		m_table[m_typetable["�h���S��"]][m_typetable["�t�F�A���["]] = 0;

		// �����i��_�F�G�X�p�[�E�S�[�X�g�A�����F�����E�t�F�A���[�A�����F�Ȃ��j
		m_table[m_typetable["����"]][m_typetable["�G�X�p�["]]
			= m_table[m_typetable["����"]][m_typetable["�S�[�X�g"]] = 2;
		m_table[m_typetable["����"]][m_typetable["����"]]
			= m_table[m_typetable["����"]][m_typetable["�t�F�A���["]] = 0.5;

		// �͂��ˁi��_�F������E����E�t�F�A���[�A�����F�ق̂��E�݂��E�ł񂫁E�͂��ˁA�����F�Ȃ��j
		m_table[m_typetable["�͂���"]][m_typetable["������"]]
			= m_table[m_typetable["�͂���"]][m_typetable["����"]]
			= m_table[m_typetable["�͂���"]][m_typetable["�t�F�A���["]] = 2;
		m_table[m_typetable["�͂���"]][m_typetable["�ق̂�"]]
			= m_table[m_typetable["�͂���"]][m_typetable["�݂�"]]
			= m_table[m_typetable["�͂���"]][m_typetable["�ł�"]]
			= m_table[m_typetable["�͂���"]][m_typetable["�͂���"]] = 0.5;

		// �t�F�A���[�i��_�F�����Ƃ��E�h���S���E�����A�����F�ق̂��E�ǂ��E�͂��ˁA�����F�Ȃ��j
		m_table[m_typetable["�t�F�A���["]][m_typetable["�����Ƃ�"]]
			= m_table[m_typetable["�t�F�A���["]][m_typetable["�h���S��"]]
			= m_table[m_typetable["�t�F�A���["]][m_typetable["����"]] = 2;
		m_table[m_typetable["�t�F�A���["]][m_typetable["�ق̂�"]]
			= m_table[m_typetable["�t�F�A���["]][m_typetable["�ǂ�"]]
			= m_table[m_typetable["�t�F�A���["]][m_typetable["�͂���"]] = 0.5;
	}

private:
	std::vector<std::vector<double>> m_table; // �����ϊ��e�[�u��
	std::map<std::string, int> m_typetable; // �^�C�v���̕ϊ��e�[�u��
};

// ��������
// �������`����H�߂������ς����c��