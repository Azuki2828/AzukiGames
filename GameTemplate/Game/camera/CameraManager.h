#pragma once
#include "MainCamera.h"
#include "LockOnCamera.h"

namespace nsMyGame {

	namespace nsCamera {

		//�J�����̎��
		enum EnCameraType {
			enCamera_Main,			//�ʏ�J����
			enCamera_LockOn,		//���b�N�I���J����

			enCamera_Num			//�J�����̐�
		};

		//�J�����Ǘ��N���X
		class CCameraManager : public CIGameObject
		{
		private:
			/**
			 * @brief �������֐��B
			 * @return ���������H
			*/
			bool Start()override final;

			/**
			 * @brief �폜�֐��B
			*/
			void OnDestroy()override final {

				//�J����������B
				Release();
			}

			/**
			 * @brief �X�V�֐��B
			*/
			void Update()override final {

				//���݂̃J�����������ɂȂ����烁�C���J�����ɖ߂��B
				if (!m_camera[m_cameraType]->IsEnable()) {

					SetCameraType(enCamera_Main);
				}

				//�J�������X�V�B
				m_camera[m_cameraType]->Update();
			}

			/**
			 * @brief �J�����𐶐�����֐��B
			*/
			void CreateCamera();
		public:

			/**
			 * @brief ����֐��B
			*/
			void Release() {

				//�e�J�����̉�����s���B
				for (const auto& camera : m_camera) {

					camera->Release();
				}
			}

			/**
			 * @brief �J�����̎��_�̍��W���擾����֐��B
			 * @return �J�����̎��_�̍��W
			*/
			const CVector3& GetPosition()const {

				return m_camera[m_cameraType]->GetPosition();
			}

			/**
			 * @brief �J�����̒����_�̍��W���擾����֐��B
			 * @return �J�����̒����_�̍��W
			*/
			const CVector3& GetTarget()const {

				return m_camera[m_cameraType]->GetTarget();
			}

			/**
			 * @brief �؂�ւ��\���H
			 * @return ���������H
			*/
			const bool CanSwitch(EnCameraType cameraType) {

				return m_camera[cameraType]->CanSwitch();
			}

			/**
			 * @brief �J�����̎�ނ�ݒ肷��֐��B
			 * @param cameraType �J�����̎��
			*/
			void SetCameraType(EnCameraType cameraType) {

				//��ɂ��ׂẴJ����������B
				for (const auto& camera : m_camera) { camera->Release(); }

				//�J�����^�C�v��ݒ�B
				m_cameraType = cameraType;

				//�J�������؂�ւ�������Ƃ�m�点��B
				m_camera[m_cameraType]->Switched();
			}

			/**
			 * @brief �J�����̎�ނ���Z����֐��B
			 * @return �J�����̎��
			*/
			const EnCameraType GetCameraType()const {

				return m_cameraType;
			}

			/**
			 * @brief ���b�N�I�����̓G�̍��W���擾����֐��B
			 * @return ���b�N�I�����̓G�̍��W
			*/
			const CVector3& GetLockOnEnemyPosition() {

				return m_lockOnCamera.GetLockOnEnemyPosition();
			}
		private:
			EnCameraType m_cameraType = enCamera_Main;				//�J�����̎��
			CCameraBase* m_camera[enCamera_Num] = { nullptr };		//�J�����̃|�C���^�z��

			CMainCamera m_mainCamera;								//���C���J����
			CLockOnCamera m_lockOnCamera;							//���b�N�I���J����
		};
	}
}

