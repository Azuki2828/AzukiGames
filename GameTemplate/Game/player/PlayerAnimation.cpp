#include "stdafx.h"
#include "PlayerAnimation.h"
#include "Player.h"

namespace nsMyGame {

	namespace nsPlayer {

		namespace {

			constexpr float c_animationInterpolateTimeNormal = 0.8f;
			constexpr float c_animationInterpolateTimeDamage = 0.4f;
			constexpr float c_animationInterpolateTimeGuard = 0.4f;
			constexpr float c_animationInterpolateTimeGuardSuccess = 0.1f;
		}
		void CPlayerAnimation::Init(CModelRender& modelRender) {
			 
			//�A�j���[�V�����N���b�v���������B
			InitAnimationClip();
#if boneDebug

			//���f������X�P���g���̃t�@�C���p�X���擾���A�X�P���g�����\�z�B
			m_skeleton[enUpperBody].Init(modelRender.GetFilePathTks());
			m_skeleton[enLowerBody].Init(modelRender.GetFilePathTks());

			//�x�[�X�ƂȂ�A�j���[�V�������������B
			m_animation[enUpperBody].Init(m_skeleton[enUpperBody], m_animationClip[enUpperBody], enAnim_Num);
			m_animation[enLowerBody].Init(m_skeleton[enLowerBody], m_animationClip[enLowerBody], enAnim_Num);

			//�ŗL�̃A�j���[�V�����������Ă���B
			modelRender.GiveUniqueAnimation();

			//�v���C���[�������B
			auto player = FindGO<CPlayer>(c_classNamePlayer);

			//�A�j���[�V�����C�x���g��ݒ肷��B
			for (auto& animation : m_animation) {

				player->AddAnimationEvent(animation, modelRender);
			}
#else
			//���̃��f���̓A�j���[�V�������Đ�����B
			modelRender.SetAnimFlg(true);
#endif
		}

		void CPlayerAnimation::InitAnimationClip() {

			//�A�j���[�V�����N���b�v��ݒ�B
			m_animationClip[enUpperBody][enAnim_Walk].Load("Assets/animData/Nokey/Nwalk.tka");
			m_animationClip[enUpperBody][enAnim_Walk].SetLoopFlag(true);
			m_animationClip[enUpperBody][enAnim_Idle].Load("Assets/animData/idle.tka");
			m_animationClip[enUpperBody][enAnim_Idle].SetLoopFlag(true);
			m_animationClip[enUpperBody][enAnim_Run].Load("Assets/animData/NoKey/Nrun.tka");
			m_animationClip[enUpperBody][enAnim_Run].SetLoopFlag(true);
			m_animationClip[enUpperBody][enAnim_Attack].Load("Assets/animData/attack.tka");
			m_animationClip[enUpperBody][enAnim_Attack].SetLoopFlag(false);
			m_animationClip[enUpperBody][enAnim_AttackBreak].Load("Assets/animData/attackBreak.tka");
			m_animationClip[enUpperBody][enAnim_AttackBreak].SetLoopFlag(false);
			m_animationClip[enUpperBody][enAnim_Damage].Load("Assets/animData/damage.tka");
			m_animationClip[enUpperBody][enAnim_Damage].SetLoopFlag(false);
			m_animationClip[enUpperBody][enAnim_Rolling].Load("Assets/animData/NoKey/Nrolling.tka");
			m_animationClip[enUpperBody][enAnim_Rolling].SetLoopFlag(false);
			m_animationClip[enUpperBody][enAnim_Guard].Load("Assets/animData/guard.tka");
			m_animationClip[enUpperBody][enAnim_Guard].SetLoopFlag(true);
			m_animationClip[enUpperBody][enAnim_GuardSuccess].Load("Assets/animData/guardSuccess.tka");
			m_animationClip[enUpperBody][enAnim_GuardSuccess].SetLoopFlag(false);
			m_animationClip[enUpperBody][enAnim_Death].Load("Assets/animData/NoKey/Ndeath.tka");
			m_animationClip[enUpperBody][enAnim_Death].SetLoopFlag(false);
			m_animationClip[enUpperBody][enAnim_LeftWalk].Load("Assets/animData/leftWalk.tka");
			m_animationClip[enUpperBody][enAnim_LeftWalk].SetLoopFlag(true);
			m_animationClip[enUpperBody][enAnim_RightWalk].Load("Assets/animData/rightWalk.tka");
			m_animationClip[enUpperBody][enAnim_RightWalk].SetLoopFlag(true);

			//�A�j���[�V�����N���b�v��ݒ�B
			m_animationClip[enLowerBody][enAnim_Walk].Load("Assets/animData/walk.tka");
			m_animationClip[enLowerBody][enAnim_Walk].SetLoopFlag(true);
			m_animationClip[enLowerBody][enAnim_Idle].Load("Assets/animData/idle.tka");
			m_animationClip[enLowerBody][enAnim_Idle].SetLoopFlag(true);
			m_animationClip[enLowerBody][enAnim_Run].Load("Assets/animData/run.tka");
			m_animationClip[enLowerBody][enAnim_Run].SetLoopFlag(true);
			m_animationClip[enLowerBody][enAnim_Attack].Load("Assets/animData/NoKey/Nattack.tka");
			m_animationClip[enLowerBody][enAnim_Attack].SetLoopFlag(false);
			m_animationClip[enLowerBody][enAnim_AttackBreak].Load("Assets/animData/attackBreak.tka");
			m_animationClip[enLowerBody][enAnim_AttackBreak].SetLoopFlag(false);
			m_animationClip[enLowerBody][enAnim_Damage].Load("Assets/animData/damage.tka");
			m_animationClip[enLowerBody][enAnim_Damage].SetLoopFlag(false);
			m_animationClip[enLowerBody][enAnim_Rolling].Load("Assets/animData/rolling.tka");
			m_animationClip[enLowerBody][enAnim_Rolling].SetLoopFlag(false);
			m_animationClip[enLowerBody][enAnim_Guard].Load("Assets/animData/guard.tka");
			m_animationClip[enLowerBody][enAnim_Guard].SetLoopFlag(true);
			m_animationClip[enLowerBody][enAnim_GuardSuccess].Load("Assets/animData/guardSuccess.tka");
			m_animationClip[enLowerBody][enAnim_GuardSuccess].SetLoopFlag(false);
			m_animationClip[enLowerBody][enAnim_Death].Load("Assets/animData/death.tka");
			m_animationClip[enLowerBody][enAnim_Death].SetLoopFlag(false);
			m_animationClip[enLowerBody][enAnim_LeftWalk].Load("Assets/animData/leftWalk.tka");
			m_animationClip[enLowerBody][enAnim_LeftWalk].SetLoopFlag(true);
			m_animationClip[enLowerBody][enAnim_RightWalk].Load("Assets/animData/rightWalk.tka");
			m_animationClip[enLowerBody][enAnim_RightWalk].SetLoopFlag(true);
		}

		void CPlayerAnimation::Update(CModelRender& modelRender, const EnPlayerState& playerState) {

#if boneDebug

			//�v���C���[�X�e�[�g�ɉ����ăA�j���[�V�������Đ��B

			switch (playerState) {
			case enState_Idle:
				m_animation[enUpperBody].Play(enAnim_Idle, c_animationInterpolateTimeNormal);
				m_animation[enLowerBody].Play(enAnim_Idle, c_animationInterpolateTimeNormal);
				break;
			case enState_Walk:
				m_animation[enUpperBody].Play(enAnim_Walk, c_animationInterpolateTimeNormal);
				m_animation[enLowerBody].Play(enAnim_Walk, c_animationInterpolateTimeNormal);
				break;
			case enState_LeftWalk:
				m_animation[enUpperBody].Play(enAnim_LeftWalk, c_animationInterpolateTimeNormal);
				m_animation[enLowerBody].Play(enAnim_LeftWalk, c_animationInterpolateTimeNormal);
				break;
			case enState_RightWalk:
				m_animation[enUpperBody].Play(enAnim_RightWalk, c_animationInterpolateTimeNormal);
				m_animation[enLowerBody].Play(enAnim_RightWalk, c_animationInterpolateTimeNormal);
				break;
			case enState_Run:
				m_animation[enUpperBody].Play(enAnim_Run, c_animationInterpolateTimeNormal);
				m_animation[enLowerBody].Play(enAnim_Run, c_animationInterpolateTimeNormal);
				break;
			case enState_Attack:
				m_animation[enUpperBody].Play(enAnim_Attack, c_animationInterpolateTimeNormal);
				m_animation[enLowerBody].Play(enAnim_Attack, c_animationInterpolateTimeNormal);
				break;
			case enState_AttackBreak:
				m_animation[enUpperBody].Play(enAnim_AttackBreak, c_animationInterpolateTimeNormal);
				m_animation[enLowerBody].Play(enAnim_AttackBreak, c_animationInterpolateTimeNormal);
				break;
			case enState_Damage:
				m_animation[enUpperBody].Play(enAnim_Damage, c_animationInterpolateTimeDamage);
				m_animation[enLowerBody].Play(enAnim_Damage, c_animationInterpolateTimeDamage);
				break;
			case enState_Rolling:
				m_animation[enUpperBody].Play(enAnim_Rolling, c_animationInterpolateTimeNormal);
				m_animation[enLowerBody].Play(enAnim_Rolling, c_animationInterpolateTimeNormal);
				break;
			case enState_Guard:
				//�K�[�h���Ȃ���ړ��̍����A�j���[�V����
				if (m_isMove) {
					m_animation[enUpperBody].Play(enAnim_Guard, c_animationInterpolateTimeGuard);
					m_animation[enLowerBody].Play(enAnim_Walk, c_animationInterpolateTimeGuard);
				}
				//�K�[�h�A�j���[�V����
				else {
					m_animation[enUpperBody].Play(enAnim_Guard, c_animationInterpolateTimeGuard);
					m_animation[enLowerBody].Play(enAnim_Guard, c_animationInterpolateTimeGuard);
				}
				break;
			case enState_GuardSuccess:
				m_animation[enUpperBody].Play(enAnim_GuardSuccess, c_animationInterpolateTimeGuardSuccess);
				m_animation[enLowerBody].Play(enAnim_GuardSuccess, c_animationInterpolateTimeGuardSuccess);
				break;
			case enState_Death:
				m_animation[enUpperBody].Play(enAnim_Death, c_animationInterpolateTimeNormal);
				m_animation[enLowerBody].Play(enAnim_Death, c_animationInterpolateTimeNormal);
				break;
			}

			//�A�j���[�V������i�߂�B
			m_animation[enUpperBody].Progress(m_animationSpeed * g_gameTime->GetFrameDeltaTime());
			m_animation[enLowerBody].Progress(m_animationSpeed * g_gameTime->GetFrameDeltaTime());

			//�X�P���g�������f�������_�[�̃X�P���g���ɃR�s�[�B
			modelRender.CopyBone(m_skeleton[enUpperBody], m_skeleton[enLowerBody], m_upperBoneName, m_lowerBoneName, c_upperBoneNum, c_lowerBoneNum);
			modelRender.GetSkeleton()->Update(modelRender.GetModel()->GetWorldMatrix());
#else
			switch (playerState) {
			case enState_Idle:
				modelRender.PlayAnimation(enAnim_Idle, 0.8f);
				break;
			case enState_Walk:
				modelRender.PlayAnimation(enAnim_Walk, 0.8f);
				break;
			case enState_LeftWalk:
				modelRender.PlayAnimation(enAnim_LeftWalk, 0.8f);
				break;
			case enState_RightWalk:
				modelRender.PlayAnimation(enAnim_RightWalk, 0.8f);
				break;
			case enState_Run:
				modelRender.PlayAnimation(enAnim_Run, 0.8f);
				break;
			case enState_Attack:
				modelRender.PlayAnimation(enAnim_Attack, 0.8f);
				break;
			case enState_AttackBreak:
				modelRender.PlayAnimation(enAnim_AttackBreak, 0.8f);
				break;
			case enState_Damage:
				modelRender.PlayAnimation(enAnim_Damage, 0.4f);
				break;
			case enState_Rolling:
				modelRender.PlayAnimation(enAnim_Rolling, 0.8f);
				break;
			case enState_Guard:
				modelRender.PlayAnimation(enAnim_Guard, 0.4f);
				break;
			case enState_GuardSuccess:
				modelRender.PlayAnimation(enAnim_GuardSuccess, 0.1f);
				break;
			case enState_Death:
				modelRender.PlayAnimation(enAnim_Death, 0.8f);
				break;
		}
#endif
			//�֐��̍Ō�ɂ͓����ĂȂ��悤�ɐݒ肷��B
			m_isMove = false;
		}
	}
}