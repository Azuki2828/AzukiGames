#include "stdafx.h"
#include "GameHUD.h"
#include "player/Player.h"

namespace nsMyGame {

	bool CGameHUD::Start() {

		//HP�o�[���������B
		InitHPBar();

		//��HP�o�[�̌����̎d����ݒ�B
		m_hpDecreaseType = enType_Linear;

		return true;
	}

	void CGameHUD::OnDestroy() {

		DeleteGO(m_hpBarFrame);
		DeleteGO(m_hpBar_Green);
		DeleteGO(m_hpBar_Red);
		DeleteGO(m_hpBarBack);
		DeleteGO(m_bossHpBarFrame);
		DeleteGO(m_bossHpBarBack);
		DeleteGO(m_bossHpBar);
		DeleteGO(m_bossNameText);
	}

	void CGameHUD::Update() {

		//HP�o�[���X�V�B
		UpdateHPBar();
	}

	void CGameHUD::InitHPBar() {

		//HP�o�[�̃t���[�����쐬�B
		m_hpBarFrame = NewGO<CSpriteRender>(enPriority_Third);
		m_hpBarFrame->Init("Assets/Image/HP_BarFrame.dds", 400.0f, 25.0f);
		m_hpBarFrame->SetPosition({ -570.0f,300.0f,0.0f });
		m_hpBarFrame->SetPivot(CVector2::Zero);

		//HP�o�[�̔w�i���쐬�B
		m_hpBarBack = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_hpBarBack->Init("Assets/Image/HP_Back.dds", 400.0f, 25.0f);
		m_hpBarBack->SetPosition({ -570.0f,300.0f,0.0f });
		m_hpBarBack->SetPivot(CVector2::Zero);

		//��HP�o�[���쐬�B
		m_hpBar_Green = NewGO<CSpriteRender>(enPriority_Second);
		m_hpBar_Green->Init("Assets/Image/HP.dds", 400.0f, 25.0f);
		m_hpBar_Green->SetPosition({ -570.0f,300.0f,0.0f });
		m_hpBar_Green->SetPivot(CVector2::Zero);

		//��HP�o�[���쐬�B
		m_hpBar_Red = NewGO<CSpriteRender>(enPriority_First);
		m_hpBar_Red->Init("Assets/Image/HP_2.dds", 400.0f, 25.0f);
		m_hpBar_Red->SetPosition({ -570.0f,300.0f,0.0f });
		m_hpBar_Red->SetPivot(CVector2::Zero);

		//�{�X��HP�o�[�̃t���[�����쐬�B
		m_bossHpBarFrame = NewGO<CSpriteRender>(enPriority_Second);
		m_bossHpBarFrame->Init("Assets/Image/HP_BarFrame.dds", 400.0f, 25.0f);
		m_bossHpBarFrame->SetPosition({ -400.0f,-300.0f,0.0f });
		m_bossHpBarFrame->SetPivot(CVector2::Zero);
		m_bossHpBarFrame->Deactivate();
		
		//�{�X��HP�o�[�̔w�i���쐬�B
		m_bossHpBarBack = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_bossHpBarBack->Init("Assets/Image/HP_Back.dds", 400.0f, 25.0f);
		m_bossHpBarBack->SetPosition({ -400.0f,-300.0f,0.0f });
		m_bossHpBarBack->SetPivot(CVector2::Zero);
		m_bossHpBarBack->Deactivate();

		//�{�X��HP�o�[���쐬�B
		m_bossHpBar = NewGO<CSpriteRender>(enPriority_First);
		m_bossHpBar->Init("Assets/Image/HP_2.dds", 400.0f, 25.0f);
		m_bossHpBar->SetPosition({ -400.0f,-300.0f,0.0f });
		m_bossHpBar->SetPivot(CVector2::Zero);
		m_bossHpBar->Deactivate();

		m_bossNameText = NewGO<nsFont::CFontRender>(enPriority_Zeroth);
		m_bossNameText->Init(L"�����̖��");
		m_bossNameText->SetColor({ 0.8f,0.8f,0.8f,1.0f });
		m_bossNameText->SetScale(0.5f);
		m_bossNameText->SetPosition({ -400.0f,-250.0f });
		m_bossNameText->Deactivate();
	}

	void CGameHUD::UpdateHPBar() {

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

		//�v���C���[��HP���擾�B
		float playerHP = player->GetHP();

		//HP�Q�[�W���X�V�B
		m_hpBarScale.x = playerHP / static_cast<float>(nsPlayer::c_playerMaxHP);

		//�g�嗦��ݒ�B
		m_hpBar_Green->SetScale(m_hpBarScale);

		//��HP�o�[���X�V�B
		UpdateRedHPBar();
	}

	void CGameHUD::UpdateRedHPBar() {
		
		if (m_hpBar_Green->GetScale().x < m_hpBar_Red->GetScale().x) {

			//�^�C�}�[���X�V�B
			m_damageTimer += GameTime().GetFrameDeltaTime();

			//��莞�Ԃ��o�������HP�Q�[�W������悤�ɁB
			if (m_damageTimer > 2.0f) {

				//�X�V�ł���Ȃ�
				if (m_canHPBarScaleUpdate) {

					//��HP�Q�[�W�̌����̊g�嗦���X�V�B
					m_damageScale = m_hpBar_Red->GetScale().x - m_hpBar_Green->GetScale().x;
				}

				//����`�ɐݒ肵�Ă���Ȃ�
				if (m_hpDecreaseType == enType_NonLinear) {

					//����ȏ��HP�Q�[�W�̌����̊g�嗦�̍X�V�����Ȃ��悤�ɂ���B
					m_canHPBarScaleUpdate = false;
				}

				//��HP�o�[�̊g�嗦���X�V�B
				m_hpBar_Red->SetScale({ m_hpBar_Red->GetScale().x - m_damageScale / 20.0f,1.0f,1.0f });
			}

			//��HP�o�[�Ɨ�HP�o�[�̊g�嗦������Ȃ��߂��Ȃ�A�����ɐݒ肷��B
			if (m_hpBar_Red->GetScale().x - m_hpBar_Green->GetScale().x < 0.001f) {
				m_hpBar_Red->SetScale({ m_hpBar_Green->GetScale().x,1.0f,1.0f });
			}
		}
		//�������Ȃ��Ȃ�^�C�}�[�ƍX�V�t���O������������B
		else {
			m_damageTimer = 0.0f;
			m_canHPBarScaleUpdate = true;
		}
	}
}