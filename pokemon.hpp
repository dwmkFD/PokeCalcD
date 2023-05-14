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
	uint64_t m_ability; // �����r�b�g���Z�b�g
	uint64_t m_item; // ������
	uint64_t m_rank; // �����N�␳

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
	static constexpr uint64_t ABILITY_A = 0x0000000000002000; // �m�[�}���X�L��
	static constexpr uint64_t ABILITY_B = 0x0000000000004000; // �X�J�C�X�L��
	static constexpr uint64_t ABILITY_C = 0x0000000000008000; // �G���L�X�L��
	static constexpr uint64_t ABILITY_D = 0x0000000000010000; // �t���[�Y�X�L��
	static constexpr uint64_t ABILITY_E = 0x0000000000020000; // �t�F�A���[�X�L��
	static constexpr uint64_t ABILITY_F = 0x0000000000040000; // �A�i���C�Y
	static constexpr uint64_t ABILITY_G = 0x0000000000080000; // ���邨���{�C�X
	static constexpr uint64_t ABILITY_H = 0x0000000000100000; // �G�A���b�N/�m�[�V�C
	static constexpr uint64_t ABILITY_I = 0x0000000000200000; // �d����
	static constexpr uint64_t ABILITY_J = 0x0000000000400000; // ���{
	static constexpr uint64_t ABILITY_K = 0x0000000000800000; // �̂���
	static constexpr uint64_t ABILITY_L = 0x0000000000100000; // ���^
	static constexpr uint64_t ABILITY_M = 0x0000000000200000; // ����
	static constexpr uint64_t ABILITY_N = 0x0000000000400000; // �V��
	static constexpr uint64_t ABILITY_O = 0x0000000000800000; // �҉�
	static constexpr uint64_t ABILITY_P = 0x0000000001000000; // �ό�����/���x��
	static constexpr uint64_t ABILITY_Q = 0x0000000002000000; // �ܗ�����
	static constexpr uint64_t ABILITY_R = 0x0000000004000000; // ����
	static constexpr uint64_t ABILITY_S = 0x0000000008000000; // �T���p���[
	static constexpr uint64_t ABILITY_T = 0x0000000001000000; // �X�L�������N
	static constexpr uint64_t ABILITY_U = 0x0000000002000000; // ���A
	static constexpr uint64_t ABILITY_V = 0x0000000004000000; // �̂Đg
	static constexpr uint64_t ABILITY_W = 0x0000000008000000; // ���̗�

	// �A�C�e���r�b�g��`
	static constexpr uint64_t ITEM_METRONOME       = 0x000000000000003F; // ���g���m�[��N���
	static constexpr uint64_t ITEM_LIFEORB         = 0x0000000000000040; // ���̎�
	static constexpr uint64_t ITEM_TYPE_ENHANCE    = 0x0000000000000080; // �^�C�v�����A�C�e��
	static constexpr uint64_t ITEM_SOULDEW         = 0x0000000000000100; // ������̂�����
	static constexpr uint64_t ITEM_CHOICEBAND      = 0x0000000000000200; // �������n�`�}�L
	static constexpr uint64_t ITEM_CHOICESPECS     = 0x0000000000000400; // ������胁�K�l
	static constexpr uint64_t ITEM_EXPERTBELT      = 0x0000000000000800; // ������̂���
	static constexpr uint64_t ITEM_MUSCLEBAND      = 0x0000000000001000; // ������̃n�`�}�L
	static constexpr uint64_t ITEM_WISEGLASSES     = 0x0000000000002000; // ���̂��胁�K�l
	static constexpr uint64_t ITEM_HALFDAMAGEBERRY = 0x0000000000004000; // ������
	static constexpr uint64_t ITEM_NORMALGEM       = 0x0000000000008000; // �m�[�}���W���G��
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

