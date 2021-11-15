#pragma once

namespace nsMyGame {

	//�h�A�N���X
	class CDoor : public CIGameObject
	{
	public:
		/**
		 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
		 * @return ���������H
		*/
		bool Start() override final;

		/**
		 * @brief �X�V�֐��B
		*/
		void Update()override final;

		/**
		 * @brief ���W��ݒ肷��֐��B
		 * @param pos ���W
		*/
		void SetPosition(const CVector3& pos) {

			m_position = pos;
		}

		/**
		 * @brief ��]��ݒ肷��֐��B
		 * @param rot ��]
		*/
		void SetRotation(const CQuaternion& rot) {

			m_rotation = rot;
		}

		/**
		 * @brief �g���ݒ肷��֐��B
		 * @param scale �g��
		*/
		void SetScale(const CVector3& scale) {

			m_scale = scale;
		}

	private:
		/**
		 * @brief �����������Ă���H
		 * @return �����������Ă��邩�ǂ����̃t���O
		*/
		const bool IsLocked()const {

			return m_isLocked;
		}

		/**
		 * @brief �h�A���J���Ă���H
		 * @return �h�A���J���Ă��邩�ǂ����̃t���O
		*/
		const bool IsOpened()const {

			return m_isOpened;
		}

		/**
		 * @brief �h�A���J����ꂽ��J���鏈�����s���֐��B
		 * @param rotNum �h�A����]�����邽�߂̉�
		*/
		void JudgeAndExecuteOpenDoor(unsigned int& rotNum);

		/**
		 * @brief �h�A�̉�]���X�V����֐��B
		 * @param rotNum �h�A����]�����邽�߂̉�
		 * @param rotValue �h�A�̉�]�̒l
		*/
		void UpdateRotation(unsigned int& rotNum, float& rotValue);
	private:
		bool m_isLocked = false;							//�����������Ă���H
		bool m_isOpened = false;							//�J���Ă���H
		CModelRender* m_modelRender = nullptr;				//���f��
		PhysicsStaticObject m_physicsStaticObject;			//�����I�u�W�F�N�g
		CVector3 m_position = CVector3::Zero;				//���W
		CQuaternion m_rotation = CQuaternion::Identity;		//��]
		CVector3 m_scale = CVector3::One;					//�g��
	};
}

