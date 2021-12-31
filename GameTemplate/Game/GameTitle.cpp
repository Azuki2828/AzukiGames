#include "stdafx.h"
#include "GameTitle.h"
#include "Game.h"

namespace nsMyGame {

	bool CGameTitle::Start() {

		//�^�C�g���摜���������B
		m_titleSprite = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_titleSprite->Init(c_filePathTitleSprite, FRAME_BUFFER_W, FRAME_BUFFER_H);

		//�uNEW GAME�v�e�L�X�g�̏������B
		m_newGameSprite = NewGO<CSpriteRender>(enPriority_Second);
		m_newGameSprite->Init(c_filePathNewGameSprite, FRAME_BUFFER_W, FRAME_BUFFER_H);
		m_newGameSprite->SetScale({ 0.15f,0.15f,0.15f });
		m_newGameSprite->SetPosition({ 0.0f,-150.0f,0.0f });

		//�uNEW GAME�v�e�L�X�g�̏������B
		m_textBackSprite = NewGO<CSpriteRender>(enPriority_First);
		m_textBackSprite->Init(c_filePathTextBackSprite, FRAME_BUFFER_W, FRAME_BUFFER_H);
		m_textBackSprite->SetScale({ 0.4f,0.06f,0.15f });
		m_textBackSprite->SetPosition({ 0.0f,-150.0f,0.0f });

		//�Q�[������BGM���Đ��B
		CSoundManager::GetInstance()->Play(enBGM_GameMain);

		//�t�F�[�h�C��
		m_fade = FindGO<CFade>(c_classNameFade);
		m_fade->StartFadeIn();

		return true;
	}

	void CGameTitle::OnDestroy() {

		//�^�C�g���摜���폜�B
		DeleteGO(m_titleSprite);
		DeleteGO(m_newGameSprite);
		DeleteGO(m_textBackSprite);
	}

	void CGameTitle::Update() {

		//A�{�^���������ꂽ��
		if (g_pad[0]->IsTrigger(enButtonA)) {

			//�t�F�[�h�A�E�g���n�߂�B
			m_fade->StartFadeOut();

			m_finishedFadeOut = true;

			//�I��SE���Đ��B
			CSoundManager::GetInstance()->Play(enSE_Select);
		}

		//�t�F�[�h�A�E�g���I�������
		if (m_finishedFadeOut && !m_fade->IsFade()) {

			//�Q�[���V�[���Ɉڍs�B
			NewGO<CGameMain>(enPriority_Zeroth, c_classNameGameMain);

			//�^�C�g����ʂ��폜�B
			DeleteGO(this);
		}
	}
}