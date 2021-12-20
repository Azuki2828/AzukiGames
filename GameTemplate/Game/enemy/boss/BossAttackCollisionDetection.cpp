#include "stdafx.h"
#include "BossAttackCollisionDetection.h"
#include "../../player/Player.h"

namespace nsMyGame {

	namespace nsEnemy {

		void CBossCollisionDetection::Update(const CVector3& pos) {

			//�͈͍U���p�̓����蔻��̍��W���X�V�B
			m_jumpAttackCollision.SetPosition(pos);

			//�K�[�h�t���O���������B
			m_isGuarded = false;

			//�v���C���[�������B
			auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

			//�v���C���[�̌����Ɏ��s�����Ȃ�I���B
			if (player == nullptr) { return; }

			//���̂Ƃ̓����蔻��𒲂ׂ�B
			CPhysicsWorld::GetInstance()->ContactTest(player->GetCharacterController(), [&](const btCollisionObject& contactObject) {

				//�g���K�[�{�b�N�X�ƐڐG�����B
				if (m_isAttackActive && m_attackCollision.IsSelf(contactObject)) {

					//�v���C���[���K�[�h��ԂȂ�K�[�h����A�����蔻������Ȃ��悤�ɐݒ肷��B
					if (player->IsGuard()) {

						m_isGuarded = true;
					}
					m_isAttackActive = false;
					//�v���C���[�ɍU���B
					player->JudgeDamage(pos);
				}

				if (m_isRangeAttackActive && m_jumpAttackCollision.IsSelf(contactObject)) {

					//�v���C���[���K�[�h��ԂȂ�K�[�h����A�����蔻������Ȃ��悤�ɐݒ肷��B
					if (player->IsGuard()) {

						m_isGuarded = true;					
					}

					//�v���C���[�ɍU���B
					player->JudgeDamage(pos);
					m_isRangeAttackActive = false;
				}
			});
		}
	}
}
