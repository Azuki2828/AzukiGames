#include "stdafx.h"
#include "Player.h"
#include "../enemy/Enemy.h"

namespace nsMyGame {

	namespace nsPlayer {

		bool CPlayer::Start() {

			m_position = { 0.0f,200.0f,0.0f };

			m_status.hp = 100;
			m_status.attack = 10;

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


		void CPlayer::Update() {

			//�ړ������B
			m_playerAction.Move(m_position, m_forward, m_playerState);

			//��]�����B
			m_playerAction.Rotate(m_rotation);

			//�O�������X�V�B
			UpdateForward();

			//�A�N�V���������B
			m_playerAction.Action(m_playerState, m_isSelect);

			//�A�j���[�V���������B
			m_playerAnimation.Update(*m_modelRender, m_playerState);

			//��Ԃ��X�V�B
			m_playerAction.Update(m_position, m_rotation, m_forward, m_playerState);

			//���W��ݒ�B
			m_modelRender->SetPosition(m_position);

			//��]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//���C�g�J�������X�V�B
			LightCameraUpdate();
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

			//���C�g�J�����̏����X�V�B
			CVector3 m_lightCameraTar = m_position;
			CVector3 m_lightCameraPos = m_lightCameraTar;

			//���C�g�J�����̍��W��ݒ�B
			m_lightCameraPos += c_addLightCameraPos;

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

			CCamera::GetLightCamera()->SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
		}
	}
}