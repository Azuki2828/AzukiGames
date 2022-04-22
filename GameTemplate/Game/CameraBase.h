#pragma once
namespace nsMyGame {

	//�J�����N���X
	class CCameraBase
	{
	public:
		/**
		 * @brief �������֐��B
		 * @return ���������H
		*/
		bool Start() {

			return StartSub();
		}
		
		/**
		 * @brief �X�V�֐��B
		*/
		void Update() {

			UpdateSub();

			//�؂�ւ���ĂP�t���[���������B
			if (m_switched) { m_switched = false; }
		}

		/**
		 * @brief ���_�̍��W���擾����֐��B
		 * @return ���_�̍��W
		*/
		const CVector3& GetPosition()const {

			return m_position;
		}

		/**
		 * @brief �����_�̍��W���擾����֐��B
		 * @return �����_�̍��W
		*/
		const CVector3& GetTarget()const {

			return m_target;
		}

		/**
		 * @brief �J������؂�ւ������Ƃ�m�点��֐��B
		*/
		void Switched() {

			m_switched = true;
		}

		/**
		 * @brief ���b�N�I�����̓G�̍��W���擾����֐��B
		 * @return ���b�N�I�����̓G�̍��W
		*/
		virtual const CVector3& GetLockOnEnemyPosition()const {

			MessageBoxA(nullptr, "��������񂪌Ăяo����Ă��܂���B", "�G���[", MB_OK);
			return CVector3::Zero;
		}
	protected:
		/**
		 * @brief �h���N���X��Start()�֐��B
		 * @return ���������H
		*/
		virtual bool StartSub() = 0;

		/**
		 * @brief �h���N���X��Update()�֐��B
		*/
		virtual void UpdateSub() = 0;
	protected:
		CVector3 m_position;		//���_
		CVector3 m_target;			//�����_
		bool m_switched = false;	//�J�������؂�ւ�����H
	};
}

