#pragma once
#include "../../MiniEngine/SpringCamera.h"
#include "../enemy/Enemy.h"
#include "CameraBase.h"
#include "LockOnMarker.h"

namespace nsMyGame {

	namespace nsCamera {

		//���b�N�I���J�����N���X
		class CLockOnCamera : public CCameraBase
		{
			//�E�X�e�B�b�N�̓��͏��
			enum R3ButtonInput {

				No_Input,		//���͂Ȃ�
				Input_Right,	//�E
				Input_Left		//��
			};
		private:
			/**
			 * @brief �������֐��B
			 * @return ���������H
			*/
			bool StartSub()override;

			/**
			 * @brief �X�V�֐��B
			*/
			void UpdateSub()override;

			void SubRelease()override final {

				//���b�N�I���A�C�R�����폜�B
				m_lockOnMarker.Release();
			}

			/**
			 * @brief �G�����b�N�I������֐��B
			*/
			const bool LockOnEnemy(R3ButtonInput r3Input = No_Input);

			/**
			 * @brief �J�������؂�ւ�����B
			*/
			void SubSwitched()override final {

				//���b�N�I���A�C�R�����������B
				m_lockOnMarker.Init();

				//�J�����̃x�N�g�����������B
				InitCameraToPlayerVec();
			}

			/**
			 * @brief �J�����̃x�N�g��������������֐��B
			*/
			void InitCameraToPlayerVec();

			/**
			 * @brief �X�V�֐��B
			*/
			void UpdateLockOnCamera();

			/**
			 * @brief ���b�N�I���A�C�R���̍X�V�֐��B
			*/
			void UpdateLockOnMarker();

			/**
			 * @brief �J�����̐؂�ւ����\���H
			 * @return �G�����m�ł����H
			*/
			const bool CanSwitch()override final {

				return LockOnEnemy();
			}

			/**
			 * @brief ���b�N�I���Ώۂ�؂�ւ���֐��B
			*/
			void ChangeLockOnEnemy();

			/**
			 * @brief �E�X�e�B�b�N�����͂���Ă��邩���ׂ�֐��B
			 * @return �E�X�e�B�b�N�����͂���Ă���H
			*/
			const bool CheckR3Input();
		public:
			/**
			 * @brief ���b�N�I�����̓G�̍��W���擾����֐��B
			 * @return ���b�N�I�����̓G�̍��W
			*/
			const CVector3& GetLockOnEnemyPosition()const {

				return m_lockOnEnemy->GetPosition();
			}
		private:
			SpringCamera m_springCamera;				//�΂˃J����
			nsEnemy::CEnemy* m_lockOnEnemy = nullptr;	//���b�N�I���Ώۂ̓G
			CLockOnMarker m_lockOnMarker;				//���b�N�I���A�C�R��
			bool m_isR3XInput = false;					//�E�X�e�B�b�N���͂���Ă���H
			R3ButtonInput m_r3Input = No_Input;			//�E�X�e�B�b�N�̓��͏��
		};
	}
}

