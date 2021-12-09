#include "stdafx.h"
#include "PlayerStateProcess.h"
#include "Player.h"
#include "../AttackCollision.h"
#include "../enemy/Enemy.h"
#include "../BackGround.h"

namespace nsMyGame {

	namespace nsPlayer {

		bool CPlayer::Start() {

			//�������W��ݒ�B
			m_position = c_playerStartPosition;

			//�X�e�[�^�X���������B
			InitStatus();

			//IGameObject�ɒǉ��B
			m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);

			//tkm�t�@�C����tks�t�@�C����ݒ�B
			m_modelRender->SetFilePathTkm(c_filePathTkmPlayer);
			m_modelRender->SetFilePathTks(c_filePathTksPlayer);

			//�s���N���X���������B
			m_playerAction.Init(m_position, m_rotation, m_forward);

			//�A�j���[�V�����N���X���������B
			m_playerAnimation.Init();

			//�A�j���[�V�������������B
			m_modelRender->InitAnimation(m_playerAnimation.GetAnimationClip(), m_playerAnimation.GetAnimationNum());

			//�e�𗎂Ƃ��B
			m_modelRender->SetShadowCasterFlag(true);

			//�e���󂯂�B
			m_modelRender->SetShadowReceiverFlag(true);

			//�������B
			m_modelRender->Init();

			return true;
		}

		void CPlayer::OnDestroy() {

			DeleteGO(m_modelRender);
		}

		void CPlayer::Update() {

			//�X�V�����B
			switch (m_playerState) {

			case enState_Death:				//����ł�����

				IsDeathStateProcess();
				break;
			case enState_Rolling:			//���[�����O��

				IsRollingStateProcess();
				break;
			case enState_Damage:			//��e��

				IsDamagedStateProcess();
				break;
			default:						//�ʏ폈��

				CommonStateProcess();
				break;
			}
		}

		void CPlayer::JudgeDamage() {

			//�K�[�h�����Ȃ�K�[�h������ԂɁB
			if (m_playerState == enState_Guard) {

				m_playerState = enState_GuardSuccess;
				m_playerAction.GuardSuccess();
				return;
			}

			//��������Ă���G�̍U�������蔻��𒲂ׂ�B
			auto enemyCollision = FindGOs<CAttackCollision>(c_enemyAttackCollisionName);

			//�����蔻�菈���B
			//���̃t���[���őS�Ă̓����蔻��Ƃ̏Փ˔�������邽�߁A��C�Ƀ_���[�W���󂯂�\������B
			//���ꂪ���Ȃ�Afor���̓����ŃX�e�[�g�𒲂ׂ邱�ƁI
			for (auto& collision : enemyCollision) {

				//���̂Ƃ̓����蔻��𒲂ׂ�B
				CPhysicsWorld::GetInstance()->ContactTest(m_playerAction.GetCharacterController(), [&](const btCollisionObject& contactObject) {

					//�g���K�[�{�b�N�X�ƐڐG�����B
					if (collision->IsSelf(contactObject)) {

						//�_���[�W���󂯂�B
						ReceiveDamage();
					}
				});
			}
		}

		void CPlayer::UpdateForward() {

			//��]�s����v�Z�B
			auto mRot = CMatrix::Identity;
			mRot.MakeRotationFromQuaternion(m_rotation);

			//�O������ݒ�B
			m_forward.x = mRot.m[2][0];
			m_forward.y = mRot.m[2][1];
			m_forward.z = mRot.m[2][2];

			//���K���B
			m_forward.Normalize();
		}

		void CPlayer::LightCameraUpdate() {

			//�w�i�N���X�������B
			auto backGround = FindGO<CBackGround>(c_classNameBackGround);

			//���C�g�J�����̏����X�V�B
			CVector3 m_lightCameraTar = m_position;
			auto ligDirection = backGround->GetSunDirectionLight()->GetLigDirection();
			CVector3 m_lightCameraPos = m_lightCameraTar - *ligDirection * 300.0f;

			//���C�g�J�����̏���ݒ�B
			CCamera::GetLightCamera()->SetPosition(m_lightCameraPos);
			CCamera::GetLightCamera()->SetTarget(m_lightCameraTar);
			CCamera::GetLightCamera()->SetFar(800.0f);

			//�J�����̏���������߂�B
			CVector3 Vec_x = CVector3::AxisX;
			CVector3 TarPos = CCamera::GetLightCamera()->GetTarget() - CCamera::GetLightCamera()->GetPosition();
			TarPos.Normalize();
			CVector3 CameraUp;
			CameraUp.Cross(TarPos, Vec_x);
			CameraUp.Normalize();

			//�������ݒ�B
			CCamera::GetLightCamera()->SetUp(CameraUp);

			//���C�g�J�������X�V�B
			CCamera::GetLightCamera()->Update();

			//���s���e�ɐݒ�B
			CCamera::GetLightCamera()->SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
		}

		void CPlayer::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName) {

			//(void)clipName;
			////�L�[�̖��O���uattack_start�v�̎��B
			//if (wcscmp(eventName, L"attack_start") == 0) {
			//	//�a���G�t�F�N�g���쐬����B
			//	MakeSlashingEffect();
			//	//�U�����ɂ���B
			//	m_isUnderAttack = true;
			//}
			////�L�[�̖��O���uattack_end�v�̎��B
			//else if (wcscmp(eventName, L"attack_end") == 0) {
			//	//�U�����I���B
			//	m_isUnderAttack = false;
			//}
			////�L�[�̖��O���umagic_attack�v�̎��B
			//else if (wcscmp(eventName, L"magic_attack") == 0) {
			//	//�t�@�C���[�{�[�����쐬����B
			//	MakeFireBall();
			//}
		}
	}
}