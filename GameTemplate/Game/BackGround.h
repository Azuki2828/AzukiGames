#pragma once
#include "Door.h"
#include "enemy/firstWinEnemy/FirstWinEnemy.h"
#include "enemy/goteWinEnemy/GoteWinEnemy.h"

namespace nsMyGame {

	class CBackGround : public CIGameObject
	{
	public:
		/**
		 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
		 * @return ���������H
		*/
		bool Start()override final;

		/**
		 * @brief �X�V�֐��B
		*/
		void Update()override final;

	private:
		CModelRender* m_modelRender = nullptr;			//���f��
		CModelRender* m_wall = nullptr;					//�ǃ��f��
		std::vector<CDoor*> m_door;						//�h�A�N���X�̃C���X�^���X
		std::vector<nsEnemy::CFirstWinEnemy*> m_fWEnemy;					//���K���̓G�̃C���X�^���X
		std::vector<nsEnemy::CGoteWinEnemy*> m_gWEnemy;						//���K���̓G�̃C���X�^���X

		CVector3 m_pos = CVector3::Zero;				//���W
		CQuaternion m_rot = CQuaternion::Identity;		//��]
		CVector3 m_sca = CVector3::One;					//�g��
		Level m_level;									//���x��
		PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g
	};
}

