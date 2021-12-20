#include "stdafx.h"
#include "FirstWinEnemyAttackCollisionDetection.h"
#include "../../player/Player.h"

namespace nsMyGame {

	namespace nsEnemy {

		void CFirstWinEnemyAttackCollisionDetection::Update() {

			//�K�[�h�t���O���������B
			m_isGuarded = false;

			//�A�N�e�B�u����Ȃ��Ȃ�I���B
			if (!m_isActive) { return; }

			//�v���C���[�������B
			auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

			//�v���C���[�̌����Ɏ��s�����Ȃ�I���B
			if (player == nullptr) { return; }

			//���̂Ƃ̓����蔻��𒲂ׂ�B
			CPhysicsWorld::GetInstance()->ContactTest(player->GetCharacterController(), [&](const btCollisionObject& contactObject) {

				//�g���K�[�{�b�N�X�ƐڐG�����B
				if (m_attackCollision.IsSelf(contactObject)) {

					//�v���C���[���K�[�h��ԂȂ�K�[�h����A�����蔻������Ȃ��悤�ɐݒ肷��B
					if (player->IsGuard()) {

						m_isGuarded = true;
						m_isActive = false;
					}

					//�v���C���[�ɍU���B
					player->JudgeDamage(m_position);
				}
			});
		}
	}
}
