#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <string>
#include <memory>

/* �|�P�����̃f�[�^��` */


// �|�P�����̃f�[�^
class PokemonData {
public:
	int m_Level; // ���x��

	// HABCDS
	int m_HitPoint;
	int m_Attack;
	int m_Block;
	int m_Contact;
	int m_Diffence;
	int m_Speed;

	// ����
	int m_gender; // ���X�A�s���A�I�X �� -1, 0, 1�Ƃ��B�����S�Ƃ��̑Ή�

	// �g���Ƒ̏d
	int m_Height; // �g�������A���̂Ƃ���ˑ��Z�͂Ȃ��H
	int m_Weight; // �̏d�́A�w�r�[�{���o�[�Ƃ������тƂ��ɕK�v

	// �}�Ӕԍ��i�S���A��N����j
	// �����o�[�W�������̃��[�W�����t�H�[���A���K�V���J���́A�Ƃ肠���������ԍ��ɂ��Ă���
	int m_zukkanNum;
	std::vector<int> m_zukkanNumLocal; // �o�����Ȃ�����A�}�ӂɍڂ�Ȃ������-1������H

	// �^�C�v
	// �n���E�B���Ƃ��X�̎􂢂Ƃ��ɂ��Ή�����(2�ȏ�ɑ�����\��������)�ւ̑Ή��̂��߁Avector�ɂ��Ă���
	std::vector<CString> m_type;

	std::vector<CString> m_ability;	// ����

	std::vector<CString> m_move; // �o����Z

	static constexpr unsigned int HP_Index = 0;
	static constexpr unsigned int Attack_Index = 1;
	static constexpr unsigned int Block_Index = 2;
	static constexpr unsigned int Contact_Index = 3;
	static constexpr unsigned int Diffence_Index = 4;
	static constexpr unsigned int Speed_Index = 5;
	static constexpr unsigned int StatusKind = 6;
};

