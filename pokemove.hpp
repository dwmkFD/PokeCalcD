#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "poketype.hpp"

/* �Z�̒�` */


// [�]�k]�킴�͉p��łł́umove�v�Ȃ̂����A�F�X�Ƌ����������Ȃ̂ŁAPokeMove�ɂ��Ă�����
class PokeMove {
public:
	PokeMove() = default;

	PokeMove( CString name, CString type, int category, int power, int accuracy, bool direct, int critical = 0 )
	{
		m_name = name; m_type = type; m_category = category;
		m_power = power; m_accuracy = accuracy; m_direct = direct;
		m_range = -1; m_critical = critical;
		// �ZDB��ҏW����܂ł͋}���ɓ�����₷���Z�͖����Ƃ���
		// �}���Z��������Ȃ��āA�������Ȃ鑊��ɕK���E�З�2�{�Ƃ��A�{�Z�A���Z�cetc���K�v
		// -> ����DB�ł��A�������ɏ����Ă���C�����邩��A��������E���H
	}

	void setRange( int range ) { m_range = range; }
	static int getCategory( CString strCategory ) {
		if ( strCategory == _T( "����" ) ) return ( 1 );
		else if ( strCategory == _T( "�ω�" ) ) return ( 0 );
		else return ( 2 );
	}

	// �Z���ރ`�F�b�N
	// -> TODO: �e���o�[�X�g�݂����Ȍ��̕��ނ���ς���́A��p�̃r�b�g�����H�i�Ǒ��̔���� -> �����l�ƃ����N�␳���ĕ�option�؂�ւ��Ȃ��Ƃˁc�j
	static constexpr unsigned int PHYSICS_CHECK = 0x1;
	static constexpr unsigned int SPECIAL_CHECK = 0x2;

	CString m_name; // �Z��
	CString m_type; // �Z�̃^�C�v
	int m_category; // �Z�̕��ށi���� bit0�A���� bit1�A�ω��Z bit0/1�Ƃ���OFF�j
	int m_power; // �Z�̈З�
	int m_accuracy; // �Z�̖�����
	int m_range; // �Z�͈̔́i�P�� 4096�A�S�̂���ё���S�� 3072 �� �_�u���ňЗ͂̔���Ɏg�p����j // 3072�ŗǂ����ǂ����͗v�����I
	bool m_direct; // �ڐG�U�����ۂ��i�L���Ƃ��̔����ŗ����邩�ǂ������v�Z���ʂɊ܂ނȂ�j
	int m_critical; // �}���ɓ�����₷���Z���H
};

// �^�C�v����
struct TypeCompatibility {
	// �U����(type1)����h�䑤(type2)�ւ̑����v�Z
	// �߂�l�͔{��( 0�A1/4�A1/2�A1�A2�A4�A8�j
	// ���Ⴆ�΁A�����h���X���X�̎􂢂��󂯂�ƕX��8�{�ɂȂ�̂ŁA�ꉞ8�܂ł��蓾��
	// �@���Ǝv�������ǁA�����ł͂����܂ŒP�^�C�v�Ƃ��Ă�����r���ĂȂ�����A0�`2�܂ł����Ȃ���
	double check( const CString &type1, const CString &type2 ) const {
		return ( m_table[m_typetable.at( type1 )][m_typetable.at( type2 )] );
	}

	TypeCompatibility() {
		// �^�C�v���𐔒l�ɕϊ����邽�߂̃e�[�u��
		PokeType pt;
		m_typetable = pt.getTypeTable();

		// �^�C�v�������v�Z����e�[�u��
		m_table.assign( 19, std::vector<double>( 19, 1 ) );

		// �m�[�}���i��_�F�Ȃ��A�����F����E�͂��ˁA�����F�S�[�X�g�j
		m_table[m_typetable[_T( "�m�[�}��" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�m�[�}��" )]][m_typetable[_T( "�͂���" )]] = 0.5;
		m_table[m_typetable[_T( "�m�[�}��" )]][m_typetable[_T( "�S�[�X�g" )]] = 0;

		// �ق̂��i��_�F�����E������E�ނ��E�͂��ˁA�����F�݂��E����E�h���S���A�����F�Ȃ��j
		m_table[m_typetable[_T( "�ق̂�" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�ق̂�" )]][m_typetable[_T( "������" )]]
			= m_table[m_typetable[_T( "�ق̂�" )]][m_typetable[_T( "�ނ�" )]]
			= m_table[m_typetable[_T( "�ق̂�" )]][m_typetable[_T( "�͂���" )]] = 2;
		m_table[m_typetable[_T( "�ق̂�" )]][m_typetable[_T( "�݂�" )]]
			= m_table[m_typetable[_T( "�ق̂�" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�ق̂�" )]][m_typetable[_T( "�h���S��" )]] = 0.5;

		// �݂��i��_�F�ق̂��E���߂�E����A�����F�݂��E�h���S���A�����F�Ȃ��j
		m_table[m_typetable[_T( "�݂�" )]][m_typetable[_T( "�ق̂�" )]]
			= m_table[m_typetable[_T( "�݂�" )]][m_typetable[_T( "���߂�" )]]
			= m_table[m_typetable[_T( "�݂�" )]][m_typetable[_T( "����" )]] = 2;
		m_table[m_typetable[_T( "�݂�" )]][m_typetable[_T( "�݂�" )]]
			= m_table[m_typetable[_T( "�݂�" )]][m_typetable[_T( "�h���S��" )]] = 0.5;

		// �ł񂫁i��_�F�݂��E�Ђ����A�����F�����E�ł񂫁E�h���S���A�����F���߂�j
		m_table[m_typetable[_T( "�ł�" )]][m_typetable[_T( "�݂�" )]]
			= m_table[m_typetable[_T( "�ł�" )]][m_typetable[_T( "�Ђ���" )]] = 2;
		m_table[m_typetable[_T( "�ł�" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�ł�" )]][m_typetable[_T( "�ł�" )]]
			= m_table[m_typetable[_T( "�ł�" )]][m_typetable[_T( "�h���S��" )]] = 0.5;
		m_table[m_typetable[_T( "�ł�" )]][m_typetable[_T( "���߂�" )]] = 0;

		// �����i��_�F�݂��E���߂�E����A�����F�ق̂��E�����E�ǂ��E�Ђ����E�ނ��E�h���S���E�͂��ˁA�����F�Ȃ��j
		m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�݂�" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "���߂�" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "����" )]] = 2;
		m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�ق̂�" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�ǂ�" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�Ђ���" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�ނ�" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�h���S��" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�͂���" )]] = 0.5;

		// ������i��_�F�����E���߂�E�Ђ����E�h���S���A�����F������A�����F�Ȃ��j
		m_table[m_typetable[_T( "������" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "������" )]][m_typetable[_T( "���߂�" )]]
			= m_table[m_typetable[_T( "������" )]][m_typetable[_T( "�Ђ���" )]]
			= m_table[m_typetable[_T( "������" )]][m_typetable[_T( "�h���S��" )]] = 2;
		m_table[m_typetable[_T( "������" )]][m_typetable[_T( "������" )]] = 0.5;

		// �����Ƃ��i��_�F�m�[�}���E������E����E�����E�͂��ˁA�����F�ǂ��E�Ђ����E�G�X�p�[�E�ނ��E�t�F�A���[�A�����F�S�[�X�g�j
		m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "�m�[�}��" )]]
			= m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "������" )]]
			= m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "�͂���" )]] = 2;
		m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "�ǂ�" )]]
			= m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "�Ђ���" )]]
			= m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "�G�X�p�[" )]]
			= m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "�ނ�" )]]
			= m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "�t�F�A���[" )]] = 0.5;
		m_table[m_typetable[_T( "�����Ƃ�" )]][m_typetable[_T( "�S�[�X�g" )]] = 0;

		// �ǂ��i��_�F�����E�t�F�A���[�A�����F�ǂ��E���߂�E����E�S�[�X�g�A�����F�͂��ˁj
		m_table[m_typetable[_T( "�ǂ�" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�ǂ�" )]][m_typetable[_T( "�t�F�A���[" )]] = 2;
		m_table[m_typetable[_T( "�ǂ�" )]][m_typetable[_T( "�ǂ�" )]]
			= m_table[m_typetable[_T( "�ǂ�" )]][m_typetable[_T( "���߂�" )]]
			= m_table[m_typetable[_T( "�ǂ�" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�ǂ�" )]][m_typetable[_T( "�S�[�X�g" )]] = 0.5;
		m_table[m_typetable[_T( "�ǂ�" )]][m_typetable[_T( "�͂���" )]] = 0;

		// ���߂�i��_�F�ق̂��E�ł񂫁E�ǂ��E����E�͂��ˁA�����F�����E�ނ��A�����F�Ђ����j
		m_table[m_typetable[_T( "���߂�" )]][m_typetable[_T( "�ق̂�" )]]
			= m_table[m_typetable[_T( "���߂�" )]][m_typetable[_T( "�ł�" )]]
			= m_table[m_typetable[_T( "���߂�" )]][m_typetable[_T( "�ǂ�" )]]
			= m_table[m_typetable[_T( "���߂�" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "���߂�" )]][m_typetable[_T( "�͂���" )]] = 2;
		m_table[m_typetable[_T( "���߂�" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "���߂�" )]][m_typetable[_T( "�ނ�" )]] = 0.5;
		m_table[m_typetable[_T( "���߂�" )]][m_typetable[_T( "�Ђ���" )]] = 0;

		// �Ђ����i��_�F�����E�����Ƃ��E�ނ��A�����F����E�͂��ˁA�����F�Ȃ��j
		m_table[m_typetable[_T( "�Ђ���" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�Ђ���" )]][m_typetable[_T( "�����Ƃ�" )]]
			= m_table[m_typetable[_T( "�Ђ���" )]][m_typetable[_T( "�ނ�" )]] = 2;
		m_table[m_typetable[_T( "�Ђ���" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�Ђ���" )]][m_typetable[_T( "�͂���" )]] = 0.5;

		// �G�X�p�[�i��_�F�����Ƃ��E�ǂ��A�����F�G�X�p�[�E�͂��ˁA�����F�����j
		m_table[m_typetable[_T( "�G�X�p�[" )]][m_typetable[_T( "�����Ƃ�" )]]
			= m_table[m_typetable[_T( "�G�X�p�[" )]][m_typetable[_T( "�ǂ�" )]] = 2;
		m_table[m_typetable[_T( "�G�X�p�[" )]][m_typetable[_T( "�G�X�p�[" )]]
			= m_table[m_typetable[_T( "�G�X�p�[" )]][m_typetable[_T( "�͂���" )]] = 0.5;
		m_table[m_typetable[_T( "�G�X�p�[" )]][m_typetable[_T( "����" )]] = 0;

		// �ނ��i��_�F�����E�G�X�p�[�E�����A�����F�ق̂��E�����Ƃ��E�ǂ��E�Ђ����E�S�[�X�g�E�͂��ˁE�t�F�A���[�A�����F�Ȃ��j
		m_table[m_typetable[_T( "�Ђ���" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�Ђ���" )]][m_typetable[_T( "�����Ƃ�" )]]
			= m_table[m_typetable[_T( "�Ђ���" )]][m_typetable[_T( "�ނ�" )]] = 2;
		m_table[m_typetable[_T( "�Ђ���" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�Ђ���" )]][m_typetable[_T( "�͂���" )]] = 0.5;

		// ����i��_�F�ق̂��E������E�Ђ����E�ނ��A�����F�����Ƃ��E���߂�E�͂��ˁA�����F�Ȃ��j
		m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�ق̂�" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "������" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�Ђ���" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�ނ�" )]] = 2;
		m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�����Ƃ�" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "���߂�" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�͂���" )]] = 0.5;

		// �S�[�X�g�i��_�F�G�X�p�[�E�S�[�X�g�A�����F�����A�����F�m�[�}���j
		m_table[m_typetable[_T( "�S�[�X�g" )]][m_typetable[_T( "�S�[�X�g" )]]
			= m_table[m_typetable[_T( "�S�[�X�g" )]][m_typetable[_T( "�G�X�p�[" )]] = 2;
		m_table[m_typetable[_T( "�S�[�X�g" )]][m_typetable[_T( "����" )]] = 0.5;
		m_table[m_typetable[_T( "�S�[�X�g" )]][m_typetable[_T( "�m�[�}��" )]] = 0;

		// �h���S���i��_�F�h���S���A�����F�͂��ˁA�����F�t�F�A���[�j
		m_table[m_typetable[_T( "�h���S��" )]][m_typetable[_T( "�h���S��" )]] = 2;
		m_table[m_typetable[_T( "�h���S��" )]][m_typetable[_T( "�͂���" )]] = 0.5;
		m_table[m_typetable[_T( "�h���S��" )]][m_typetable[_T( "�t�F�A���[" )]] = 0;

		// �����i��_�F�G�X�p�[�E�S�[�X�g�A�����F�����E�t�F�A���[�A�����F�Ȃ��j
		m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�G�X�p�[" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�S�[�X�g" )]] = 2;
		m_table[m_typetable[_T( "����" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "����" )]][m_typetable[_T( "�t�F�A���[" )]] = 0.5;

		// �͂��ˁi��_�F������E����E�t�F�A���[�A�����F�ق̂��E�݂��E�ł񂫁E�͂��ˁA�����F�Ȃ��j
		m_table[m_typetable[_T( "�͂���" )]][m_typetable[_T( "������" )]]
			= m_table[m_typetable[_T( "�͂���" )]][m_typetable[_T( "����" )]]
			= m_table[m_typetable[_T( "�͂���" )]][m_typetable[_T( "�t�F�A���[" )]] = 2;
		m_table[m_typetable[_T( "�͂���" )]][m_typetable[_T( "�ق̂�" )]]
			= m_table[m_typetable[_T( "�͂���" )]][m_typetable[_T( "�݂�" )]]
			= m_table[m_typetable[_T( "�͂���" )]][m_typetable[_T( "�ł�" )]]
			= m_table[m_typetable[_T( "�͂���" )]][m_typetable[_T( "�͂���" )]] = 0.5;

		// �t�F�A���[�i��_�F�����Ƃ��E�h���S���E�����A�����F�ق̂��E�ǂ��E�͂��ˁA�����F�Ȃ��j
		m_table[m_typetable[_T( "�t�F�A���[" )]][m_typetable[_T( "�����Ƃ�" )]]
			= m_table[m_typetable[_T( "�t�F�A���[" )]][m_typetable[_T( "�h���S��" )]]
			= m_table[m_typetable[_T( "�t�F�A���[" )]][m_typetable[_T( "����" )]] = 2;
		m_table[m_typetable[_T( "�t�F�A���[" )]][m_typetable[_T( "�ق̂�" )]]
			= m_table[m_typetable[_T( "�t�F�A���[" )]][m_typetable[_T( "�ǂ�" )]]
			= m_table[m_typetable[_T( "�t�F�A���[" )]][m_typetable[_T( "�͂���" )]] = 0.5;
	}

private:
	std::vector<std::vector<double>> m_table; // �����ϊ��e�[�u��
	std::map<CString, int> m_typetable; // �^�C�v���̕ϊ��e�[�u��
};

// ��������
// �������`����H�߂������ς����c��
