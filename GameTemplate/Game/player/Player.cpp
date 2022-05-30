#include "stdafx.h"
#include "Player.h"
#include "PlayerStateProcess.h"
#include "../AttackCollision.h"
#include "../enemy/Enemy.h"
#include "../BackGround.h"

namespace nsMyGame {

	namespace nsPlayer {

		namespace {
			constexpr float lightCameraDirection = 300.0f;
			constexpr float lightCameraFar = 800.0f;
		}
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

			//�A�j���[�V�����ɑΉ�������B
			//m_modelRender->InitAnimation(m_playerAnimation.GetAnimationClip(), m_playerAnimation.GetAnimationNum());

			//�e�𗎂Ƃ��B
			m_modelRender->SetShadowCasterFlag(true);

			//�e���󂯂�B
			m_modelRender->SetShadowReceiverFlag(true);

			//�������B
			m_modelRender->Init();

			//�A�j���[�V�����N���X���������B
			m_playerAnimation.Init(*m_modelRender);

			//���Ɏ��t����ꂽ�{�[���̔ԍ���ǂݍ��ށB
			int swordBoneNum = m_modelRender->GetSkeleton()->FindBoneID(L"mixamorig5:LeftHandRing4");

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

			//����ł����Ԃ��ǂ�������B
			if (IsDeath()) { m_playerState = enState_Death; }

			//����ł��Ȃ��Ȃ�
			if (!IsDeath()) {

				//�ړ������B
				m_playerAction.Move(m_position, m_forward, m_playerState);

				//��]�����B
				m_playerAction.Rotate(m_rotation, m_forward, m_playerState);

				//�O�������X�V�B
				UpdateForward();

				//�A�N�V���������B
				m_playerAction.Action(m_playerState, m_isSelect);

				//���͂ɂ���ē����Ă���Ȃ�
				if (m_playerAction.IsMove()) {

					//���͂ɂ���ē����Ă��邱�Ƃ��A�j���[�V�����S���ɓ`����B
					m_playerAnimation.Move();
				}
			}

			//�A�j���[�V���������B
			m_playerAnimation.Update(*m_modelRender, m_playerState);

			//�N�[���^�C�����X�V�B
			m_playerAction.Update();

			//���W��ݒ�B
			m_modelRender->SetPosition(m_position);

			//��]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//���C�g�J�������X�V�B
			LightCameraUpdate();

			//�I����Ԃ������B
			m_isSelect = false;
		}

		void CPlayer::JudgeDamage(const CVector3& effectPos) {

			//�K�[�h�������A��e���A���񂾏�ԂȂ�I���B
			if (m_playerState == enState_GuardSuccess
				|| m_playerState == enState_Death
				|| m_playerState == enState_Damage
			) { return; }

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
			CVector3 m_lightCameraPos = m_lightCameraTar - *ligDirection * lightCameraDirection;

			//���C�g�J�����̏���ݒ�B
			CCamera::GetLightCamera()->SetPosition(m_lightCameraPos);
			CCamera::GetLightCamera()->SetTarget(m_lightCameraTar);
			CCamera::GetLightCamera()->SetFar(lightCameraFar);

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