#include "stdafx.h"
#include "GameHUD.h"
#include "player/Player.h"

namespace nsMyGame {

	bool CGameHUD::Start() {

		InitHPBar();

		return true;
	}

	void CGameHUD::OnDestroy() {

		DeleteGO(m_hpBarFrame);
		DeleteGO(m_hpBar);
	}

	void CGameHUD::Update() {

		//HP�o�[���X�V�B
		UpdateHPBar();
	}

	void CGameHUD::InitHPBar() {

		//HP�o�[�̃t���[�����쐬�B
		m_hpBarFrame = NewGO<CSpriteRender>(enPriority_Second);
		m_hpBarFrame->Init("Assets/Image/HP_BarFrame.dds", 400.0f, 25.0f);
		m_hpBarFrame->SetPosition({ -550.0f,230.0f,0.0f });
		m_hpBarFrame->SetPivot(CVector2::Zero);

		//HP�o�[�̔w�i���쐬�B
		m_hpBarBack = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_hpBarBack->Init("Assets/Image/HP_Back.dds", 400.0f, 25.0f);
		m_hpBarBack->SetPosition({ -550.0f,230.0f,0.0f });
		m_hpBarBack->SetPivot(CVector2::Zero);

		//HP�o�[���쐬�B
		m_hpBar = NewGO<CSpriteRender>(enPriority_First);
		m_hpBar->Init("Assets/Image/HP.dds", 400.0f, 25.0f);
		m_hpBar->SetPosition({ -550.0f,230.0f,0.0f });
		m_hpBar->SetPivot(CVector2::Zero);

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
		m_bossHpBar->Init("Assets/Image/HP.dds", 400.0f, 25.0f);
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
		m_hpBar->SetScale(m_hpBarScale);
	}
}