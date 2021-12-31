#pragma once

namespace nsMyGame {

	//HUD�N���X
	class CGameHUD : public CIGameObject
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

		/**
		 * @brief HP�o�[�̍X�V���s���֐��B
		*/
		void UpdateHPBar();
	private:
		CSpriteRender* m_hpBarFrame = nullptr;			//HP�o�[�̃t���[��
		CSpriteRender* m_hpBar = nullptr;				//HP�o�[
		CSpriteRender* m_hpBarBack = nullptr;			//HP�o�[�̔w�i
		CVector3 m_hpBarScale = CVector3::One;			//HP�o�[�̊g�嗦
	};
}

