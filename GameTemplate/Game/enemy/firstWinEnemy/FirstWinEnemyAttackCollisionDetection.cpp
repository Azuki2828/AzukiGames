#include "stdafx.h"
#include "FirstWinEnemyAttackCollisionDetection.h"
#include "../../player/Player.h"

namespace nsMyGame {

	namespace nsEnemy {

		void CFirstWinEnemyAttackCollisionDetection::Create(const CVector3& pos, const CQuaternion& rot) {

			//�U���̓����蔻����쐬�B
			m_ghostBox.CreateBox(
				pos,
				rot,
				c_attackTriggerBoxSize
			);
			
		}

		void CFirstWinEnemyAttackCollisionDetection::Activate(const CVector3& pos, const CQuaternion& rot) {

			if (!m_isActive) {

				//�g���K�[�{�b�N�X���쐬�B
				Create(pos, rot);

				//�v���C���[��T���B
				m_player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

				//�_���[�W�t���O��false�ɐݒ�B
				m_player->SetReceiveDamage(false);

				//�g���K�[�{�b�N�X��L���ɂ���B
				m_isActive = true;
			}
		}

		void CFirstWinEnemyAttackCollisionDetection::Deactivate() {

			if (m_isActive) {

				//�g���K�[�{�b�N�X���폜�B
				m_ghostBox.Release();
				//�g���K�[�{�b�N�X�𖳌��ɂ���B
				m_isActive = false;
				m_isGuarded = false;
			}
		}


		void CFirstWinEnemyAttackCollisionDetection::Update(const CVector3& pos, const CQuaternion& rot, const CVector3& forward) {

			//�A�N�e�B�u����Ȃ��Ȃ�I���B
			if (!m_isActive) {

				return;
			}

			//���W�����߂�B
			CVector3 position = pos;
			position.y += c_attackTriggerBoxSize.y / 2;

			//���W�Ɖ�]��ݒ�B
			m_ghostBox.SetPosition(position + forward * c_attackTriggerBoxMul);
			m_ghostBox.SetRotation(rot);

			//���̂Ƃ̓����蔻��𒲂ׂ�B
			CPhysicsWorld::GetInstance()->ContactTest(m_player->GetCharacterController(), [&](const btCollisionObject& contactObject) {

				//�܂��v���C���[������̍U�����󂯂Ă��Ȃ���ԂŃg���K�[�{�b�N�X�ƐڐG�����B
				if (!m_player->GetReceiveDamage() && m_ghostBox.IsSelf(contactObject)) {

					if (m_player->IsGuard()) {

						m_isGuarded = true;
					}

					//�v���C���[�Ƀ_���[�W��^����B
					m_player->SetReceiveDamage(true);
				}
			});
		}
	}
}
