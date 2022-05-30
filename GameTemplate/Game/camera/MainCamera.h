#pragma once
#include "../../MiniEngine/SpringCamera.h"
#include "CameraBase.h"

namespace nsMyGame {

	//�G�C���A�X�錾
	namespace nsPlayer {

		class CPlayer;
	}

	namespace nsCamera {

		//���C���J�����N���X
		class CMainCamera : public CCameraBase
		{
			
		private:
			/**
			 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
			 * @return ���������H
			*/
			bool StartSub()override final;

			/**
			 * @brief �X�V�֐��B
			*/
			void UpdateSub()override final;

			void SubSwitched()override final {

			}
		private:
			float m_eventTimer = 0.0f;							//�C�x���g�^�C�}�[(�{�X�o�ꎞ�̃J�������[�N)
			SpringCamera m_springCamera;						//�΂˃J�����B

			CVector3 m_tar = CVector3::Zero;					//�����_

			//�e�N���X�̃|�C���^�ϐ�
			nsPlayer::CPlayer* m_player = nullptr;
		};
	}
}

