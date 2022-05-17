#include "stdafx.h"
#include "player/Player.h"
#include "enemy/firstWinEnemy/FirstWinEnemy.h"
#include "enemy/boss/Boss.h"
#include "Game.h"
#include "BackGround.h"
#include "camera/CameraManager.h"
#include "GameTitle.h"
#include "GameHUD.h"

namespace nsMyGame {

	bool CGameMain::Start() {

		//�v���C���[�𐶐��B
		m_player = NewGO<nsPlayer::CPlayer>(enPriority_Zeroth, c_classNamePlayer);

		//�w�i�N���X�𐶐��B
		m_backGround = NewGO<CBackGround>(enPriority_Zeroth, c_classNameBackGround);

		//���C���J�����𐶐��B
		m_cameraManager = NewGO<nsCamera::CCameraManager>(enPriority_Zeroth, c_classNameCameraManager);

		//HUD���쐬�B
		m_gameHUD = NewGO<CGameHUD>(enPriority_Zeroth, c_classNameGameHUD);

		//���S�X�v���C�g�𐶐��B
		m_youDiedSprite = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_youDiedSprite->Init(c_filePathYouDiedSprite, c_spriteYouDiedWH.x, c_spriteYouDiedWH.y);
		m_youDiedSprite->SetScale(c_spriteSizeYouDied);
		m_youDiedSprite->SetMulColor(c_translucentValue_Zero);

		//��\���ɐݒ�B
		m_youDiedSprite->Deactivate();

		//�Q�[���N���A�X�v���C�g�𐶐��B
		m_gameClearSprite = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_gameClearSprite->Init(c_filePathGameClearSprite, c_spriteYouDiedWH.x, c_spriteYouDiedWH.y);
		m_gameClearSprite->SetScale(c_spriteSizeYouDied);
		m_gameClearSprite->SetMulColor(c_translucentValue_Zero);

		//��\���ɐݒ�B
		m_gameClearSprite->Deactivate();

		//�t�F�[�h�C���B
		m_fade = FindGO<CFade>(c_classNameFade);
		m_fade->StartFadeIn();

		return true;
	}

	void CGameMain::OnDestroy() {

		//�e�N���X���폜�B
		DeleteGO(m_player);
		DeleteGO(m_youDiedSprite);
		DeleteGO(m_gameClearSprite);
		DeleteGO(m_backGround);
		DeleteGO(m_gameHUD);
		DeleteGO(m_cameraManager);
	}

	void CGameMain::Update() {

		//�v���C���[������ł���Ȃ�YouDied��\��������B
		if (m_player->IsDeath()) {

			//���S�X�v���C�g�p�̃^�C�}�[���X�V�B
			m_youDiedMessageTime += GameTime().GameTimeFunc().GetFrameDeltaTime();

			//��莞�Ԉȏォ�A���S�ɕ\������Ă��Ȃ��Ȃ�
			if (m_youDiedMessageTime >= 2.5f && m_youDiedSpriteTrans < 1.0f) {

				//�Q�[���I�[�o�[�T�E���h���Đ�����Ă��Ȃ��Ȃ�
				if (!m_gameOverSoundFlag) {

					//�Q�[���I�[�o�[�T�E���h���Đ��B
					CSoundManager::GetInstance()->Play(enSE_GameOver);

					//�Q�[���I�[�o�[�T�E���h���Đ����ꂽ�B
					m_gameOverSoundFlag = true;
				}
				
				//�L���ɂ���B
				m_youDiedSprite->Activate();

				//���񂾂�\�������悤�ɂ���B
				m_youDiedSpriteTrans += GameTime().GameTimeFunc().GetFrameDeltaTime() * 0.5f;
				m_youDiedSprite->SetMulColor({ CVector4::White.x,CVector4::White.y,CVector4::White.z, m_youDiedSpriteTrans });
			}
		}
		else if (g_pad[0]->IsTrigger(enButtonRB3)) {

			//���b�N�I����Ԃ���Ȃ��Ȃ�
			if (m_cameraManager->GetCameraType() != nsCamera::enCamera_LockOn
				&& m_cameraManager->CanSwitch(nsCamera::enCamera_LockOn)			//���G�̌����ɐ�������
				) {

				//���b�N�I����ԂɁB
				m_cameraManager->SetCameraType(nsCamera::enCamera_LockOn);
			}
			//���b�N�I����ԂȂ�
			else {
				//�ʏ�J�����ɁB
				m_cameraManager->SetCameraType(nsCamera::enCamera_Main);
			}
		}

		//�{�X��|������Q�[���N���A�摜��\��������B
		if (m_isGameClear) {

			//�L���ɂ���B
			m_gameClearSprite->Activate();

			//���S�X�v���C�g�p�̃^�C�}�[���X�V�B
			m_gameClearMessageTime += GameTime().GameTimeFunc().GetFrameDeltaTime();

			//���S�ɕ\������Ă��Ȃ��Ȃ�
			if (m_gameClearSpriteTrans < 1.0f) {

				//���񂾂�\�������悤�ɂ���B
				m_gameClearSpriteTrans += GameTime().GameTimeFunc().GetFrameDeltaTime() * 0.5f;
				m_gameClearSprite->SetMulColor({ CVector4::White.x,CVector4::White.y,CVector4::White.z, m_gameClearSpriteTrans });
			}
		}

		//�^�C�g���ɖ߂�B
		if (m_youDiedMessageTime > 7.0f || m_gameClearMessageTime > 4.5f) {

			if (!m_fade->IsFade()) {
				DeleteGO(this);
				NewGO<CGameTitle>(enPriority_Zeroth);

				CSoundManager::GetInstance()->Release(enBGM_Boss);
			}
		}
		//�t�F�[�h�A�E�g�B
		else if (m_youDiedMessageTime > 6.0f || m_gameClearMessageTime > 3.5f) {

			m_fade->StartFadeOut();
		}
	}
}