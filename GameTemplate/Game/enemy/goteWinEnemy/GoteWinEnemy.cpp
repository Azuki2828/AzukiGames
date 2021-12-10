#include "stdafx.h"
#include "GoteWinEnemy.h"

namespace nsMyGame {

	namespace nsEnemy {

		extern CEnemy* g_pCurrentEnemy;

		bool CGoteWinEnemy::StartSub() {

			//�������W��ݒ�B
			//m_position = { 900.0f,500.0f,-1200.0f };

			//�L�����N�^�[�R���g���[���[���������B
			m_charaCon.Init(
				20.0f,			//���a�B
				100.0f,			//�����B
				m_position		//���W�B
			);

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

		void CGoteWinEnemy::UpdateSub() {

			// ���ݍX�V���������s���̃G�l�~�[�̃A�h���X����
			g_pCurrentEnemy = this;

			//�X�e�[�g�ɉ����ēǂݍ���Python�X�N���v�g��ς���B
			switch (m_state) {

			case enState_Idle:
				ImportModule("GoteWinEnemyIdle");
				break;
			case enState_Walk:
				ImportModule("GoteWinEnemyMove");
				break;
			case enState_Attack:
				ImportModule("GoteWinEnemyAttack");
				break;
			case enState_Guard:
				ImportModule("GoteWinEnemyGuard");
				break;
			case enState_Damage:
				ImportModule("GoteWinEnemyDamage");
				break;
			case enState_Death:
				ImportModule("GoteWinEnemyDeath");
				break;
			case enState_AttackBreak:
				ImportModule("GoteWinEnemyAttackBreak");
				break;
			}

			//Python�X�N���v�g��Update()�֐����Ăяo���B
			auto updateFunc = m_enemyPyModule.attr("Update");
			updateFunc();
			
		}

		void CGoteWinEnemy::InitStatus() {

			m_status.hp = 100;
			m_status.attack = 10;
		}

		void CGoteWinEnemy::InitAnimationClip() {

			//�A�j���[�V�����N���b�v��ݒ�B
			m_animationClip[enAnim_Walk].Load("Assets/animData/walk.tka");
			m_animationClip[enAnim_Walk].SetLoopFlag(true);
			m_animationClip[enAnim_Idle].Load("Assets/animData/goteWinEnemyIdle.tka");
			m_animationClip[enAnim_Idle].SetLoopFlag(true);
			m_animationClip[enAnim_Attack].Load("Assets/animData/attack.tka");
			m_animationClip[enAnim_Attack].SetLoopFlag(false);
			m_animationClip[enAnim_Guard].Load("Assets/animData/guard.tka");
			m_animationClip[enAnim_Guard].SetLoopFlag(false);
			m_animationClip[enAnim_Damage].Load("Assets/animData/damage.tka");
			m_animationClip[enAnim_Damage].SetLoopFlag(false);
			m_animationClip[enAnim_Death].Load("Assets/animData/death.tka");
			m_animationClip[enAnim_Death].SetLoopFlag(false);
			m_animationClip[enAnim_AttackBreak].Load("Assets/animData/attackBreak.tka");
			m_animationClip[enAnim_AttackBreak].SetLoopFlag(false);
		}

		void CGoteWinEnemy::AnimationUpdate() {

			//�e�X�e�[�g�ɑΉ������A�j���[�V�������Đ�����B
			switch (m_state) {
			case enState_Idle:
				m_modelRender->PlayAnimation(enAnim_Idle, 0.4f);
				break;
			case enState_Walk:
				m_modelRender->PlayAnimation(enAnim_Walk, 0.4f);
				break;
			case enState_Attack:
				m_modelRender->PlayAnimation(enAnim_Attack, 0.4f);
				break;
			case enState_Guard:
				m_modelRender->PlayAnimation(enAnim_Guard, 0.4f);
				break;
			case enState_Damage:
				m_modelRender->PlayAnimation(enAnim_Damage, 0.4f);
				break;
			case enState_Death:
				m_modelRender->PlayAnimation(enAnim_Death, 0.4f);
				break;
			case enState_AttackBreak:
				m_modelRender->PlayAnimation(enAnim_AttackBreak, 0.4f);
				break;
			}
		}

		void CGoteWinEnemy::Move() {
			//x������z�����̈ړ����x���������B
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;

			//�v���C���[�̍��W���擾����B
			CVector3 toPlayerVec = m_player->GetPosition() - m_position;

			//���K���B
			toPlayerVec.Normalize();

			//������ԂȂ�v���C���[�Ɉ�葬�x�ŋ߂Â��B
			if (m_state == enState_Walk) {

				m_moveSpeed += toPlayerVec * 150.0f;
			}

			//�d�͂�������B
			m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();

			//���W��ݒ�B
			m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			//�n�ʂɂ��Ă��邩����B
			if (m_charaCon.IsOnGround()) {

				//�n�ʂɂ��Ă���Ȃ牺�����ɂ͗͂������Ȃ��B
				m_moveSpeed.y = 0.0f;
			}
		}

		void CGoteWinEnemy::UpdateTriggerBox(const CVector3& pos, const CQuaternion& rot, const CVector3& forward) {

			//�U����ԂȂ�
			if (m_state == enState_Attack) {

				//�a��^�C�~���O�Ńg���K�[�{�b�N�X��L���ɂ���B
				if (m_coolTime > 0.2f && m_coolTime < 0.6f) {

					m_triggerBox.Activate(pos, rot);
				}
				//����ȊO�͖����ɂ���B
				else {

					m_triggerBox.Deactivate();
				}
			}
			//�U�����ȊO�͖����ɂ���B
			else {

				m_triggerBox.Deactivate();
			}

			//�g���K�[�{�b�N�X���X�V�B
			m_triggerBox.Update(pos, rot, forward);
		}
	}
}