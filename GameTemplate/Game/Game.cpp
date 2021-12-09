#include "stdafx.h"
#include "player/Player.h"
#include "enemy/firstWinEnemy/FirstWinEnemy.h"
#include "Game.h"
#include "BackGround.h"
#include "MainCamera.h"

namespace nsMyGame {

	bool CGameMain::Start() {

		//�v���C���[�𐶐��B
		m_player = NewGO<nsPlayer::CPlayer>(0, c_classNamePlayer);

		//�w�i�N���X�𐶐��B
		m_backGround = NewGO<CBackGround>(0, c_classNameBackGround);

		//���C���J�����𐶐��B
		m_mainCamera = NewGO<CMainCamera>(0);

		m_youDiedSprite = NewGO<CSpriteRender>(0);
		m_youDiedSprite->Init("Assets/image/youDied2.dds", 1740.0f, 180.0f);
		m_youDiedSprite->SetPosition({ 0.0f,0.0f,0.0f });
		m_youDiedSprite->SetScale({ 0.8f,0.8f,0.8f });
		m_youDiedSprite->SetMulColor({ 1.0f,1.0f,1.0f,m_youDiedSpriteTrans });

		//��\���ɐݒ�B
		m_youDiedSprite->Deactivate();

		// �Ƃ肠�����e�X�g�œG��ǉ��B
		auto fEnemy = NewGO<nsEnemy::CFirstWinEnemy>(0, c_classNameEnemy);
		fEnemy->SetPosition({ 500.0f,500.0f,500.0f });

		return true;
	}

	void CGameMain::OnDestroy() {

		DeleteGO(m_player);
		DeleteGO(m_youDiedSprite);
		DeleteGO(m_backGround);
		DeleteGO(m_mainCamera);
	}

	void CGameMain::Update() {

		//�v���C���[������ł���Ȃ�YouDied��\��������B
		if (m_player->IsDeath()) {

			//�L���ɂ���B
			m_youDiedSprite->Activate();

			static float youDiedMessageTime = 0.0f;

			youDiedMessageTime += GameTime().GameTimeFunc().GetFrameDeltaTime();

			if (youDiedMessageTime >= 3.0f && m_youDiedSpriteTrans < 1.0f) {

				m_youDiedSpriteTrans += 0.01f;
				m_youDiedSprite->SetMulColor({ 1.0f, 1.0f, 1.0f, m_youDiedSpriteTrans });
			}
		}
	}
}