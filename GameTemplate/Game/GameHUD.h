#pragma once

namespace nsMyGame {

	//HUD�N���X
	class CGameHUD : public CIGameObject
	{
		//��HP�o�[�̌����̎d��
		enum EnHPDecreaseType {

			enType_Linear,		//���`
			enType_NonLinear	//����`
		};

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
		 * @brief HP�o�[������������֐��B
		*/
		void InitHPBar();

		/**
		 * @brief HP�o�[�̍X�V���s���֐��B
		*/
		void UpdateHPBar();

		/**
		 * @brief ��HP�o�[�̍X�V���s���֐��B
		*/
		void UpdateRedHPBar();
	public:
		/**
		 * @brief �{�X��HP�o�[��L���ɂ���֐��B
		*/
		void ActivateBossHUD() {

			m_bossHpBarFrame->Activate();
			m_bossHpBar->Activate();
			m_bossHpBarBack->Activate();
			m_bossNameText->Activate();
		}

		void UpdateBossHUD(const int hp) {

			//HP�Q�[�W���X�V�B
			m_bossHpBarScale.x = static_cast<float>(hp) / static_cast<float>(nsEnemy::c_bossMaxHP);

			if (m_bossHpBarScale.x <= 0.0f) {

				m_bossHpBarScale.x = 0.0f;
			}
			//�g�嗦��ݒ�B
			m_bossHpBar->SetScale(m_bossHpBarScale);
		}
	private:
		CSpriteRender* m_hpBarFrame = nullptr;			//HP�o�[�̃t���[��
		CSpriteRender* m_hpBar_Green = nullptr;			//HP�o�[(��)
		CSpriteRender* m_hpBar_Red = nullptr;			//HP�o�[(��)
		CSpriteRender* m_hpBarBack = nullptr;			//HP�o�[�̔w�i
		CVector3 m_hpBarScale = CVector3::One;			//HP�o�[�̊g�嗦

		bool m_isActiveBossHPBar = false;				//�{�X��HP�o�[���L���H
		CSpriteRender* m_bossHpBarFrame = nullptr;		//�{�X��HP�o�[�̃t���[��
		CSpriteRender* m_bossHpBar = nullptr;			//�{�X��HP�o�[
		CSpriteRender* m_bossHpBarBack = nullptr;		//�{�X��HP�o�[�̔w�i
		CVector3 m_bossHpBarScale = CVector3::One;		//�{�X��HP�o�[�̊g�嗦
		nsFont::CFontRender* m_bossNameText = nullptr;	//�{�X�̖��O

		EnHPDecreaseType m_hpDecreaseType = enType_Linear;	//��HP�o�[�̌����̎d��
		bool m_canHPBarScaleUpdate = true;					//��HP�o�[�̊g�嗦���X�V�ł���H
		float m_damageTimer = 0.0f;							//��HP�Q�[�W����������܂ł̎��Ԃ��͂���^�C�}�[
		float m_damageScale = 0.0f;							//��HP�Q�[�W�̌����̊g�嗦
	};
}

