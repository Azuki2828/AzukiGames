#pragma once
#include "../constEnemy.h"

namespace nsMyGame {

	namespace nsPlayer {

		class CPlayer;
	}

	namespace nsEnemy {


		//���K���̓G�̍U�������Ɏg���g���K�[�{�b�N�X�̃N���X
		class CGoteWinEnemyCollisionDetection
		{
		private:
			/**
			 * @brief �g���K�[�{�b�N�X���쐬����֐��B
			 * @param pos ���W
			 * @param rot ��]
			*/
			void Create(const CVector3& pos, const CQuaternion& rot);
		public:

			/**
			 * @brief �g���K�[�{�b�N�X��L���ɂ���֐��B
			 * @param pos ���W
			 * @param rot ��]
			*/
			void Activate(const CVector3& pos, const CQuaternion& rot);

			/**
			 * @brief �g���K�[�{�b�N�X�𖳌��ɂ���֐��B
			*/
			void Deactivate();

			/**
			 * @brief �X�V�֐��B
			 * @param pos ���W
			 * @param rot ��]
			 * @param forward �O����
			*/
			void Update(const CVector3& pos, const CQuaternion& rot, const CVector3& forward);

			/**
			 * @brief �U�����K�[�h���ꂽ�H
			 * @return �U�����K�[�h���ꂽ���ǂ����̃t���O
			*/
			bool IsGuarded() {

				return m_isGuarded;
			}
		private:
			bool m_isActive = false;			//�g���K�[�{�b�N�X���L���H
			bool m_isGuarded = false;			//�U�����K�[�h���ꂽ�H

			CVector3 m_position;				//���W
			CQuaternion m_rotation;				//��]
			CVector3 m_forward;					//�O����
			CPhysicsGhostObject m_triggerBox;		//�g���K�[�{�b�N�X

			nsPlayer::CPlayer* m_player = nullptr;
		};
	}
}

