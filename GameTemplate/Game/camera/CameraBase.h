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
		 * @brief �J������؂�ւ����Ƃ��ɌĂяo�����֐��B
		*/
		virtual void Switched() = 0;

		/**
		 * @brief �e�J�����̉���֐��B
		*/
		virtual void Release(){}

		/**
		 * @brief �J�����̐؂�ւ����\���H
		 * @return ���������H
		*/
		virtual const bool CanSwitch() {

			return true;
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
	};
}

