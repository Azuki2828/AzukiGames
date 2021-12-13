#pragma once

namespace nsMyGame {

	//�^�C�g���N���X
	class CGameTitle : public CIGameObject
	{
		/**
		 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
		 * @return ���������H
		*/
		bool Start()override final;

		/**
		 * @brief �폜�֐��B
		*/
		void OnDestroy()override final;

		/**
		 * @brief �X�V�֐��B
		*/
		void Update()override final;
	private:
		CSpriteRender* m_titleSprite = nullptr;		//�^�C�g���摜
	};
}

