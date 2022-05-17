#include "stdafx.h"
#include <random>
#include "MainCamera.h"
#include "../player/Player.h"
#include "constCamera.h"

namespace nsMyGame {

	namespace nsCamera {

		namespace {

			constexpr float c_mainCameraVelocityMax = 2500.0f;	//�ړ����x�̍ő�l
			constexpr float c_mulCameraPosition = 20.0f;			//�J�����̍��W�����߂�l
			constexpr float c_mainCameraDampingRate = 0.8f;			//�΂˃J�����̌����̎d��
			constexpr float c_mainCameraRotationSpeed = 4.0f;		//�J�����̉�]���x
			constexpr float c_mainCameraDirectionUp = -0.5f;		//�J�������ǂꂭ�炢��������邩
			constexpr float c_mainCameraDirectionDown = 0.8f;		//�J�������ǂꂭ�炢���������邩
		}

		bool CMainCamera::StartSub() {

			//�J�����̉��Z���W���������B
			m_cameraToPlayerVec = c_defaultCameraVec;

			//�p�����[�^���������B
			g_camera3D->SetPosition(m_position);
			g_camera3D->SetTarget(m_target);
			g_camera3D->SetFar(c_cameraFar);

			//�΂˃J�����̏������B
			m_springCamera.Init(
				*g_camera3D,				//�΂˃J�����̏������s���J�������w�肷��B
				c_mainCameraVelocityMax,	//�J�����̈ړ����x�̍ő�l�B
				true,						//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
				c_cameraCollisionRadius		//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
			);
			m_springCamera.SetDampingRate(c_mainCameraDampingRate);
			return true;
		}

		void CMainCamera::UpdateSub() {

			m_player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);
			//�J�������X�V�B
			//�����_���v�Z����B
			m_target = m_player->GetPosition();
			//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
			m_target.y += c_addCameraTarget;
			m_target += g_camera3D->GetForward() * c_mulCameraPosition;

			CVector3 toCameraPosOld = m_cameraToPlayerVec;
			//�p�b�h�̓��͂��g���ăJ�������񂷁B
			float x = g_pad[0]->GetRStickXF();
			float y = g_pad[0]->GetRStickYF();
			//Y������̉�]
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3::AxisY, c_mainCameraRotationSpeed * x);
			qRot.Apply(m_cameraToPlayerVec);
			//X������̉�]�B
			CVector3 axisX;
			axisX.Cross(CVector3::AxisY, m_cameraToPlayerVec);
			axisX.Normalize();
			qRot.SetRotationDeg(axisX, c_mainCameraRotationSpeed * y);
			qRot.Apply(m_cameraToPlayerVec);

			//�J�����̉�]�̏�����`�F�b�N����B
			//�����_���王�_�܂ł̃x�N�g���𐳋K������B
			//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
			//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
			CVector3 toPosDir = m_cameraToPlayerVec;
			toPosDir.Normalize();
			if (toPosDir.y < c_mainCameraDirectionUp) {
				//�J����������������B
				m_cameraToPlayerVec = toCameraPosOld;
			}
			else if (toPosDir.y > c_mainCameraDirectionDown) {
				//�J�����������������B
				m_cameraToPlayerVec = toCameraPosOld;
			}


			CVector3 shakeTarget = CVector3::Zero;

			//�J�������h���ԂȂ�^�[�Q�b�g��h�炷�B
			if (m_state == enShake) {

				std::random_device seed_gen;
				std::mt19937 random(seed_gen());


				shakeTarget = { static_cast<float>(random() % 201) - 100.0f,static_cast<float>(random() % 201) - 100.0f ,static_cast<float>(random() % 201) - 100.0f };
			}

			//���_���v�Z����B
			m_position = m_target + m_cameraToPlayerVec;

			//�o�l�J�����ɒ����_�Ǝ��_��ݒ肷��B
			m_springCamera.SetPosition(m_position + shakeTarget);
			m_springCamera.SetTarget(m_target + shakeTarget);
			m_springCamera.Update();
		}
	}
}