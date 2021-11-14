#include "stdafx.h"
#include "GoteWinEnemyAttackCollisionDetection.h"
#include "../../player/Player.h"

namespace nsMyGame {

	namespace nsEnemy {

		void CGoteWinEnemyCollisionDetection::Create(const CVector3& pos, const CQuaternion& rot) {

			//�U���̓����蔻����쐬�B
			m_triggerBox.CreateBox(
				pos,
				rot,
				c_attackTriggerBoxSize
			);
		}

		void CGoteWinEnemyCollisionDetection::Activate(const CVector3& pos, const CQuaternion& rot) {

			if (!m_isActive) {

				//�g���K�[�{�b�N�X���쐬�B
				Create(pos, rot);

				m_player = FindGO<nsPlayer::CPlayer>("player");

				m_player->SetReceiveDamage(false);

				m_isActive = true;
			}
		}

		void CGoteWinEnemyCollisionDetection::Deactivate() {

			if (m_isActive) {

				//�g���K�[�{�b�N�X���폜�B
				m_triggerBox.Release();
				m_isActive = false;
			}
		}


		void CGoteWinEnemyCollisionDetection::Update(const CVector3& pos, const CQuaternion& rot, const CVector3& forward) {

			//�A�N�e�B�u����Ȃ��Ȃ�I���B
			if (!m_isActive) {

				return;
			}

			//���W�����߂�B
			CVector3 position = pos;
			position.y += c_attackTriggerBoxSize.y / 2;

			//���W�Ɖ�]��ݒ�B
			m_triggerBox.SetPosition(position + forward * c_attackTriggerBoxMul);
			m_triggerBox.SetRotation(rot);

			//���̂Ƃ̓����蔻��𒲂ׂ�B
			CPhysicsWorld::GetInstance()->ContactTest(m_player->GetCharacterController(), [&](const btCollisionObject& contactObject) {

				//�܂��v���C���[������̍U�����󂯂Ă��Ȃ���ԂŃg���K�[�{�b�N�X�ƐڐG�����B
				if (!m_player->GetReceiveDamage() && m_triggerBox.IsSelf(contactObject)) {

					if (m_player->IsGuard()) {

						m_isGuarded = true;
					}
					else {
					
						m_isGuarded = false;
					}

					//�v���C���[�Ƀ_���[�W��^����B
					m_player->SetReceiveDamage(true);
				}
			});
		}
	}
}
