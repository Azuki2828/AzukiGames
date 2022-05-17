#pragma once

namespace nsMyGame {

	//�G�C���A�X�錾
	class CBackGround;
	class CGameHUD;
	namespace nsCamera {

		class CCameraManager;
	}

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
	public:
		/**
		 * @brief �Q�[���N���A�ɂ���֐��B
		*/
		void GameClear() {

			m_isGameClear = true;
		}
	private:
		bool m_isGameClear = false;					//�Q�[���N���A�H
		bool m_gameOverSoundFlag = false;			//�Q�[���I�[�o�[�T�E���h���Đ����ꂽ�H
		float m_youDiedSpriteTrans = 0.0f;			//���S�X�v���C�g�̓����x
		float m_youDiedMessageTime = 0.0f;			//�Q�[���I�[�o�[�X�v���C�g���ł�܂ł̎���
		float m_gameClearSpriteTrans = 0.0f;		//�Q�[���N���A�X�v���C�g�̓����x
		float m_gameClearMessageTime = 0.0f;		//�Q�[���N���A�X�v���C�g���ł�܂ł̎���

		//�e�N���X�̃|�C���^�ϐ�
		nsPlayer::CPlayer* m_player = nullptr;
		CSpriteRender* m_youDiedSprite = nullptr;
		CSpriteRender* m_gameClearSprite = nullptr;
		CBackGround* m_backGround = nullptr;
		CGameHUD* m_gameHUD = nullptr;
		nsCamera::CCameraManager* m_cameraManager = nullptr;
		CFade* m_fade = nullptr;
	};
}

