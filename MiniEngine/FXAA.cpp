#include "stdafx.h"
#include "FXAA.h"

void FXAA::Init() {

    // �ŏI�����p�̃X�v���C�g������������
    SpriteInitData spriteInitData;
    spriteInitData.m_textures[0] = &RenderTarget::GetRenderTarget(enMainRT)->GetRenderTargetTexture();
    // �𑜓x��mainRenderTarget�̕��ƍ���
    spriteInitData.m_width = RenderTarget::GetRenderTarget(enMainRT)->GetWidth();
    spriteInitData.m_height = RenderTarget::GetRenderTarget(enMainRT)->GetHeight();
    // 2D�p�̃V�F�[�_�[���g�p����
    spriteInitData.m_fxFilePath = "Assets/shader/fxaa.fx";
    spriteInitData.m_vsEntryPointFunc = "VSMain";
    spriteInitData.m_psEntryPoinFunc = "PSMain";

    spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;

    //�𑜓x��GPU�ɑ��邽�߂̒萔�o�b�t�@��ݒ肷��B
    spriteInitData.m_expandConstantBuffer = (void*)&m_buffer;
    spriteInitData.m_expandConstantBufferSize = sizeof(SFXAABuffer) +
        (16 - (sizeof(SFXAABuffer) % 16));
    m_finalSprite.Init(spriteInitData);
}

void FXAA::Render(RenderContext& rc) {

    // �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
    rc.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetRenderTarget(enFXAART));
    // �����_�����O�^�[�Q�b�g��ݒ�
    rc.SetRenderTargetAndViewport(*RenderTarget::GetRenderTarget(enFXAART));
    m_buffer.bufferW = static_cast<float>(g_graphicsEngine->GetFrameBufferWidth());
    m_buffer.bufferH = static_cast<float>(g_graphicsEngine->GetFrameBufferHeight());
    //�`��B
    m_finalSprite.Draw(rc);
    // �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
    //���C�������_�\�^�[�Q�b�g��RENDERTARGET����PRESENT�ցB
    rc.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetRenderTarget(enFXAART));
}