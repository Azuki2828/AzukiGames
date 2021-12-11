#pragma once
#include "../../AttackCollision.h"

namespace nsMyGame {

	namespace nsEnemy {
		
		//���K���̓G�̍U�������Ɏg���g���K�[�{�b�N�X�̃N���X
		class CFirstWinEnemyAttackCollisionDetection
		{
		public:
			/**
			 * @brief �g���K�[�{�b�N�X���쐬����֐��B
			 * @param pos ���W
			 * @param rot ��]
			*/
			void Create(const CVector3& pos, const CQuaternion& rot) {

				m_attackCollision.CreateBox(pos, rot, c_attackTriggerBoxSize);
			}

			/**
			 * @brief �g���K�[�{�b�N�X��L���ɂ���֐��B
			 * @param pos ���W
			 * @param rot ��]
			*/
			void Activate() {

				m_isActive = true;
			}

			/**
			 * @brief �g���K�[�{�b�N�X�𖳌��ɂ���֐��B
			*/
			void Deactivate() {

				m_isActive = false;
			}

			/**
			 * @brief ���W�Ɖ�]���X�V����֐��B
			 * @param worldMatrix ���[���h�s��
			*/
			void UpdatePositionAndRotation(const CMatrix& worldMatrix) {

				CVector3 position;
				position.x = worldMatrix.m[3][0];
				position.y = worldMatrix.m[3][1];
				position.z = worldMatrix.m[3][2];
				m_attackCollision.SetPosition(position);

				CQuaternion rotation;
				rotation.SetRotation(worldMatrix);
				m_attackCollision.SetRotation(rotation);
			}

			/**
			 * @brief �X�V�֐��B
			 * @param pos ���W
			 * @param rot ��]
			 * @param forward �O����
			*/
			void Update();

			/**
			 * @brief �U�����K�[�h���ꂽ�H
			 * @return �U�����K�[�h���ꂽ���ǂ����̃t���O
			*/
			const bool IsGuarded()const {

				return m_isGuarded;
			}
		private:
			bool m_isActive = false;			//�g���K�[�{�b�N�X���L���H
			bool m_isGuarded = false;			//�U�����K�[�h���ꂽ�H

			CPhysicsGhostObject m_attackCollision;	//�U���p�����蔻��
		};
	}
}

