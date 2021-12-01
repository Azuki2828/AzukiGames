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
		 * @brief ���W���擾����֐��B
		 * @return ���W
		*/
		const CVector3& GetPosition()const {

			return m_position;
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

		/**
		 * @brief �����̃I�u�W�F�N�g�H
		 * @return �����̃I�u�W�F�N�g���ǂ���
		*/
	    void SetObj(const bool objFlag) {

			m_isObj = objFlag;
		}

		/**
		 * @brief �h�A���J���Ă���H
		 * @return �h�A���J���Ă��邩�ǂ����̃t���O
		*/
		const bool IsOpened()const {

			return m_isOpened;
		}

		/**
		 * @brief �I����Ԃ�ύX����֐��B
		 * @param SelectFlg �I����Ԃ��ǂ����̃t���O
		*/
		void SetSelectFlag(bool SelectFlg)override  {

			m_isSelected = SelectFlg;
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
		 * @brief �h�A���J����ꂽ��J���鏈�����s���֐��B
		 * @param rotNum �h�A����]�����邽�߂̉�
		*/
		void JudgeAndExecuteOpenDoor(unsigned int& rotNum);

		/**
		 * @brief �h�A�̉�]���X�V����֐��B
		 * @param rotNum �h�A����]�����邽�߂̉�
		 * @param rotValue �h�A�̉�]�̒l
		*/
		void UpdateRotation(unsigned int& rotNum);

		/**
		 * @brief �I����ԁH
		 * @return �I����Ԃ��ǂ����̃t���O
		*/
		const bool IsSelected() {

			return m_isSelected;
		}
	private:
		bool m_isLocked = false;							//�����������Ă���H
		bool m_isOpened = false;							//�J���Ă���H
		bool m_isObj = false;								//�����̃I�u�W�F�N�g�H
		bool m_isSelected = false;							//�I����ԁH

		unsigned int m_doorRotNum = 0;						//�h�A����]�����邽�߂̉�
		float m_doorRotValue = 0.0f;						//�h�A�̉�]�̒l

		CModelRender* m_modelRender = nullptr;				//���f��
		PhysicsStaticObject m_physicsStaticObject;			//�����I�u�W�F�N�g
		CVector3 m_position = CVector3::Zero;				//���W
		CQuaternion m_rotation = CQuaternion::Identity;		//��]
		CVector3 m_scale = CVector3::One;					//�g��
	};
}

