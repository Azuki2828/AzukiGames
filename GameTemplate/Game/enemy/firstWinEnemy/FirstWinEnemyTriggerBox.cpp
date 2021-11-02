#include "stdafx.h"
#include "FirstWinEnemyTriggerBox.h"

namespace nsMyGame {

	namespace nsEnemy {

		void CFirstWinEnemyTriggerBox::Create(const CVector3& pos, const CQuaternion& rot) {

			//�U���̓����蔻����쐬�B
			m_ghostBox.CreateBox(
				pos,
				rot,
				c_attackTriggerBoxSize
			);
			m_player = FindGO<nsPlayer::CPlayer>("player");
		}

		void CFirstWinEnemyTriggerBox::Activate(const CVector3& pos, const CQuaternion& rot) {

			if (!m_isActive) {

				//�g���K�[�{�b�N�X���쐬�B
				Create(pos, rot);

				//���O��Enemy�̃I�u�W�F�N�g��CEnemy�N���X�ɃL���X�g�B
				//�G���܂�����̍U�����󂯂Ă��Ȃ��悤�ɐݒ�B
				QueryGOs<nsEnemy::CEnemy>("Enemy", [this](nsEnemy::CEnemy* enemy) {

					enemy->SetReceiveDamage(false);
					return true;
					});

				m_isActive = true;
			}
		}

		void CFirstWinEnemyTriggerBox::Deactivate() {

			if (m_isActive) {

				m_ghostBox.Release();
				m_isActive = false;
			}
		}


		void CFirstWinEnemyTriggerBox::Update(const CVector3& pos, const CQuaternion& rot, const CVector3& forward) {

			if (m_isActive) {

				//���W�����߂�B
				CVector3 position = pos;
				position.y += c_attackTriggerBoxSize.y / 2;

				//���W�Ɖ�]��ݒ�B
				m_ghostBox.SetPosition(position + forward * c_attackTriggerBoxMul);
				m_ghostBox.SetRotation(rot);	

				//���̂Ƃ̓����蔻��𒲂ׂ�B
				CPhysicsWorld::GetInstance()->ContactTest(m_player->GetCharacterController(), [&](const btCollisionObject& contactObject) {

					//�܂��G������̍U�����󂯂Ă��Ȃ���ԂŃg���K�[�{�b�N�X�ƐڐG�����B
					if (!enemy->GetReceiveDamage() && m_ghostBox.IsSelf(contactObject)) {

						//�G���폜�B
						//enemy->Delete();
						//�G�Ƀ_���[�W��^����B
						enemy->SetReceiveDamage(true);
					}
				});
			}
		}
	}
}
