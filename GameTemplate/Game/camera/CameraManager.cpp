#include "stdafx.h"
#include "CameraManager.h"

namespace nsMyGame {

	namespace nsCamera {

		bool CCameraManager::Start() {

			//�J�����𐶐��B
			CreateCamera();

			return true;
		}

		void CCameraManager::CreateCamera() {

			//�K�v�ȃJ�������|�C���^�Ɋi�[�B
			m_camera[enCamera_Main] = &m_mainCamera;
			m_camera[enCamera_LockOn] = &m_lockOnCamera;

			//���ꂼ��̃J������Start()�֐����Ăяo���B
			for (const auto& camera : m_camera) {

				camera->Start();
			}
		}
	}
}