#include "stdafx.h"
#include "player/Player.h"
#include "enemy/firstWinEnemy/FirstWinEnemy.h"
#include "Game.h"
#include "BackGround.h"
#include "MainCamera.h"

namespace nsMyGame {

	bool CGameMain::Start() {

		//�v���C���[�𐶐��B
		m_player = NewGO<nsPlayer::CPlayer>(enPriority_Zeroth, c_classNamePlayer);

		//�w�i�N���X�𐶐��B
		m_backGround = NewGO<CBackGround>(enPriority_Zeroth, c_classNameBackGround);

		//���C���J�����𐶐��B
		m_mainCamera = NewGO<CMainCamera>(enPriority_Zeroth);

		//���S�X�v���C�g�𐶐��B
		m_youDiedSprite = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_youDiedSprite->Init(c_filePathYouDiedSprite, c_spriteYouDiedWH.x, c_spriteYouDiedWH.y);
		m_youDiedSprite->SetScale(c_spriteSizeYouDied);
		m_youDiedSprite->SetMulColor(c_translucentValue_Zero);

		//��\���ɐݒ�B
		m_youDiedSprite->Deactivate();

		// �Ƃ肠�����e�X�g�œG��ǉ��B
		auto fEnemy = NewGO<nsEnemy::CFirstWinEnemy>(enPriority_Zeroth, c_classNameEnemy);
		fEnemy->SetPosition({ 500.0f,500.0f,500.0f });

		//�t�F�[�h�C���B
		m_fade = FindGO<Fade>(c_classNameFade);
		m_fade->StartFadeIn();

		return true;
	}

	void CGameMain::OnDestroy() {

		//�e�N���X���폜�B
		DeleteGO(m_player);
		DeleteGO(m_youDiedSprite);
		DeleteGO(m_backGround);
		DeleteGO(m_mainCamera);
	}

	void CGameMain::Update() {

		//���S�X�v���C�g�p�̃^�C�}�[���������B
		static float youDiedMessageTime = 0.0f;

		//�v���C���[������ł���Ȃ�YouDied��\��������B
		if (m_player->IsDeath()) {

			//�L���ɂ���B
			m_youDiedSprite->Activate();

			//���S�X�v���C�g�p�̃^�C�}�[���X�V�B
			youDiedMessageTime += GameTime().GameTimeFunc().GetFrameDeltaTime();

			//��莞�Ԉȏォ�A���S�ɕ\������Ă��Ȃ��Ȃ�
			if (youDiedMessageTime >= 2.5f && m_youDiedSpriteTrans < 1.0f) {

				//���񂾂�\�������悤�ɂ���B
				m_youDiedSpriteTrans += GameTime().GameTimeFunc().GetFrameDeltaTime() * 0.5f;
				m_youDiedSprite->SetMulColor({ 1.0f, 1.0f, 1.0f, m_youDiedSpriteTrans });
			}
		}
		//����ł��Ȃ��Ȃ�
		else {

			//���S�X�v���C�g�p�̃^�C�}�[���������B
			youDiedMessageTime = 0.0f;
		}
	}
}