#pragma once

namespace nsMyGame {

	//�G�C���A�X�錾
	class CBackGround;
	class CMainCamera;

	namespace nsPlayer {

		class CPlayer;
	}

	//�Q�[�����C���N���X
	class CGameMain : public CIGameObject
	{
	private:
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
		float m_youDiedSpriteTrans = 0.0f;			//���S�X�v���C�g�̓����x

		//�e�N���X�̃|�C���^�ϐ�
		nsPlayer::CPlayer* m_player = nullptr;
		CSpriteRender* m_youDiedSprite = nullptr;
		CBackGround* m_backGround = nullptr;
		CMainCamera* m_mainCamera = nullptr;
		Fade* m_fade = nullptr;
	};
}

