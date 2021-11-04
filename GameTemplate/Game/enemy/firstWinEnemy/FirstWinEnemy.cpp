#include "stdafx.h"
#include "FirstWinEnemy.h"

namespace nsMyGame {

	namespace nsEnemy {

		extern CEnemy* g_pCurrentEnemy;

		bool CFirstWinEnemy::StartSub() {
		
			//IGameObject�ɒǉ��B
			m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);
		
			//tkm�t�@�C����tks�t�@�C����ݒ�B
			m_modelRender->SetFilePathTkm(c_filePathTkmEnemy);
			m_modelRender->SetFilePathTks(c_filePathTksEnemy);
		
		
			//�A�j���[�V�����N���b�v���������B
			InitAnimationClip();
		
			//�A�j���[�V�������������B
			m_modelRender->InitAnimation(m_animationClip, enAnim_Num);
		
			//�e�𗎂Ƃ��B
			m_modelRender->SetShadowCasterFlag(true);
		
			//�e���󂯂�B
			m_modelRender->SetShadowReceiverFlag(true);
		
			//�X�e�[�^�X���������B
			InitStatus();

			//�������B
			m_modelRender->Init();
			return true;
		}

		void CFirstWinEnemy::UpdateSub() {

			// ���ݍX�V���������s���̃G�l�~�[�̃A�h���X����
			g_pCurrentEnemy = this;
			
			
			switch (m_state) {
			case enState_Idle:
				ImportModule("EnemyIdle");
				break;
			case enState_Walk:
				ImportModule("EnemyMove");
				break;
			case enState_ThreeCombo:
				ImportModule("EnemyAttack");
				break;
			case enState_Damage:
				ImportModule("EnemyDamage");
				break;
			case enState_Death:
				ImportModule("EnemyDeath");
				break;
			}

			auto updateFunc = m_enemyPyModule.attr("Update");
			updateFunc();
		}

		void CFirstWinEnemy::InitStatus() {

			m_status.hp = 100;
			m_status.attack = 10;
		}

		void CFirstWinEnemy::InitAnimationClip() {

			//�A�j���[�V�����N���b�v��ݒ�B
			m_animationClip[enAnim_Walk].Load("Assets/animData/walk.tka");
			m_animationClip[enAnim_Walk].SetLoopFlag(true);
			m_animationClip[enAnim_Idle].Load("Assets/animData/idle.tka");
			m_animationClip[enAnim_Idle].SetLoopFlag(true);
			m_animationClip[enAnim_ThreeCombo].Load("Assets/animData/threeCombo.tka");
			m_animationClip[enAnim_ThreeCombo].SetLoopFlag(false);
			m_animationClip[enAnim_Damage].Load("Assets/animData/damage.tka");
			m_animationClip[enAnim_Damage].SetLoopFlag(false);
			m_animationClip[enAnim_Death].Load("Assets/animData/death.tka");
			m_animationClip[enAnim_Death].SetLoopFlag(false);
		}

		void CFirstWinEnemy::AnimationUpdate() {

			switch (m_state) {
			case enState_Idle:
				m_modelRender->PlayAnimation(enAnim_Idle, 0.4f);
				break;
			case enState_Walk:
				m_modelRender->PlayAnimation(enAnim_Walk, 0.4f);
				break;
			case enState_ThreeCombo:
				m_modelRender->PlayAnimation(enAnim_ThreeCombo, 0.4f);
				break;
			case enState_Damage:
				m_modelRender->PlayAnimation(enAnim_Damage, 0.4f);
				break;
			case enState_Death:
				m_modelRender->PlayAnimation(enAnim_Death, 0.4f);
				break;
			}
		}

		void CFirstWinEnemy::Move() {

			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;

			CVector3 toPlayerVec = m_player->GetPosition() - m_position;
			toPlayerVec.Normalize();

			if (m_state == enState_Walk) {

				m_moveSpeed += toPlayerVec * 150.0f;
			}
			else if (m_state == enState_ThreeCombo) {

				if (c_threeComboCoolTime - m_coolTime < 2.4f) {
					m_moveSpeed += toPlayerVec * 50.0f;
				}
			}
			//�d�͂�������B
			m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();

			m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			//�n�ʂɂ��Ă��邩����B
			if (m_charaCon.IsOnGround()) {

				//�n�ʂɂ��Ă���Ȃ牺�����ɂ͗͂������Ȃ��B
				m_moveSpeed.y = 0.0f;
			}
		}

		void CFirstWinEnemy::UpdateTriggerBox(const CVector3& pos, const CQuaternion& rot, const CVector3& forward) {

			if (m_state == enState_ThreeCombo) {

				if (m_coolTime > 0.4f && m_coolTime < 0.8f) {

					m_triggerBox.Activate(pos, rot);
				}
				else if (m_coolTime > 1.3f && m_coolTime < 1.7f) {

					m_triggerBox.Activate(pos, rot);
				}
				else if (m_coolTime > 2.0f && m_coolTime < 2.4f) {

					m_triggerBox.Activate(pos, rot);
				}
				else {
					m_triggerBox.Deactivate();
				}
			}
			else {

				m_triggerBox.Deactivate();
			}

			//�g���K�[�{�b�N�X���X�V�B
			m_triggerBox.Update(pos, rot, forward);
		}
	}
}