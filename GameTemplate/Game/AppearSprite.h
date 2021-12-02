#pragma once

namespace nsMyGame {

	//�X�v���C�g�o���N���X
	//�A�C�e���擾���A�h�A�̃��b�N���莞�ȂǁA��莞�Ԃŏ�����X�v���C�g�������N���X
	class CAppearSprite : public CIGameObject
	{
		/**
		 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
		 * @return ���������H
		*/
		bool Start()override final;

		/**
		 * @brief �X�V�֐��B
		*/
		void Update()override final;
	public:

		/**
		 * @brief �e�L�X�g��ݒ肷��֐��B
		 * @param text �e�L�X�g
		*/
		void SetText(const wchar_t* text) {

			m_text = text;
		}

		/**
		 * @brief �e�L�X�g�̍��W��ݒ肷��֐��B
		 * @param textPos ���W
		*/
		void SetTextPosition(const CVector2& textPos) {

			m_textPosition = textPos;
		}
	private:
		/**
		 * @brief �X�v���C�g�ƃe�L�X�g��\������֐��B
		*/
		void AppearSpriteAndText();

		/**
		 * @brief �X�v���C�g�ƃe�L�X�g���\���ɂ���֐��B
		*/
		void DisappearSpriteAndText();

		/**
		 * @brief �m�F�{�^�������͂��ꂽ�H
		 * @return ���͂��ꂽ���ǂ����̃t���O
		*/
		const bool IsPressButton()const {

			return m_isPressButton;
		}
	private:
		const wchar_t* m_text = nullptr;			//�e�L�X�g
		CVector2 m_textPosition = CVector2::Zero;	//�e�L�X�g�̍��W
		bool m_isPressButton = false;				//�m�F�{�^�������͂��ꂽ�H
		float m_textSpriteTranslucent = 0.0f;		//�X�v���C�g�̓����x
		CSpriteRender* m_textSprite = nullptr;		//�X�v���C�g
		nsFont::CFontRender* m_font = nullptr;		//�e�L�X�g�̐ݒ�
	};
}

