#include "stdafx.h"
#include "PlayerTriggerBox.h"
#include "../enemy/Enemy.h"
#include "../enemy/boss/Boss.h"

namespace nsMyGame {

	namespace nsPlayer {

		void CPlayerTriggerBox::Update() {

			//�A�N�e�B�u��Ԃ���Ȃ��Ȃ�I���B
			if (!m_isActive) { return; }

			//���O��Enemy�̃I�u�W�F�N�g��CEnemy�N���X�ɃL���X�g�B
			QueryGOs<nsEnemy::CEnemy>(c_classNameEnemy, [this](nsEnemy::CEnemy* enemy) {

				//���̂Ƃ̓����蔻��𒲂ׂ�B
				CPhysicsWorld::GetInstance()->ContactTest(enemy->GetCharacterController(), [&](const btCollisionObject& contactObject) {

					//�܂��G������̍U�����󂯂Ă��Ȃ���ԂŃg���K�[�{�b�N�X�ƐڐG�����B
					if (m_attackCollision.IsSelf(contactObject)) {

						//�G�Ƀ_���[�W��^����B
						enemy->SetReceiveDamage(true);

						//�����Ԃ��G�t�F�N�g���Đ��B
						Effect* bloodEffect = NewGO<Effect>(enPriority_Zeroth);
						bloodEffect->Init(u"Assets/effect/bloodGreen.efk");
						bloodEffect->SetPosition(m_position);
						bloodEffect->SetScale({ 5.0f, 5.0f,5.0f });
						bloodEffect->Play();

						//�a��T�E���h���Đ��B
						CSoundManager::GetInstance()->Play(enSE_Kill);

						m_isActive = false;
					}
				});

				return true;
			});

			auto boss = FindGO<nsEnemy::CBoss>(c_classNameBoss);

			//�{�X���o�����Ă��Ȃ��Ȃ�I���B
			if (boss == nullptr) {
				return;
			}

			//���̂Ƃ̓����蔻��𒲂ׂ�B
			CPhysicsWorld::GetInstance()->ContactTest(boss->GetCharacterController(), [&](const btCollisionObject& contactObject) {

				//�܂��G������̍U�����󂯂Ă��Ȃ���ԂŃg���K�[�{�b�N�X�ƐڐG�����B
				if (m_attackCollision.IsSelf(contactObject)) {

					//�G�Ƀ_���[�W��^����B
					boss->SetReceiveDamage(true);

					//�����Ԃ��G�t�F�N�g���Đ��B
					Effect* bloodEffect = NewGO<Effect>(enPriority_Zeroth);
					bloodEffect->Init(c_bloodEffectFilePath);
					bloodEffect->SetPosition(m_position);
					bloodEffect->SetScale(c_bloodEffectSize);
					bloodEffect->Play();

					//�a��T�E���h���Đ��B
					CSoundManager::GetInstance()->Play(enSE_Kill);

					m_isActive = false;
				}
			});
		}
	}
}