#include "stdafx.h"
#include "AppearSprite.h"
#include "player/Player.h"

namespace nsMyGame {

	bool CAppearSprite::Start() {

		//�e�L�X�g�̃X�v���C�g���������B
		m_textSprite = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_textSprite->Init(c_filePathTextSprite, c_textSpriteWH.x, c_textSpriteWH.y);
		m_textSprite->SetPosition(c_textSpritePosition);
		m_textSprite->SetScale(c_textSpriteSize);

		//��\���ɐݒ�B
		m_textSprite->Deactivate();

		//�e�L�X�g���������B
		m_font = NewGO<nsFont::CFontRender>(enPriority_Zeroth);
		m_font->Init(m_text);
		m_font->SetPosition(m_textPosition);
		m_font->SetScale(c_textSize);
		m_font->SetColor(CVector4::White);

		//��\���ɐݒ�B
		m_font->Deactivate();

		return true;
	}

	void CAppearSprite::Update() {

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

		//�v���C���[��I����Ԃɐݒ�B
		player->SetSelectFlag(true);

		//A�{�^�������͂��ꂽ��m�F�t���O��true�ɂ���B
		if (g_pad[0]->IsTrigger(enButtonA)) {

			m_isPressButton = true;
		}

		//�m�F�{�^�������͂���Ă��Ȃ��Ȃ�
		if (!IsPressButton()) {

			//�X�v���C�g�ƃe�L�X�g�����X�ɏo��������B
			AppearSpriteAndText();
		}
		//�m�F�{�^�������͂��ꂽ��
		else {

			//���񂾂�X�v���C�g��������悤�ɂ���B
			DisappearSpriteAndText();

			//���S�ɏ������玩�g���폜�B
			if (m_textSpriteTranslucent == 0.0f) {
				DeleteGO(this);
				DeleteGO(m_textSprite);
				DeleteGO(m_font);
			}
		}
	}

	void CAppearSprite::AppearSpriteAndText() {

		//�X�v���C�g�ƃe�L�X�g��\���B
		m_textSprite->Activate();
		m_font->Activate();

		//���񂾂�X�v���C�g�������悤�ɂ���B
		if (m_textSpriteTranslucent < 1.0f) {

			//�e�L�X�g�J���[��ݒ�B
			float textColor = m_textSpriteTranslucent;
			m_font->SetColor({ textColor ,textColor ,textColor,m_textSpriteTranslucent });

			//�X�v���C�g�̓����x��ݒ�B
			m_textSpriteTranslucent += GameTime().GameTimeFunc().GetFrameDeltaTime() * 5.0f;
			m_textSprite->SetMulColor({ 1.0f,1.0f,1.0f, m_textSpriteTranslucent });
		}
	}

	void CAppearSprite::DisappearSpriteAndText() {

		if (m_textSpriteTranslucent > 0.0f) {

			//�e�L�X�g�J���[��ݒ�B
			float textColor = m_textSpriteTranslucent;
			m_font->SetColor({ textColor,textColor,textColor,m_textSpriteTranslucent });

			//�X�v���C�g�̓����x��ݒ�B
			m_textSpriteTranslucent -= GameTime().GameTimeFunc().GetFrameDeltaTime() * 5.0f;
			m_textSprite->SetMulColor({ 1.0f,1.0f,1.0f, m_textSpriteTranslucent });
		}
		//�J���X�v���C�g���\���B
		//�e�L�X�g���\���B
		else {
			m_textSpriteTranslucent = 0.0f;
			m_textSprite->Deactivate();
			m_font->Deactivate();
		}
	}
}