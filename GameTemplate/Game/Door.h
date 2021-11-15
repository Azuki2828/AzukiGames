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
	private:
		bool m_isLocked = false;							//�����������Ă���H
		CModelRender* m_modelRender = nullptr;				//���f��
		CVector3 m_position = CVector3::Zero;				//���W
		CQuaternion m_rotation = CQuaternion::Identity;		//��]
		CVector3 m_scale = CVector3::One;					//�g��
	};
}

