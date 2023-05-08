#pragma once

/* �_���[�W�v�Z���C���w�b�_ */
#include <Windows.h>
#include <afxdb.h>

#include <vector>
#include <map>
#include <memory>

#include "pokemove.hpp"
#include "pokemon.hpp"

class CCalcDamage{
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
			short nFields = rs.GetODBCFieldCount();
			std::vector<CDBVariant> var( nFields );
			while ( rs.IsEOF() != FALSE )
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
				m_move.emplace_back( PokeMove( *var[1].m_pstring, *var[2].m_pstring, PokeMove::getCategory( *var[3].m_pstring ),
											   var[4].m_lVal, var[5].m_lVal, var[7].m_boolVal ) );

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

	std::vector<std::pair<CString, std::vector<int>>> calc( PokemonData atk, PokemonData def ) {
		// �U�������o����S�Ă̍U���Z�Ń_���[�W�v�Z����
		// �߂�l�́A�u�Z���F�_���[�W�p�^�[��(�����Ƌ}���ɂ��S32�p�^�[��)�v���o����Z�S�ĂŌv�Z��������
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
		}
	}

private:
	CDatabase *m_pDatabase;
	std::vector<PokeMove> m_move;
};

