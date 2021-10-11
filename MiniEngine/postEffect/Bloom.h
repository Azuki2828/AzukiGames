#pragma once
#include "PostEffectComponentBase.h"
#include "GaussianBlur.h"


namespace nsMyGame {

	namespace nsPostEffect {

		//�u���[���N���X

		class Bloom : public PostEffectComponentBase
		{
		public:
			/**
			 * @brief �������֐��B
			*/
			void OnInit()override final;

			/**
			 * @brief �`��֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void OnRender(RenderContext& rc)override final;

			/**
			 * @brief �P�x�e�N�X�`�����擾����֐��B
			 * @return �P�x�e�N�X�`��
			*/
			Texture& GetResultTexture()override final {

				return m_luminanceRT.GetRenderTargetTexture();
			}

		private:
			/**
			 * @brief �P�x���o�Ɏg�p����X�v���C�g������������֐��B
			*/
			void InitLuminanceSprite();

			/**
			 * @brief �K�E�V�A���u���[�Ɏg�p����X�v���C�g������������֐��B
			*/
			void InitGaussianBlurSprite();

			/**
			 * @brief �P�x���o�����s����֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void ExecuteDrawLuminanceSprite(RenderContext& rc);

			/**
			 * @brief �K�E�V�A���u���[�����s����֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void ExecuteGaussianBlur(RenderContext& rc);

		private:
			RenderTarget m_luminanceRT;			//�P�x���o�p�̃����_�����O�^�[�Q�b�g
			GaussianBlur m_gaussianBlur[4];		//�K�E�V�A���u���[�N���X�̃C���X�^���X
			Sprite m_luminanceSprite;			//�P�x���o�p�̃X�v���C�g
			Sprite m_bloomFinalSprite;			//�u���[���̍ŏI�X�v���C�g
		};
	}
}