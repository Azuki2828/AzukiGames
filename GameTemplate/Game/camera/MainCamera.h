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
			//�X�e�[�g
			enum EnState {
				enNormal,		//�ʏ�
				enShake			//�h����
			};
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
		public:
			/**
			 * @brief �J������h���Ԃɂ���֐��B
			*/
			void ShakeCamera() {

				m_state = enShake;
			}

			/**
			 * @brief �J�����̏�Ԃ�ʏ��Ԃɂ���֐��B
			*/
			void SetNormalCamera() {

				m_state = enNormal;
			}
		private:
			EnState m_state = enNormal;							//�X�e�[�g
			float m_eventTimer = 0.0f;							//�C�x���g�^�C�}�[(�{�X�o�ꎞ�̃J�������[�N)
			SpringCamera m_springCamera;						//�΂˃J�����B

			CVector3 m_tar = CVector3::Zero;					//�����_

			//�e�N���X�̃|�C���^�ϐ�
			nsPlayer::CPlayer* m_player = nullptr;
		};
	}
}

