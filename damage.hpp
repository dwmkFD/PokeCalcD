#pragma once

/* �_���[�W�v�Z���C���w�b�_ */
#include <Windows.h>
#include <afxdb.h>

#include <vector>
#include <map>
#include <memory>

#include "pokemove.hpp"
#include "pokemon.hpp"

class CBattleSettings { // -> �N���X���͂��������ɕς�������
public:
	// �V�C�A�t�B�[���h�A�ǁA�菕���c�Ȃǂ̏�Ԃ��Ǘ�������
	// -> ���C���_�C�A���O�̃����o�ϐ����A����ɂ�������
	int m_weather; // �V�C�i0: �Ȃ��A1: ����A2: �J�A3: ���A4: ��j
	bool m_isBurned; // �Ώ�
	int m_barrier; // bit0: ���t���N�^�[�A bit1: ���̕�
	bool m_range; // �_�u���␳�i0: �Ȃ��A1: ����j
	int m_ability; // �����ɂ��␳
					// bit0: �X�i�C�p�[�Abit1: �F�ዾ�Abit2: ���ӂ���(����e)�Abit3: �t�����h�K�[�h�Abit4: �X�̗ؕ��Abit5: �p���N���b�N(�U��)
					// bit6: �p���N���b�N(�h��)�Abit7: �t�@���g���K�[�h�Abit8: �}���`�X�P�C���Abit9: ���ӂ���(�ڐG�Z)�Abit10: �n�[�h���b�N/�t�B���^�[
					// bit11: �v���Y���A�[�}�[
	bool m_twice; // ����������ňЗ�2�{����
	int m_item; // �A�C�e���␳
				// bit0-5: ���g���m�[��1-6��ځAbit6: ���̎�Abit7: �������Abit8: �^�C�v�����A�C�e���Abit9: �m�[�}���W���G��
				// bit10: �B�l�̑сA

	// �����r�b�g��`
	static constexpr int ABILITY_SNIPER = 1; // �X�i�C�p�[

	// �A�C�e���r�b�g��`
	static constexpr int ITEM_METRONOME = 0x3F; // ����6bit���g���i6�ō����Ă������H�j
	static constexpr int ITEM_LIFEORB = 0x40; // ���̎�
};

class CCalcDamage {
public:
	CCalcDamage( CDatabase *db )
	{
		m_pDatabase = db;
		CRecordset rs( db );

		try {
			CString strSQL;
			strSQL.Format( _T( "SELECT * FROM move" ) );
			auto res = rs.Open( CRecordset::forwardOnly, strSQL );
			CODBCFieldInfo fi;
			int nFields = rs.GetODBCFieldCount();
			std::vector<CDBVariant> var( nFields );
			while ( rs.IsEOF() == FALSE )
			{
				for ( int i = 0; i < nFields; ++i )
				{
					rs.GetFieldValue( i, var[i] );
				}

				// var[0] : ID		var[1] : �Z��
				// var[2] : �^�C�v	var[3] : ����
				// var[4] : �З�	var[5] : ����
				// var[6] : PP		var[7] : �ڐG����
				// var[8] : ����
				m_moveDB[*var[1].m_pstring] = PokeMove( *var[1].m_pstring, *var[2].m_pstring, PokeMove::getCategory( *var[3].m_pstring ),
											   var[4].m_lVal, var[5].m_lVal, var[7].m_boolVal );

				rs.MoveNext();
			}

			rs.Close();
		}
		catch ( CDBException &e ) {
			TCHAR msg[1024];
			e.GetErrorMessage( msg, sizeof( msg ) );
			MessageBox( nullptr, msg, _T( "error" ), MB_ICONERROR );
		}
	}

	int correctPower( CString name, CBattleSettings option ) {
		// �Z�̈З͂��ς��ꍇ�ɕ␳���鏈��
		int power = m_moveDB[name].m_power;
	}

	std::vector<std::pair<CString, std::vector<int>>> calc( PokemonData atk, PokemonData def, CBattleSettings option ) {
		// �U�������o����S�Ă̍U���Z�Ń_���[�W�v�Z����
		// �߂�l�́A�u�Z���F�_���[�W�p�^�[��(�����Ƌ}���ɂ��S32�p�^�[��)�v���o����Z�S�ĂŌv�Z��������
		// �������A�ω��Z�͖�������
		std::vector<std::pair<CString, std::vector<int>>> result;
		for ( auto &&atkmove : atk.m_move )
		{
			// �_���[�W�v�Z����
			//  (((���x���~2/5+2)�~�З́~A/D)/50+2)�~�͈͕␳�~���₱�����␳�~�V�C�␳�~�}���␳�~�����␳�~�^�C�v��v�␳�~�����␳�~�₯�Ǖ␳�~M�~Mprotect
			// A = �U�����̍U��(����) or ���U(����)
			// D = �h�䑤�̖h��(����) or ���h(����)
			// ���������͌v�Z���邽�тɏ����_�ȉ���؂�̂āB�͈͕␳����}���␳�܂ł͊e�v�Z�̌�A�����_�ȉ��𒀈�܎̌ܒ�������B�����␳�v�Z��͐؂�̂Ă�B�^�C�v��v�␳�v�Z��͌܎̌ܒ�������B�����␳�v�Z��͐؂�̂Ă�B�₯�Ǖ␳�v�Z��͌܎̌ܒ�������BM�v�Z��͌܎̌ܒ�������BMprotect�v�Z��͌܎̌ܒ�������B

			// M = �Ǖ␳�~�u���C���t�H�[�X�␳�~�X�i�C�p�[�␳�~����߂��˕␳�~���ӂ��ӂق̂��␳�~Mhalf�~Mfilter�~�t�����h�K�[�h�␳�~������̂��ѕ␳�~���g���m�[���␳�~���̂��̂��ܕ␳�~�����̎��␳�~Mtwice
			// M�̊e�␳�l�̌v�Z�ł́A�����_�ȉ��𒀈�l�̌ܓ�����B
			// Mhalf = �_���[�W���������ɂ��␳(0.5�{): ������̂��Ղ�A�p���N���b�N�A�t�@���g���K�[�h�A�}���`�X�P�C���A���ӂ��Ӓ���
			// Mfilter = ���ʃo�c�O���̃_���[�W���y����������ɂ��␳(0.75�{): �n�[�h���b�N�A�t�B���^�[�A�v���Y���A�[�}�[
			// MTwice = �����@�钆�̒n�k/�}�O�j�`���[�h�A�_�C�r���O���̔g���A�������Ȃ�ւ̂ӂ݂��� -> �f�[�^�x�[�X�ɓ��ꂽ�����ǂ�����
			// MProtect�͌���̑�㐢��ł͑��݂��Ȃ��i���ɑ΂���Z�Z����1/4�␳�j
			// �����␳ = 85 �` 100�̗����������A���̌�100�Ŋ���
			// �����␳�͑S�Ă̑����{�����o���āA�|���Z�������Ɛ؂�̂Ă�
			// �Ǖ␳�́A�h�䑤�̏��1�C�Ȃ�0.5�{�A2�C�ȏ�o���Ă����2732/4096�{
			// ����^�C�v�̉Η͂��グ��A�C�e��(�_��̂�������)�́A�З͂�4915/4096�{����

			// �T�C�R�V���b�N���̌v�Z������ȋZ�́AA/D/M����Ǝ��v�Z����K�v������̂ŁA���ƂŎ�������
			// 4096��12bit�Œ菬���_���Z�̂��߁i�����ň����ƁA1.0��4096�ƂȂ�j
			std::vector<int> tmpresult( 32 ); // �}���̗L�����ꂼ��ɂ��āA�����ɂ��16�p�^�[���̃_���[�W���Z�o����
			int damage = 4096;
			int A = 4096, D = 4096, M = 4096;
			int Mhalf = 4096, Mfilter = 4096, MTwice = 4096;

			/* STEP1. A/D������ */ // --> �v�m�F�I�I�I�@�����N�␳���Ă�����A/D�𒼐ڂ�����H
			if ( m_moveDB[atkmove].m_category == 0 )
			{
				continue; // �ω��Z�͏������Ȃ�
			}
			if ( m_moveDB[atkmove].m_category & PokeMove::PHYSICS_CHECK )
			{
				// �����Z�̎��́A�U�����́u�U���v�Ɩh�䑤�́u�h��v���g��
				A *= atk.m_Attack; D *= def.m_Block;
			}
			if ( m_moveDB[atkmove].m_category & PokeMove::SPECIAL_CHECK )
			{
				// ����Z�̎��́A�U�����́u���U�v�Ɩh�䑤�́u���h�v���g��
				A *= atk.m_Contact; D *= def.m_Diffence;
			}

			// �����_�[���[���̏ꍇ��D���Čv�Z���鏈��������i�h��Ɠ��h�����ւ���j
			// �T�C�R�V���b�N���̏����������ɂ����H
			// �\�[���[�r�[���͈З͂��ς�邩��A�͈͕␳����ɂ����������c�H
			// �З͕ω��n�̋Z�́A�ʓr��p�֐�����Čv�Z���������ǂ�����
			// A��D���ς��^�C�v�̈З͕ω��n�i�t�H�g���Q�C�U�[�Ƃ��j�͂������Ȃ��c�B

			/* STEP2. �ŏ���()�����v�Z */
			/* STEP2-1. �З͂����� */
			int power = m_moveDB[atkmove].m_power;
			if ( option.m_item & CBattleSettings::ITEM_LIFEORB )
			{
				// �^�C�v�����A�C�e���Ȃ�З�4915/4096�{
				power *= 4915; power /= 4096;
			}

			/* �ȉ��A�T�C�R�t�B�[���h�Ń��C�h�t�H�[�X�Ƃ��A�W���C���{�[���Ƃ��A������������v�Z���� */

			/* STEP2-2. A/D�Ƀ����N�␳������̂͂����H */
			// -> �}���ɓ�����ꍇ�͕s���Ȍ��ʂ𖳎�����̂ŁA������Ƃ߂�ǂ����ƂɂȂ邩���c

			/* STEP2-LAST. �v�Z�����З͂��g���Ďc����v�Z */
			damage *= ( ( atk.m_Level * 2 ) / 5 ) + 2; damage = ( damage / 4096 ) * 4096;
			damage *= ( power * A ) / D; damage = ( damage / 4096 ) * 4096;
			damage /= 50; damage += 2; damage = ( damage / 4096 ) * 4096;

			/* STEP3. �͈͕␳ */
			damage *= m_moveDB[atkmove].m_range; damage += 2047; damage /= 4096; damage *= 4096;

			/* STEP4. �e�q���␳�͑�㐢��ɂ͑��݂��Ȃ� */

			/* STEP5. �V�C�␳ */
			if ( option.m_weather == 1 )
			{
				// ����̎��A���Z��1.5�{�A���Z��0.5�{
				if ( m_moveDB[atkmove].m_type == _T( "�ق̂�" ) )
					;
				else if ( m_moveDB[atkmove].m_type == _T( "�݂�" ) )
					;
			}
			else if ( option.m_weather == 2 )
			{
				// �J�̎��A���Z��0.5�{�A���Z��1.5�{
				// ����̎��A���Z��1.5�{�A���Z��0.5�{
				if ( m_moveDB[atkmove].m_type == _T( "�݂�" ) )
					;
				else if ( m_moveDB[atkmove].m_type == _T( "�ق̂�" ) )
					;
			}

			/* STEP6. �}���␳ */
			int damage_critical = damage * ( 2048 + 4096 ) / 4096;
			damage_critical += 2047; damage_critical /= 4096; damage_critical *= 4096;

			/* STEP7. �����␳ */
			for ( int i = 0; i < 16; ++i )
			{
				tmpresult[i] = damage * ( 85 + i ); tmpresult[i] /= 100; tmpresult[i] /= 4096; tmpresult[i] *= 4096;
				tmpresult[i + 16] = damage_critical * ( 85 + i ); tmpresult[i + 16] /= 100; tmpresult[i + 16] /= 4096; tmpresult[i + 16] *= 4096;
			}

			/* STEP8. �^�C�v��v�␳ */
			for ( auto &&type : atk.m_type )
			{
				if ( type == m_moveDB[atkmove].m_type )
				{
					for ( int i = 0; i < 32; ++i )
					{
						tmpresult[i] *= ( 4096 + 2048 );
						tmpresult[i] += 2047;
						tmpresult[i] /= 4096;
					}
				}
			}

			/* STEP9. �����␳ */
			double typecomp_res = 1.0;
			for ( auto &&type : def.m_type )
			{
				typecomp_res *= m_typecomp.check( m_moveDB[atkmove].m_type, type );
			}
			for ( int i = 0; i < 32; ++i ) // STEP����32��̃��[�v�����̔����Ȃ񂾂��ǂˁc
			{
				tmpresult[i] *= typecomp_res;
				tmpresult[i] /= 4096;
				tmpresult[i] *= 4096;
			}

			/* STEP10. �Ώ��␳ */
			for ( int i = 0; i < 32; ++i )
			{
				if ( option.m_isBurned )
				{
					tmpresult[i] *= 2048;
					tmpresult[i] += 2047;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11. M���v�Z���� */ // -> M���v�Z����ʊ֐�������������ǂ��C������B�ȉ�Mhalf�������l�B
			/* STEP11-1. �Ǖ␳ */
			if ( m_moveDB[atkmove].m_category & option.m_barrier )
			{
				// ���ނƕǂ̗L������v
				// ���e���o�[�X�g�Ƃ��t�H�g���Q�C�U�[�����邩�c
				//   bit�ɂ͋󂫂����邵�A��pbit����邩
				for ( int i = 0; i < 16; ++i ) // �}���ɓ���������ǂ͖���
				{
					if ( option.m_range )
					{
						// �_�u���␳�����鎞��2732/4096�{
						tmpresult[i] *= 2732;
					}
					else
					{
						// �V���O���Ȃ�0.5�{
						tmpresult[i] *= 2048;
					}
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-2. �u���C���t�H�[�X�␳�͑�㐢��ɂ͑��݂��Ȃ� */

			/* STEP11-3. �X�i�C�p�[�␳ */
			if ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
			{
				for ( int i = 16; i < 32; ++i ) // �}���ɓ����������A�X�ɈЗ͂�1.5�{
				{
					tmpresult[i] *= ( 2048 + 4096 );
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-4. ����߂��˕␳ */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( typecomp_res < 1.0 ) )
			{
				for ( int i = 0; i < 32; ++i )
				{
					// ���ʂ����ЂƂȉ��̏ꍇ�̓_���[�W2�{
					tmpresult[i] *= 8192;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-5. ���ӂ���(���Z��e)�␳ */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( m_moveDB[atkmove].m_type == _T( "�ق̂�" ) ) )
			{
				for ( int i = 0; i < 32; ++i )
				{
					// �������ӂ��ӂŉ��Z���e�����ꍇ�̓_���[�W2�{
					// ����͖h�䑤�̓������Q�Ƃ���̂Ŏ����ɒ��ӁI�I�I�I�I
					tmpresult[i] *= 8192;
					tmpresult[i] += 2048;
					tmpresult[i] /= 4096;
				}
			}

			/* STEP11-6. Mhalf�␳ */
			/* STEP11-6-1. �X�̗ؕ��␳ */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( m_moveDB[atkmove].m_category & PokeMove::SPECIAL_CHECK ) )
			{
				// �X�̗ؕ��œ���Z���󂯂鎞�͈З͔���
			}

			/* STEP11-6-2. �t�@���g���K�[�h�A�}���`�X�P�C���␳ */
			if ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
			{
				// �t�@���g���K�[�h�A�}���`�X�P�C�����������鎞�̓_���[�W����
				// -> �c�[���Ƃ��Ă̓`�F�b�N�{�b�N�X��ON/OFF�Ő؂�ւ���̂�HP����͂��Ȃ�
				// �t�@���g���K�[�h�́A�V���h�[���C�⃁�e�I�h���C�u�̓����ђʂ𖳎����Ĕ�������̂ŁA
				// �ʁX�Ɍv�Z���������ǂ�����
			}

			/* STEP11-6-3. �p���N���b�N�␳ */
			if ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
			{
				// ���̋Z���󂯂鎞�̓_���[�W����
				// �t�ɉ��Z���g�����͈З͏㏸�H
			}

			/* STEP11-6-4. ���ӂ���(�ڐG�Z)�␳ */
			if ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
			{
				// �ڐG�Z���󂯂鎞�̓_���[�W����
			}

			/* STEP11-7. Mfilter�␳ */
			/* STEP11-7-1. �n�[�h���b�N/�t�B���^�[�␳ */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( typecomp_res > 1.0 ) )
			{
				// �n�[�h���b�N/�t�B���^�[���������鎞�̓_���[�W0.75�{
				// �v���Y���A�[�}�[�́A�V���h�[���C�⃁�e�I�h���C�u�̓����ђʂ𖳎����Čy������̂ŁA�ʁX�Ɍv�Z
			}
			/* STEP11-7-2. �v���Y���A�[�}�[�␳ */
			if ( ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
				&& ( typecomp_res > 1.0 ) )
			{
				// �v���Y���A�[�}�[���������鎞�̓_���[�W0.75�{
			}

			/* STEP11-8. �t�����h�K�[�h�␳ */
			if ( option.m_ability & CBattleSettings::ABILITY_SNIPER )
			{
				// �t�����h�K�[�h���������鎞�̓_���[�W0.75�{
				// -> �c�[���Ƃ��Ă̓`�F�b�N�{�b�N�X��ON/OFF�Ő؂�ւ���
			}

			/* STEP11-9. �B�l�̑ѕ␳ */
			if ( ( option.m_item & CBattleSettings::ABILITY_SNIPER )
				&& ( typecomp_res > 1.0 ) )
			{
				// �B�l�̑т��������鎞�̓_���[�W1.2�{
			}

			/* STEP11-10. ���g���m�[���␳ */
			if ( option.m_item & CBattleSettings::ITEM_METRONOME )
			{
				// ���g���m�[���œ����Z��N��g������_���[�W�㏸
			}

			/* STEP11-11. ���̎�␳ */
			if ( option.m_item & CBattleSettings::ITEM_LIFEORB )
			{
				// ���̎�Ȃ�_���[�W1.3�{
			}

			/* STEP11-12. �������␳ */
			if ( ( option.m_item & CBattleSettings::ITEM_LIFEORB )
				&& ( typecomp_res > 1.0 ) )
			{
				// ��_�����̎��Ȃ�_���[�W0.5�{
			}

			/* STEP11-13. Mtwice�␳ */
			if ( option.m_twice )
			{
				// ����������Ń_���[�W2�{�̋Z���g�p����
			}

			/* STEP12. Mprotect�␳�͑�㐢��ɂ͑��݂��Ȃ� */
		}
	}

private:
	CDatabase *m_pDatabase;
	std::map<CString, PokeMove> m_moveDB;

	TypeCompatibility m_typecomp;
};

