#pragma once

#include <Windows.h>
#include <afxstr.h>
#include <vector>
#include <map>
#include <string>
#include <memory>

#include "poketype.hpp"

/* �|�P�����̃f�[�^��` */

// �����͕ʊǗ����������ǂ�����
class PokemonAbility {
public:
	PokemonAbility() {
		m_ability_map[_T( "�X�i�C�p�[" )] = ABILITY_SNIPER;
		m_ability_map[_T( "����߂���" )] = ABILITY_TINTLENS;
		m_ability_map[_T( "���ӂ���" )] = ABILITY_FLUFFY; // �e�|�P�����ɏ�񎝂�����悤�ɂ�������A�U�����Ɩh�䑤�ł��ꂼ���p�����������Ȃ��Ă��ǂ��Ǝv��
		m_ability_map[_T( "�t�����h�K�[�h" )] = ABILITY_FRIENDGUARD;
		m_ability_map[_T( "������̂��Ղ�" )] = ABILITY_ICE_SCALES;
		m_ability_map[_T( "�p���N���b�N" )] = ABILITY_PUNKROCK;
		m_ability_map[_T( "�t�@���g���K�[�h" )] = ABILITY_SHADOWSHIELD;
		m_ability_map[_T( "�}���`�X�P�C��" )] = ABILITY_MULTISCALE;
		m_ability_map[_T( "�t�B���^�[" )] = ABILITY_FILTER;
		m_ability_map[_T( "�n�[�h���b�N" )] = ABILITY_SOLIDROCK;
		m_ability_map[_T( "�v���Y���A�[�}�[" )] = ABILITY_PRISMARMOR;
		m_ability_map[_T( "���񂩂�" )] = ABILITY_LONGREACH;
		m_ability_map[_T( "�m�[�}���X�L��" )] = ABILITY_NORMALIZE;
		m_ability_map[_T( "�X�J�C�X�L��" )] = ABILITY_AERILATE;
		m_ability_map[_T( "�G���L�X�L��" )] = ABILITY_GALVANIZE;
		m_ability_map[_T( "�t���[�Y�X�L��" )] = ABILITY_REFRIGERATE;
		m_ability_map[_T( "�t�F�A���[�X�L��" )] = ABILITY_PIXILATE;
		m_ability_map[_T( "�A�i���C�Y" )] = ABILITY_ANALYTIC;
		m_ability_map[_T( "���邨���{�C�X" )] = ABILITY_LIQUIDVOICE;
		m_ability_map[_T( "�G�A���b�N" )] = ABILITY_AIRLOCK;
		m_ability_map[_T( "�m�[�Ă�" )] = ABILITY_CLOUDNINE;
		m_ability_map[_T( "�������c��" )] = ABILITY_TOUGHCLAWS;
		m_ability_map[_T( "���񂶂傤����" )] = ABILITY_STRONGJAW;
		m_ability_map[_T( "����������" )] = ABILITY_SCRAPPY;
		m_ability_map[_T( "���傤����" )] = ABILITY_SUPERLUCK;
		m_ability_map[_T( "������イ" )] = ABILITY_TORRENT;
		m_ability_map[_T( "�����傭" )] = ABILITY_OVERGROW;
		m_ability_map[_T( "������" )] = ABILITY_BLAZE;
		m_ability_map[_T( "�ւ񂰂񂶂���" )] = ABILITY_PROTEAN;
		m_ability_map[_T( "���x��" )] = ABILITY_LIBERO;
		m_ability_map[_T( "����ނ��イ" )] = ABILITY_GORILLATACTICS;
		m_ability_map[_T( "���񂶂傤" )] = ABILITY_GUTS;
		m_ability_map[_T( "�T���p���[" )] = ABILITY_SOLARPOWER;
		m_ability_map[_T( "�X�L�������N" )] = ABILITY_SKILLLINK;
		m_ability_map[_T( "�����ق�" )] = ABILITY_WATERBUBBLE;
		m_ability_map[_T( "���Ă�" )] = ABILITY_RECKLESS;
		m_ability_map[_T( "���Ȃ̂�����" )] = ABILITY_SANDFORCE;
		m_ability_map[_T( "����ʂ�" )] = ABILITY_INFILTRATOR;
		m_ability_map[_T( "�X���[�X�^�[�g" )] = ABILITY_SLOWSTART;
		m_ability_map[_T( "������Â�" )] = ABILITY_SHEERFORCE;
		m_ability_map[_T( "���������" )] = ABILITY_HUGEPOWER;
		m_ability_map[_T( "���K�p���[" )] = ABILITY_PUREPOWER;
		m_ability_map[_T( "�e�N�j�V����" )] = ABILITY_TECHNICIAN;
		m_ability_map[_T( "�Ă�������傭" )] = ABILITY_ADAPTABILITY;
		m_ability_map[_T( "�Ă̂��Ԃ�" )] = ABILITY_IRONFIST;
		m_ability_map[_T( "�Ă�˂�" )] = ABILITY_UNAWARE;
		m_ability_map[_T( "�ǂ��ڂ�����" )] = ABILITY_TOXICBOOST;
		m_ability_map[_T( "�g�����W�X�^" )] = ABILITY_TRANSISTOR;
		m_ability_map[_T( "�˂ڂ�����" )] = ABILITY_FLAREBOOST;
		m_ability_map[_T( "�͂��˂���" )] = ABILITY_STEELWORKER;
		m_ability_map[_T( "�͂��˂̂�������" )] = ABILITY_STEELYSPIRIT;
		m_ability_map[_T( "�͂肫��" )] = ABILITY_HUSTLE;
		m_ability_map[_T( "�v���X" )] = ABILITY_PLUSMINUS;
		m_ability_map[_T( "�}�C�i�X" )] = ABILITY_PLUSMINUS;
		m_ability_map[_T( "�ނ��̂��点" )] = ABILITY_SWARM;
		m_ability_map[_T( "���K�����`���[" )] = ABILITY_MEGALAUNCHER;
		m_ability_map[_T( "���炢��" )] = ABILITY_FLASHFIRE;
		m_ability_map[_T( "��킫" )] = ABILITY_DEFEATIST;
		m_ability_map[_T( "��イ�̂�����" )] = ABILITY_DRAGONSMAW;
		m_ability_map[_T( "����͂���" )] = ABILITY_ROCKYPAYLOAD;
		m_ability_map[_T( "�ЂƂłȂ�" )] = ABILITY_MERCILESS;
		m_ability_map[_T( "��������������" )] = ABILITY_PROTOSYNTHESIS;
		m_ability_map[_T( "�N�H�[�N�`���[�W" )] = ABILITY_QUARKDRIVE;
		m_ability_map[_T( "�ЂЂ���̂��ǂ�" )] = ABILITY_ORICHALCUMPULSE;
		m_ability_map[_T( "�n�h�����G���W��" )] = ABILITY_HADRONENGINE;
	}

	std::map<CString, uint64_t> m_ability_map;

	// �����r�b�g��`�iPokemonDataSub����ڐA����j
	static constexpr uint64_t ABILITY_SNIPER          = 0x0000000000000001; // �X�i�C�p�[
	static constexpr uint64_t ABILITY_TINTLENS        = 0x0000000000000002; // �F�ዾ
	static constexpr uint64_t ABILITY_FLUFFY          = 0x0000000000000004; // ���ӂ���
	static constexpr uint64_t ABILITY_FRIENDGUARD     = 0x0000000000000008; // �t�����h�K�[�h
	static constexpr uint64_t ABILITY_ICE_SCALES      = 0x0000000000000010; // �X�̗ؕ�
	static constexpr uint64_t ABILITY_PUNKROCK        = 0x0000000000000020; // �p���N���b�N
	static constexpr uint64_t ABILITY_XXXXXXXXXXXXXX1 = 0x0000000000000040; // �󂫃r�b�g
	static constexpr uint64_t ABILITY_SHADOWSHIELD    = 0x0000000000000080; // �t�@���g���K�[�h
	static constexpr uint64_t ABILITY_MULTISCALE      = 0x0000000000000100; // �}���`�X�P�C��
	static constexpr uint64_t ABILITY_XXXXXXXXXXXXXX2 = 0x0000000000000200; // �󂫃r�b�g
	static constexpr uint64_t ABILITY_FILTER          = 0x0000000000000400; // �t�B���^�[
	static constexpr uint64_t ABILITY_SOLIDROCK       = 0x0000000000000400; // �n�[�h���b�N
	static constexpr uint64_t ABILITY_PRISMARMOR      = 0x0000000000000800; // �v���Y���A�[�}�[
	static constexpr uint64_t ABILITY_LONGREACH       = 0x0000000000001000; // ���u
	static constexpr uint64_t ABILITY_NORMALIZE       = 0x0000000000002000; // �m�[�}���X�L��
	static constexpr uint64_t ABILITY_AERILATE        = 0x0000000000004000; // �X�J�C�X�L��
	static constexpr uint64_t ABILITY_GALVANIZE       = 0x0000000000008000; // �G���L�X�L��
	static constexpr uint64_t ABILITY_REFRIGERATE     = 0x0000000000010000; // �t���[�Y�X�L��
	static constexpr uint64_t ABILITY_PIXILATE        = 0x0000000000020000; // �t�F�A���[�X�L��
	static constexpr uint64_t ABILITY_ANALYTIC        = 0x0000000000040000; // �A�i���C�Y
	static constexpr uint64_t ABILITY_LIQUIDVOICE     = 0x0000000000080000; // ���邨���{�C�X
	static constexpr uint64_t ABILITY_AIRLOCK         = 0x0000000000100000; // �G�A���b�N
	static constexpr uint64_t ABILITY_CLOUDNINE       = 0x0000000000100000; // �m�[�V�C
	static constexpr uint64_t ABILITY_TOUGHCLAWS      = 0x0000000000200000; // �d���� // memo: 5325/4096
	static constexpr uint64_t ABILITY_STRONGJAW       = 0x0000000000400000; // ���{
	static constexpr uint64_t ABILITY_SCRAPPY         = 0x0000000000800000; // �̂���
	static constexpr uint64_t ABILITY_SUPERLUCK       = 0x0000000000100000; // ���^
	static constexpr uint64_t ABILITY_TORRENT         = 0x0000000000200000; // ����
	static constexpr uint64_t ABILITY_OVERGROW        = 0x0000000000400000; // �V��
	static constexpr uint64_t ABILITY_BLAZE           = 0x0000000000800000; // �҉�
	static constexpr uint64_t ABILITY_PROTEAN         = 0x0000000001000000; // �ό�����
	static constexpr uint64_t ABILITY_LIBERO          = 0x0000000001000000; // ���x��
	static constexpr uint64_t ABILITY_GORILLATACTICS  = 0x0000000002000000; // �ܗ�����
	static constexpr uint64_t ABILITY_GUTS            = 0x0000000004000000; // ����
	static constexpr uint64_t ABILITY_SOLARPOWER      = 0x0000000008000000; // �T���p���[
	static constexpr uint64_t ABILITY_SKILLLINK       = 0x0000000001000000; // �X�L�������N
	static constexpr uint64_t ABILITY_WATERBUBBLE     = 0x0000000002000000; // ���A
	static constexpr uint64_t ABILITY_RECKLESS        = 0x0000000004000000; // �̂Đg
	static constexpr uint64_t ABILITY_SANDFORCE       = 0x0000000008000000; // ���̗�
	static constexpr uint64_t ABILITY_INFILTRATOR     = 0x0000000010000000; // ���蔲��
	static constexpr uint64_t ABILITY_SLOWSTART       = 0x0000000020000000; // �X���[�X�^�[�g
	static constexpr uint64_t ABILITY_SHEERFORCE      = 0x0000000040000000; // �͂Â�
	static constexpr uint64_t ABILITY_HUGEPOWER       = 0x0000000080000000; // �͎���
	static constexpr uint64_t ABILITY_PUREPOWER       = 0x0000000080000000; // ���K�p���[
	static constexpr uint64_t ABILITY_TECHNICIAN      = 0x0000000100000000; // �e�N�j�V����
	static constexpr uint64_t ABILITY_ADAPTABILITY    = 0x0000000200000000; // �K���� 
	static constexpr uint64_t ABILITY_IRONFIST        = 0x0000000400000000; // �Ă̂��Ԃ�
	static constexpr uint64_t ABILITY_UNAWARE         = 0x0000000800000000; // �V�R
	static constexpr uint64_t ABILITY_TOXICBOOST      = 0x0000001000000000; // �Ŗ\��
	static constexpr uint64_t ABILITY_TRANSISTOR      = 0x0000002000000000; // �g�����W�X�^
	static constexpr uint64_t ABILITY_FLAREBOOST      = 0x0000004000000000; // �M�\��
	static constexpr uint64_t ABILITY_STEELWORKER     = 0x0000008000000000; // �|�g��
	static constexpr uint64_t ABILITY_STEELYSPIRIT    = 0x0000010000000000; // �|�̐��_
	static constexpr uint64_t ABILITY_HUSTLE          = 0x0000020000000000; // ����؂�
	static constexpr uint64_t ABILITY_PLUSMINUS       = 0x0000040000000000; // �v���X/�}�C�i�X
	static constexpr uint64_t ABILITY_SWARM           = 0x0000080000000000; // �ނ��̂��点
	static constexpr uint64_t ABILITY_MEGALAUNCHER    = 0x0000100000000000; // ���K�����`���[
	static constexpr uint64_t ABILITY_FLASHFIRE       = 0x0000200000000000; // �Ⴂ��
	static constexpr uint64_t ABILITY_DEFEATIST       = 0x0000400000000000; // ��C
	static constexpr uint64_t ABILITY_DRAGONSMAW      = 0x0000800000000000; // ���̂�����
	static constexpr uint64_t ABILITY_ROCKYPAYLOAD    = 0x0001000000000000; // ��^��
	static constexpr uint64_t ABILITY_MERCILESS       = 0x0002000000000000; // �l�łȂ�
	static constexpr uint64_t ABILITY_PROTOSYNTHESIS  = 0x0004000000000000; // �Ñ㊈�� // -> �ȉ�4�A�V�C�Ƃ��t�B�[���h�����Ď����I�ɕ␳����Ȃ�A�r�b�g�����Ȃ��ƃ_��
	static constexpr uint64_t ABILITY_QUARKDRIVE      = 0x0004000000000000; // �N�H�[�N�`���[�W
	static constexpr uint64_t ABILITY_ORICHALCUMPULSE = 0x0004000000000000; // �q�q�C���̌ۓ�
	static constexpr uint64_t ABILITY_HADRONENGINE    = 0x0004000000000000; // �n�h�����G���W��
};

// ������������Ɋւ���f�[�^
class PokemonDataSub {
public:
	int m_barrier; // bit0: ���t���N�^�[�A bit1: ���̕�
	uint64_t m_ability; // �����r�b�g���Z�b�g
	uint64_t m_item; // ������
	uint64_t m_rank; // �����N�␳ -> ���ꏭ�Ȃ��Ƃ�����/�����2�͕K�v�Ȃ͂�(�U�����ւ������邩��A5�����Ă������ǂ��Ǝv���j
	CString m_teraType; // �e���X�^�C�v
	uint64_t m_conditionAbnormaly; // ��Ԉُ�

	void clear() {
		m_barrier = 0;
		m_ability = 0;
		m_item = 0;
		m_rank = 0; // �����킹�Ē���
	}

	// �����̕ӂ��A�r�b�g��`����̎��̂͗ǂ����ǁAstd::map�Ƃ��ɓ���Ă����������ǂ��Ǝv���c
	// �@�f�[�^�x�[�X����ǂݏo���ă|�P�����ɃZ�b�g������������r�b�g�����E���̖����ł���c
	// ���X�����ǁA�ʂɃr�b�g�ɂ��Ȃ��ėǂ������̂ł́Hstd::map�Ƃ�����E���āA��ӂɌ��߂�Ηǂ��񂾂�
	// �����r�b�g��`
	static constexpr uint64_t ABILITY_SNIPER          = 0x0000000000000001; // �X�i�C�p�[
	static constexpr uint64_t ABILITY_TINTLENS        = 0x0000000000000002; // �F�ዾ
	static constexpr uint64_t ABILITY_FLUFFY_FLARE    = 0x0000000000000004; // ���ӂ���(����e)
	static constexpr uint64_t ABILITY_FRIENDGUARD     = 0x0000000000000008; // �t�����h�K�[�h
	static constexpr uint64_t ABILITY_ICE_SCALES      = 0x0000000000000010; // �X�̗ؕ�
	static constexpr uint64_t ABILITY_PUNKROCK_ATK    = 0x0000000000000020; // �p���N���b�N(�U����)
	static constexpr uint64_t ABILITY_PUNKROCK_DEF    = 0x0000000000000040; // �p���N���b�N(�h�䑤)
	static constexpr uint64_t ABILITY_SHADOWSHIELD    = 0x0000000000000080; // �t�@���g���K�[�h
	static constexpr uint64_t ABILITY_MULTISCALE      = 0x0000000000000100; // �}���`�X�P�C��
	static constexpr uint64_t ABILITY_FLUFFY_DIRECT   = 0x0000000000000200; // ���ӂ���(�ڐG�Z)
	static constexpr uint64_t ABILITY_FILTER          = 0x0000000000000400; // �t�B���^�[
	static constexpr uint64_t ABILITY_SOLIDROCK       = 0x0000000000000400; // �n�[�h���b�N
	static constexpr uint64_t ABILITY_PRISMARMOR      = 0x0000000000000800; // �v���Y���A�[�}�[
	static constexpr uint64_t ABILITY_LONGREACH       = 0x0000000000001000; // ���u
	static constexpr uint64_t ABILITY_NORMALIZE       = 0x0000000000002000; // �m�[�}���X�L��
	static constexpr uint64_t ABILITY_AERILATE        = 0x0000000000004000; // �X�J�C�X�L��
	static constexpr uint64_t ABILITY_GALVANIZE       = 0x0000000000008000; // �G���L�X�L��
	static constexpr uint64_t ABILITY_REFRIGERATE     = 0x0000000000010000; // �t���[�Y�X�L��
	static constexpr uint64_t ABILITY_PIXILATE        = 0x0000000000020000; // �t�F�A���[�X�L��
	static constexpr uint64_t ABILITY_ANALYTIC        = 0x0000000000040000; // �A�i���C�Y
	static constexpr uint64_t ABILITY_LIQUIDVOICE     = 0x0000000000080000; // ���邨���{�C�X
	static constexpr uint64_t ABILITY_AIRLOCK         = 0x0000000000100000; // �G�A���b�N
	static constexpr uint64_t ABILITY_CLOUDNINE       = 0x0000000000100000; // �m�[�V�C
	static constexpr uint64_t ABILITY_TOUGHCLAWS      = 0x0000000000200000; // �d���� // memo: 5325/4096
	static constexpr uint64_t ABILITY_STRONGJAW       = 0x0000000000400000; // ���{
	static constexpr uint64_t ABILITY_SCRAPPY         = 0x0000000000800000; // �̂���
	static constexpr uint64_t ABILITY_SUPERLUCK       = 0x0000000000100000; // ���^
	static constexpr uint64_t ABILITY_TORRENT         = 0x0000000000200000; // ����
	static constexpr uint64_t ABILITY_OVERGROW        = 0x0000000000400000; // �V��
	static constexpr uint64_t ABILITY_BLAZE           = 0x0000000000800000; // �҉�
	static constexpr uint64_t ABILITY_PROTEAN         = 0x0000000001000000; // �ό�����
	static constexpr uint64_t ABILITY_LIBERO          = 0x0000000001000000; // ���x��
	static constexpr uint64_t ABILITY_GORILLATACTICS  = 0x0000000002000000; // �ܗ�����
	static constexpr uint64_t ABILITY_GUTS            = 0x0000000004000000; // ����
	static constexpr uint64_t ABILITY_SOLARPOWER      = 0x0000000008000000; // �T���p���[
	static constexpr uint64_t ABILITY_SKILLLINK       = 0x0000000001000000; // �X�L�������N
	static constexpr uint64_t ABILITY_WATERBUBBLE     = 0x0000000002000000; // ���A
	static constexpr uint64_t ABILITY_RECKLESS        = 0x0000000004000000; // �̂Đg
	static constexpr uint64_t ABILITY_SANDFORCE       = 0x0000000008000000; // ���̗�
	static constexpr uint64_t ABILITY_INFILTRATOR     = 0x0000000010000000; // ���蔲��
	static constexpr uint64_t ABILITY_SLOWSTART       = 0x0000000020000000; // �X���[�X�^�[�g
	static constexpr uint64_t ABILITY_SHEERFORCE      = 0x0000000040000000; // �͂Â�
	static constexpr uint64_t ABILITY_HUGEPOWER       = 0x0000000080000000; // �͎���
	static constexpr uint64_t ABILITY_PUREPOWER       = 0x0000000080000000; // ���K�p���[
	static constexpr uint64_t ABILITY_TECHNICIAN      = 0x0000000100000000; // �e�N�j�V����
	static constexpr uint64_t ABILITY_ADAPTABILITY    = 0x0000000200000000; // �K���� 
	static constexpr uint64_t ABILITY_IRONFIST        = 0x0000000400000000; // �Ă̂��Ԃ�
	static constexpr uint64_t ABILITY_UNAWARE         = 0x0000000800000000; // �V�R
	static constexpr uint64_t ABILITY_TOXICBOOST      = 0x0000001000000000; // �Ŗ\��
	static constexpr uint64_t ABILITY_TRANSISTOR      = 0x0000002000000000; // �g�����W�X�^
	static constexpr uint64_t ABILITY_FLAREBOOST      = 0x0000004000000000; // �M�\��
	static constexpr uint64_t ABILITY_STEELWORKER     = 0x0000008000000000; // �|�g��
	static constexpr uint64_t ABILITY_STEELYSPIRIT    = 0x0000010000000000; // �|�̐��_
	static constexpr uint64_t ABILITY_HUSTLE          = 0x0000020000000000; // ����؂�
	static constexpr uint64_t ABILITY_PLUSMINUS       = 0x0000040000000000; // �v���X/�}�C�i�X
	static constexpr uint64_t ABILITY_SWARM           = 0x0000080000000000; // �ނ��̂��点
	static constexpr uint64_t ABILITY_MEGALAUNCHER    = 0x0000100000000000; // ���K�����`���[
	static constexpr uint64_t ABILITY_FLASHFIRE       = 0x0000200000000000; // �Ⴂ��
	static constexpr uint64_t ABILITY_DEFEATIST       = 0x0000400000000000; // ��C
	static constexpr uint64_t ABILITY_DRAGONSMAW      = 0x0000800000000000; // ���̂�����
	static constexpr uint64_t ABILITY_ROCKYPAYLOAD    = 0x0001000000000000; // ��^��
	static constexpr uint64_t ABILITY_MERCILESS       = 0x0002000000000000; // �l�łȂ�
	static constexpr uint64_t ABILITY_PROTOSYNTHESIS  = 0x0004000000000000; // �Ñ㊈�� // -> �ȉ�4�A�V�C�Ƃ��t�B�[���h�����Ď����I�ɕ␳����Ȃ�A�r�b�g�����Ȃ��ƃ_��
	static constexpr uint64_t ABILITY_QUARKDRIVE      = 0x0004000000000000; // �N�H�[�N�`���[�W
	static constexpr uint64_t ABILITY_ORICHALCUMPULSE = 0x0004000000000000; // �q�q�C���̌ۓ�
	static constexpr uint64_t ABILITY_HADRONENGINE    = 0x0004000000000000; // �n�h�����G���W��
	// �܂�����c�c�c�H

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
	static constexpr uint64_t ITEM_LIGHTBALL       = 0x0000000000010000; // �d�C��
	static constexpr uint64_t ITEM_LEEK            = 0x0000000000020000; // ���l�M
	static constexpr uint64_t ITEM_GRISEOUSORB     = 0x0000000000040000; // ������
	static constexpr uint64_t ITEM_THICKCLUB       = 0x0000000000080000; // �ӂƂ��z�l
	static constexpr uint64_t ITEM_LUCKYPUNCH      = 0x0000000000100000; // ���b�L�[�p���`
	static constexpr uint64_t ITEM_SITRUSBERRY     = 0x0000000000200000; // �I�{���̂�
	static constexpr uint64_t ITEM_FOCUSSASH       = 0x0000000000400000; // �������̃^�X�L
	static constexpr uint64_t ITEM_IRONBALL        = 0x0000000000800000; // ���낢�Ă����イ
	static constexpr uint64_t ITEM_DEEPSEASCALE    = 0x0000000001000000; // ���񂩂��̗�
	static constexpr uint64_t ITEM_EVIOLITE        = 0x0000000002000000; // ���񂩂̂�����
	static constexpr uint64_t ITEM_LEFTOVERS       = 0x0000000004000000; // �H�׎c��
	static constexpr uint64_t ITEM_ASSAULTVEST     = 0x0000000008000000; // �Ƃ����`���b�L
	static constexpr uint64_t ITEM_METALPOWDER     = 0x0000000010000000; // ���^���p�E�_�[
	static constexpr uint64_t ITEM_SCOPELENS       = 0x0000000020000000; // �s���g�����Y
	static constexpr uint64_t ITEM_RAZORCLAW       = 0x0000000020000000; // ����ǂ��c��

	// ��Ԉُ�r�b�g��`
	static constexpr uint64_t CONDITION_POISON    = 0x01; // �ŁE�ғ�
	static constexpr uint64_t CONDITION_BURN      = 0x02; // �Ώ�
	static constexpr uint64_t CONDITION_PARALYSIS = 0x04; // ���
	static constexpr uint64_t CONDITION_SLEEP     = 0x08; // ����

};

// �|�P�����̃f�[�^
class PokemonData {
public:
	CString m_name; // ���O
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

