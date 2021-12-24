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

			//������]��ݒ�B
			CQuaternion quaternion = CQuaternion::Identity;
			quaternion.SetRotationDegY(180.0f);
			m_rotation = quaternion;

			//�X�e�[�^�X���������B
			InitStatus();

			//IGameObject�ɒǉ��B
			m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);

			//tkm�t�@�C����tks�t�@�C����ݒ�B
			m_modelRender->SetFilePathTkm(c_filePathTkmPlayer);
			m_modelRender->SetFilePathTks(c_filePathTksPlayer);

			//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
			m_modelRender->AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {

				m_playerAction.OnAnimationEvent(clipName, eventName);
			});

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

			//���Ɏ��t����ꂽ�{�[���̔ԍ���ǂݍ��ށB
			int swordBoneNum = m_modelRender->GetSkeleton()->FindBoneID(L"mixamorig5:LeftHand");

			//���̃{�[�����擾�B
			Bone* swordBone = m_modelRender->GetSkeleton()->GetBone(swordBoneNum);

			//�s���N���X���������B
			m_playerAction.Init(m_position, m_rotation, m_forward, swordBone);
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
			case enState_Guard:
				IsGuardStateProcess();
				break;
			case enState_Attack:
				IsAttackStateProcess();
				break;
			default:						//�ʏ폈��

				CommonStateProcess();
				break;
			}
		}

		void CPlayer::JudgeDamage(const CVector3& effectPos) {

			//�K�[�h�������Ȃ�I���B
			if (m_playerState == enState_GuardSuccess || m_playerState == enState_Death) { return; }

			//�K�[�h�����Ȃ�K�[�h������ԂɁB
			if (m_playerState == enState_Guard) {

				m_playerState = enState_GuardSuccess;
				m_playerAction.GuardSuccess();

				//�K�[�hSE���Đ��B
				CSoundManager::GetInstance()->Play(enSE_Guard);

				//�����͂����ŏI���B
				return;
			}

			//�_���[�W���󂯂�B
			ReceiveDamage(effectPos);
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
	}
}