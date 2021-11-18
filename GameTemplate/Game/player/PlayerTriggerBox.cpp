#include "stdafx.h"
#include "PlayerTriggerBox.h"
#include "../enemy/Enemy.h"

namespace nsMyGame {

	namespace nsPlayer {
		
		void CPlayerTriggerBox::Create(const CVector3& pos, const CQuaternion& rot) {

			//�U���̓����蔻����쐬�B
			m_ghostBox.CreateBox(
				pos,
				rot,
				c_attackTriggerBoxSize
			);
		}

		void CPlayerTriggerBox::Activate(const CVector3& pos, const CQuaternion& rot) {

			if (!m_isActive) {

				//�g���K�[�{�b�N�X���쐬�B
				Create(pos, rot);

				//���O��Enemy�̃I�u�W�F�N�g��CEnemy�N���X�ɃL���X�g�B
				//�G���܂�����̍U�����󂯂Ă��Ȃ��悤�ɐݒ�B
				QueryGOs<nsEnemy::CEnemy>(c_classNameEnemy, [this](nsEnemy::CEnemy* enemy) {

					enemy->SetReceiveDamage(false);
					return true;
				});

				m_isActive = true;
			}
		}

		void CPlayerTriggerBox::Deactivate() {
			
			if (m_isActive) {

				m_ghostBox.Release();
				m_isActive = false;
			}
		}


		void CPlayerTriggerBox::Update(const CVector3& pos, const CQuaternion& rot, const CVector3& forward) {

			if (m_isActive) {

				//���W�����߂�B
				CVector3 position = pos;
				position.y += c_attackTriggerBoxSize.y / 2;

				//���W�Ɖ�]��ݒ�B
				m_ghostBox.SetPosition(position + forward * c_attackTriggerBoxMul);
				m_ghostBox.SetRotation(rot);

				//���O��Enemy�̃I�u�W�F�N�g��CEnemy�N���X�ɃL���X�g�B
				QueryGOs<nsEnemy::CEnemy>(c_classNameEnemy, [this](nsEnemy::CEnemy* enemy) {

					//���̂Ƃ̓����蔻��𒲂ׂ�B
					CPhysicsWorld::GetInstance()->ContactTest(enemy->GetCharacterController(), [&](const btCollisionObject& contactObject) {

						//�܂��G������̍U�����󂯂Ă��Ȃ���ԂŃg���K�[�{�b�N�X�ƐڐG�����B
						if (!enemy->GetReceiveDamage() && m_ghostBox.IsSelf(contactObject)) {

							//�G���폜�B
							//enemy->Delete();
							//�G�Ƀ_���[�W��^����B
							enemy->SetReceiveDamage(true);
						}
					});

					return true;
				});
			}
		}
	}
}