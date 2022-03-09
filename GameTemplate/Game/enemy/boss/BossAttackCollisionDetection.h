#pragma once
#include "../constEnemy.h"
#include "../../AttackCollision.h"

namespace nsMyGame {

	namespace nsEnemy {

		//���K���̓G�̍U�������Ɏg���g���K�[�{�b�N�X�̃N���X
		class CBossCollisionDetection
		{
		public:
			/**
			 * @brief �g���K�[�{�b�N�X���쐬����֐��B
			 * @param pos ���W
			 * @param rot ��]
			*/
			void Create(const CVector3& pos, const CQuaternion& rot) {

				m_attackCollision.CreateBox(pos, rot, c_bossAttackTriggerBoxSize);
				m_jumpAttackCollision.CreateBox(pos, rot, { 500.0f,100.0f,500.0f });
			}

			/**
			 * @brief �g���K�[�{�b�N�X��L���ɂ���֐��B
			*/
			void ActivateAttack() {

				m_isAttackActive = true;
			}

			/**
			 * @brief �g���K�[�{�b�N�X�𖳌��ɂ���֐��B
			*/
			void DeactivateAttack() {

				m_isAttackActive = false;
			}

			/**
			 * @brief �g���K�[�{�b�N�X��L���ɂ���֐��B
			*/
			void ActivateRangeAttack() {

				m_isRangeAttackActive = true;
			}

			/**
			 * @brief �g���K�[�{�b�N�X�𖳌��ɂ���֐��B
			*/
			void DeactivateRangeAttack() {

				m_isRangeAttackActive = false;
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
			*/
			void Update(const CVector3& pos);

			/**
			 * @brief �U�����K�[�h���ꂽ�H
			 * @return �U�����K�[�h���ꂽ���ǂ����̃t���O
			*/
			const bool IsGuarded()const {

				return m_isGuarded;
			}
		private:
			bool m_isAttackActive = false;			//�g���K�[�{�b�N�X���L���H
			bool m_isRangeAttackActive = false;			//�g���K�[�{�b�N�X���L���H
			bool m_isGuarded = false;			//�U�����K�[�h���ꂽ�H

			CPhysicsGhostObject m_attackCollision;	//�U���p�����蔻��
			CPhysicsGhostObject m_jumpAttackCollision;	//�U���p�����蔻��
		};
	}
}

