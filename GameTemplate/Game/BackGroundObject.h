#pragma once

namespace nsMyGame {

	class CBackGroundObject : public CIGameObject
	{
	private:
		/**
		 * @brief �J�n���ɌĂ΂��֐��B
		 * @return ���������H
		*/
		//bool Start()override final;
		/**
		 * @brief �X�V�֐��B
		*/
		//void Update()override final;
	public:
		/**
		 * @brief �������֐��B
		 * @param fileName �t�@�C���p�X
		 * @param position ���W
		 * @param rotation ��]
		 * @param scale �g��
		 * @param isCollision �����蔻������H
		*/
		void InitModel(const char* fileName,
			const CVector3& position,
			const CQuaternion& rotation,
			const CVector3& scale, 
			const bool isCollision = true
		);

		/**
		 * @brief ���f���𖳎�����H
		*/
		void IgnoreObj() {

			m_isIgnoreObject = true;
		}

	private:
		bool m_isIgnoreObject = false;				//���f���𖳎�����H
		CModelRender* m_modelRender = nullptr;		//���f��
		PhysicsStaticObject m_physicsStaticObject;	//�R���W����
	};
}

