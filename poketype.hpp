#pragma once

#include <Windows.h>
#include <afxstr.h>

#include <vector>
#include <map>
#include <memory>

// �^�C�v�Ɋւ����`

class PokeType {
public:
	PokeType() {
		// �^�C�v���𐔒l�ɕϊ����邽�߂̃e�[�u��
		m_typetable[_T( "�m�[�}��" )] = 0; m_typetable[_T( "�ق̂�" )] = 1;
		m_typetable[_T( "�݂�" )] = 2; m_typetable[_T( "�ł�" )] = 3;
		m_typetable[_T( "����" )] = 4; m_typetable[_T( "������" )] = 5;
		m_typetable[_T( "�����Ƃ�" )] = 6; m_typetable[_T( "�ǂ�" )] = 7;
		m_typetable[_T( "���߂�" )] = 8; m_typetable[_T( "�Ђ���" )] = 9;
		m_typetable[_T( "�G�X�p�[" )] = 10; m_typetable[_T( "�ނ�" )] = 11;
		m_typetable[_T( "����" )] = 12; m_typetable[_T( "�S�[�X�g" )] = 13;
		m_typetable[_T( "�h���S��" )] = 14; m_typetable[_T( "����" )] = 15;
		m_typetable[_T( "�͂���" )] = 16; m_typetable[_T( "�t�F�A���[" )] = 17;
		m_typetable[_T( "�e���X�^�C�v" )] = 18; // �e���X�^�C�v���I���̏ꍇ�A�m�[�}���Ƌ�ʂ��t���Ȃ��Ȃ�̂œ���Ă���(�g�����Ƃ͖����Ǝv��)
	}

	std::map<CString, int> &getTypeTable() { return ( m_typetable ); }

protected:
	std::map<CString, int> m_typetable; // �^�C�v���̕ϊ��e�[�u��
};
