#pragma once
#include "../../MiniEngine/SpringCamera.h"
#include "../enemy/Enemy.h"
#include "CameraBase.h"

namespace nsMyGame {

	//���b�N�I���J�����N���X
	class CLockOnCamera : public CCameraBase
	{
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

		/**
		 * @brief �G�����b�N�I������֐��B
		*/
		const bool LockOnEnemy();

		/**
		 * @brief �J�������؂�ւ�����B
		*/
		void Switched()override final {

		}

		/**
		 * @brief �J�����̐؂�ւ����\���H
		 * @return �G�����m�ł����H
		*/
		const bool CanSwitch()override final {

			return LockOnEnemy();
		}
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
		CVector3 m_position = CVector3::Zero;		//���_
		CVector3 m_target = CVector3::Zero;			//�����_
		nsEnemy::CEnemy* m_lockOnEnemy = nullptr;	//���b�N�I���Ώۂ̓G
	};
}

