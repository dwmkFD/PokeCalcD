#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <string>
#include <memory>

/* �|�P�����̃f�[�^��` */

// ������������Ɋւ���f�[�^
class PokemonDataSub {
public:
	int m_barrier; // bit0: ���t���N�^�[�A bit1: ���̕�
	uint64_t m_Ability; // �����r�b�g���Z�b�g
	uint64_t m_item; // ������
				// bit0-5: ���g���m�[��1-6��ځAbit6: ���̎�Abit7: �������Abit8: �^�C�v�����A�C�e���Abit9: �m�[�}���W���G��
				// bit10: �B�l�̑сA

	// �����r�b�g��`
	static constexpr uint64_t ABILITY_SNIPER        = 0x0000000000000001; // �X�i�C�p�[
	static constexpr uint64_t ABILITY_TINTLENS      = 0x0000000000000002; // �F�ዾ
	static constexpr uint64_t ABILITY_FLUFFY_FLARE  = 0x0000000000000004; // ���ӂ���(����e)
	static constexpr uint64_t ABILITY_FRIENDGUARD   = 0x0000000000000008; // �t�����h�K�[�h
	static constexpr uint64_t ABILITY_ICE_SCALES    = 0x0000000000000010; // �X�̗ؕ�
	static constexpr uint64_t ABILITY_PUNKROCK_ATK  = 0x0000000000000020; // �p���N���b�N(�U����)
	static constexpr uint64_t ABILITY_PUNKROCK_DEF  = 0x0000000000000040; // �p���N���b�N(�h�䑤)
	static constexpr uint64_t ABILITY_SHADOWSHIELD  = 0x0000000000000080; // �t�@���g���K�[�h
	static constexpr uint64_t ABILITY_MULTISCALE    = 0x0000000000000100; // �}���`�X�P�C��
	static constexpr uint64_t ABILITY_FLUFFY_DIRECT = 0x0000000000000200; // ���ӂ���(�ڐG�Z)
	static constexpr uint64_t ABILITY_FILTER        = 0x0000000000000400; // �n�[�h���b�N/�t�B���^�[
	static constexpr uint64_t ABILITY_PRISMARMOR    = 0x0000000000000800; // �v���Y���A�[�}�[
	static constexpr uint64_t ABILITY_LONGREACH     = 0x0000000000001000; // ���u
	static constexpr uint64_t ABILITY_X = 0x0000000000002000; // 
	static constexpr uint64_t ABILITY_Y = 0x0000000000004000; // 
	static constexpr uint64_t ABILITY_Z = 0x0000000000008000; // 

	// �A�C�e���r�b�g��`
	static constexpr uint64_t ITEM_METRONOME    = 0x000000000000003F; // ���g���m�[��N���
	static constexpr uint64_t ITEM_LIFEORB      = 0x0000000000000040; // ���̎�
	static constexpr uint64_t ITEM_TYPE_ENHANCE = 0x0000000000000080; // �^�C�v�����A�C�e��
	static constexpr uint64_t ITEM_SOULDEW      = 0x0000000000000100; // ������̂�����
	static constexpr uint64_t ITEM_CHOICEBAND   = 0x0000000000000200; // �������n�`�}�L
	static constexpr uint64_t ITEM_CHOICESPECS  = 0x0000000000000400; // ������胁�K�l
	static constexpr uint64_t ITEM_EXPERTBELT   = 0x0000000000000800; // ������̂���
	static constexpr uint64_t ITEM_MUSCLEBAND   = 0x0000000000001000; // ������̃n�`�}�L
	static constexpr uint64_t ITEM_WISEGLASSES  = 0x0000000000002000; // ���̂��胁�K�l
};

// �|�P�����̃f�[�^
class PokemonData {
public:
	int m_Level; // ���x��

	// HABCDS
	int m_status[6];

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

	PokemonDataSub m_option; // �o�g���S�̂ł͂Ȃ��|�P�������̐ݒ�

	void clear() {
		// �㏑������Ȃ������N���A���� -> �łȂ��ƁA�|�P������ς��Ă��O�Ɏ����Ă��^�C�v���̏��������p���ł��܂��c
		m_zukkanNumLocal.clear();
		m_type.clear();
		m_ability.clear();
		m_move.clear();
	}

	static constexpr unsigned int HP_Index = 0;
	static constexpr unsigned int Attack_Index = 1;
	static constexpr unsigned int Block_Index = 2;
	static constexpr unsigned int Contact_Index = 3;
	static constexpr unsigned int Diffence_Index = 4;
	static constexpr unsigned int Speed_Index = 5;
	static constexpr unsigned int StatusKind = 6;
};

