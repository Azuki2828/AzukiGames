#pragma once
#include "PostEffectComponentBase.h"

namespace nsMyGame {

	namespace nsPostEffect {

		//FXAA�N���X

		class CFXAA : public CPostEffectComponentBase
		{
		private:
			//FXAA�pBuffer
			struct SFXAABuffer {
				float bufferW;
				float bufferH;
			};
		public:
			/**
			 * @brief �������֐��B
			*/
			void OnInit();

			/**
			 * @brief �`��֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void OnRender(RenderContext& rc);

			/**
			 * @brief FXAA��̃e�N�X�`�����擾����֐��B
			 * @return FXAA��̃e�N�X�`��
			*/
			Texture& GetResultTexture()override final {

				return m_fxaaRT.GetRenderTargetTexture();
			};

			/**
			 * @brief �|�X�g�̌��ʂ����C�������_�����O�^�[�Q�b�g�ɃR�s�[����H
			 * @return �R�s�[����H
			*/
			bool IsCopyResultTextureToMainRenderTarget() const override final
			{
				return true;
			}

		private:
			RenderTarget m_fxaaRT;		//FXAA�p�̃����_�����O�^�[�Q�b�g
			SFXAABuffer m_buffer;		//FXAA�p�̍\���̃o�b�t�@
			Sprite m_finalSprite;		//�ŏI�X�v���C�g
		};
	}
}

