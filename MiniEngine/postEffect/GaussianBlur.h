#pragma once
#include "Sprite.h"

namespace nsMyGame {

	namespace nsPostEffect {
		
		
		//�K�E�V�A���u���[�N���X
		
		class GaussianBlur {
		public:
			/**
			 * @brief �������֐��B
			 * @param originalTexture �K�E�V�A���u���[��������I���W�i���e�N�X�`���B
			*/
			void Init(Texture* originalTexture);

			/**
			 * @brief �K�E�V�A���u���[��GPU��Ŏ��s����֐��B
			 * @param rc �����_�[�R���e�L�X�g
			 * @param blurPower �u���[�̋����B�l���傫���قǃ{�P�������Ȃ�B
			 * 
			 * �{�֐��̌Ăяo���́ADirectX12�𗘗p�����`��R�}���h�������ɌĂяo���K�v������܂��B
			*/
			void ExecuteOnGPU(RenderContext& rc, float blurPower);

			/**
			 * @brief �{�P�e�N�X�`�����擾����֐��B
			 * @return �{�P�e�N�X�`��
			*/
			Texture& GetBokeTexture()
			{
				return m_yBlurRenderTarget.GetRenderTargetTexture();
			}
		private:

			/**
			 * @brief �����_�����O�^�[�Q�b�g������������֐��B
			*/
			void InitRenderTargets();

			/**
			 * @brief �X�v���C�g������������֐��B
			*/
			void InitSprites();

			/**
			 * @brief �d�݃e�[�u�����X�V����֐��B
			 * @param blurPower �d��
			*/
			void UpdateWeightsTable(float blurPower);

		private:
			float m_weights[c_gaussianBlurNumWeight];			//�d�݃e�[�u��
			Texture* m_originalTexture = nullptr;	//�I���W�i���e�N�X�`��
			RenderTarget m_xBlurRenderTarget;		//���{�P�摜��`�悷�郌���_�����O�^�[�Q�b�g
			RenderTarget m_yBlurRenderTarget;		//�c�{�P�摜��`�悷�郌���_�����O�^�[�Q�b�g
			Sprite m_xBlurSprite;					//���{�P�摜��`�悷�邽�߂̃X�v���C�g
			Sprite m_yBlurSprite;					//�c�{�P�摜��`�悷�邽�߂̃X�v���C�g
		};
	}
}
