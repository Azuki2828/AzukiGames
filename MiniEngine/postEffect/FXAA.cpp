#include "stdafx.h"
#include "FXAA.h"

namespace nsMyGame {

    namespace nsPostEffect {

        void FXAA::OnInit() {

            //FXAA�p�̃����_�����O�^�[�Q�b�g���쐬����B
            m_fxaaRT.Create(
                RenderTarget::GetRenderTarget(enMainRT)->GetWidth(),
                RenderTarget::GetRenderTarget(enMainRT)->GetHeight(),
                c_mipLevel1,
                c_renderArraySize1,
                DXGI_FORMAT_R8G8B8A8_UNORM,
                DXGI_FORMAT_UNKNOWN
            );

            //�ŏI�����p�̃X�v���C�g������������B
            SpriteInitData spriteInitData;
            spriteInitData.m_textures[0] = &RenderTarget::GetRenderTarget(enMainRT)->GetRenderTargetTexture();

            //�𑜓x��mainRenderTarget�̕��ƍ����Ɠ����ɂ���B
            spriteInitData.m_width = RenderTarget::GetRenderTarget(enMainRT)->GetWidth();
            spriteInitData.m_height = RenderTarget::GetRenderTarget(enMainRT)->GetHeight();

            //FXAA�p�̃V�F�[�_�[���g�p����B
            spriteInitData.m_fxFilePath = "Assets/shader/fxaa.fx";
            spriteInitData.m_vsEntryPointFunc = "VSMain";
            spriteInitData.m_psEntryPoinFunc = "PSMain";

            //�A���t�@�u�����f�B���O���[�h�͎w�肵�Ȃ��B
            spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;

            //�𑜓x��GPU�ɑ��邽�߂̒萔�o�b�t�@��ݒ肷��B
            spriteInitData.m_expandConstantBuffer = (void*)&m_buffer;
            spriteInitData.m_expandConstantBufferSize = sizeof(SFXAABuffer) +
                (16 - (sizeof(SFXAABuffer) % 16));

            //�X�v���C�g���������B
            m_finalSprite.Init(spriteInitData);
        }

        void FXAA::OnRender(RenderContext& rc) {

            // �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
            rc.WaitUntilToPossibleSetRenderTarget(m_fxaaRT);
            // �����_�����O�^�[�Q�b�g��ݒ�
            rc.SetRenderTargetAndViewport(m_fxaaRT);
            m_buffer.bufferW = static_cast<float>(g_graphicsEngine->GetFrameBufferWidth());
            m_buffer.bufferH = static_cast<float>(g_graphicsEngine->GetFrameBufferHeight());
            //�`��B
            m_finalSprite.Draw(rc);
            // �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
            rc.WaitUntilFinishDrawingToRenderTarget(m_fxaaRT);
        }
    }
}