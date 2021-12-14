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
		bool m_finishedFadeOut = false;				//�t�F�[�h�A�E�g���I������H
		CSpriteRender* m_titleSprite = nullptr;		//�^�C�g���摜
		CSpriteRender* m_newGameSprite = nullptr;	//�uNEW GAME�v�e�L�X�g
		CSpriteRender* m_textBackSprite = nullptr;	//�e�L�X�g�̌��ɔz�u����摜
		CFade* m_fade = nullptr;					//�t�F�[�h
	};
}

