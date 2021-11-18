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

		static void CreateDirLight() {

			m_dirLight[0] = new nsLight::CDirectionLight;

			m_dirLight[0] = NewGO<nsLight::CDirectionLight>(enPriority_Zeroth);
			m_dirLight[0]->SetLigDirection({ 1.0f,-1.0f,-1.0f });
			m_dirLight[0]->SetLigColor({ 2.8f,2.8f,2.8f });

		
			m_dirLight[1] = new nsLight::CDirectionLight;

			m_dirLight[1] = NewGO<nsLight::CDirectionLight>(enPriority_Zeroth);
			m_dirLight[1]->SetLigDirection(g_camera3D->GetForward());
			m_dirLight[1]->SetLigColor({ 1.0f,1.0f,1.0f });
		}

		static nsLight::CDirectionLight* GetSunDirectionLight() {

			return m_dirLight[0];
		}
	private:
		CModelRender* m_modelRender = nullptr;			//���f��
		CModelRender* m_wall = nullptr;					//�ǃ��f��
		std::vector<CDoor*> m_door;						//�h�A�N���X�̃C���X�^���X
		std::vector<nsEnemy::CFirstWinEnemy*> m_fWEnemy;					//���K���̓G�̃C���X�^���X
		std::vector<nsEnemy::CGoteWinEnemy*> m_gWEnemy;						//���K���̓G�̃C���X�^���X
		std::vector<nsLight::CPointLight*> m_pointLight;					//�|�C���g���C�g�̃C���X�^���X
		static nsLight::CDirectionLight* m_dirLight[2];	//�f�B���N�V�������C�g
		CVector3 m_pos = CVector3::Zero;				//���W
		CQuaternion m_rot = CQuaternion::Identity;		//��]
		CVector3 m_sca = CVector3::One;					//�g��
		Level m_level;									//���x��
		PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g
	};
}

