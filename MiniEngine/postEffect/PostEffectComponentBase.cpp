#include "stdafx.h"
#include "PostEffectComponentBase.h"

namespace nsMyGame {

	namespace nsPostEffect {

		void PostEffectComponentBase::Init() {

			//�h���N���X�̏������B
			OnInit();


			//�h���N���X�ŃR�s�[������Ă���Ȃ�A�R�s�[�p�̃X�v���C�g���쐬����B
			//�u���[�����A���C�������_�����O�^�[�Q�b�g�ɒ��ډ��Z����������͔̂h���N���X��false���g�p����B
			if (IsCopyResultTextureToMainRenderTarget()) {
				SpriteInitData initData;
				initData.m_width = RenderTarget::GetRenderTarget(enMainRT)->GetWidth();
				initData.m_height = RenderTarget::GetRenderTarget(enMainRT)->GetHeight();
				initData.m_colorBufferFormat = RenderTarget::GetRenderTarget(enMainRT)->GetColorBufferFormat();
				initData.m_fxFilePath = c_fxFilePathCopySprite;
				initData.m_textures[0] = &GetResultTexture();
				m_copyMainRtSprite.Init(initData);
			}
		}

		void PostEffectComponentBase::Render(RenderContext& rc) {

			//�h���N���X�̕`��֐��Ăяo���B
			OnRender(rc);

			//auto& mainRT = *RenderTarget::GetRenderTarget(enMainRT);



			//�h���N���X�ŃR�s�[������Ă���Ȃ�A�|�X�g�G�t�F�N�g�̌��ʂ����C�������_�����O�^�[�Q�b�g�ɔ��f�B
			if (IsCopyResultTextureToMainRenderTarget()) {
				// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
				rc.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));
				// �����_�����O�^�[�Q�b�g��ݒ�
				rc.SetRenderTargetAndViewport(*RenderTarget::GetRenderTarget(enMainRT));
				// �|�X�g�G�t�F�N�g�̌��ʂ����C�������_�����O�^�[�Q�b�g�ɔ��f�B
				m_copyMainRtSprite.Draw(rc);
				// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
				rc.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));
			}
		}
	}
}