#include "stdafx.h"
#include "RenderingEngine.h"

RenderingEngine* RenderingEngine::m_renderingEngine = nullptr;


void RenderingEngine::Init() {

	//�����_�����O�^�[�Q�b�g���쐬�B
	CreateRenderTarget();

	//�|�X�g�G�t�F�N�g���������B
	InitPostEffect();

	//�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g���������B
	InitDeferredRenderingSprite();

	//���C�������_�����O�^�[�Q�b�g�̃X�v���C�g���������B
	InitCopyToMainRenderTargetSprite();
}

void RenderingEngine::Render() {

	//�V���h�E�}�b�v��`��B
	DrawShadowMap();

	//�f�B�t�@�[�h�����_�����O
	ExecuteDeferredRendering();

	//�f�B�t�@�[�h���C�e�B���O�B
	ExecuteDeferredLighting();

	//�P�x�e�N�X�`�����쐬�B
	//ExecuteDrawLuminanceTexture();

	//�u���[���B
	//ExecuteGaussianBlur();

	DrawFont();
	//�t���[���o�b�t�@��`��B
	CopyToFrameBuffer();
}

void RenderingEngine::CreateRenderTarget() {

	//�����_�����O�^�[�Q�b�g���쐬�B
	RenderTarget::CreateMainRenderTarget();
	RenderTarget::CreateLuminanceRenderTarget();
	RenderTarget::CreateShadowMap();
	RenderTarget::CreateAlbedoAndShadowReceiverFlagRenderTarget();
	RenderTarget::CreateNormalAndDepthRenderTarget();
	RenderTarget::CreateWorldPosRenderTarget();
}

void RenderingEngine::InitPostEffect() {

	//�u���[���ɕK�v�ȃe�N�X�`�����������B
	m_postEffect = NewGO<PostEffect>(0);
	m_postEffect->InitLuminance(*RenderTarget::GetRenderTarget(enMainRT));
	m_postEffect->InitGaussianBlur(*RenderTarget::GetRenderTarget(enLuminanceRT));
}

void RenderingEngine::InitDeferredRenderingSprite() {

	//�f�B�t�@�[�h�����_�����O�ɕK�v�ȃf�[�^��ݒ肷��B
	SpriteInitData spriteInitData;

	spriteInitData.m_textures[0] = &RenderTarget::GetGBufferRT(enAlbedoAndShadowReceiverFlgMap)->GetRenderTargetTexture();
	spriteInitData.m_textures[1] = &RenderTarget::GetGBufferRT(enNormalAndDepthMap)->GetRenderTargetTexture();
	spriteInitData.m_textures[2] = &RenderTarget::GetGBufferRT(enWorldPosMap)->GetRenderTargetTexture();
	spriteInitData.m_width = c_renderTargetW1280H720.x;
	spriteInitData.m_height = c_renderTargetW1280H720.y;
	spriteInitData.m_fxFilePath = c_fxFilePath_DeferredLighting;
	spriteInitData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigData();
	spriteInitData.m_expandConstantBufferSize = sizeof(*LightManager::GetInstance()->GetLigData());
	spriteInitData.m_expandShaderResoruceView = &RenderTarget::GetRenderTarget(enShadowMap)->GetRenderTargetTexture();

	// �������I�u�W�F�N�g���g���āA�X�v���C�g������������
	m_deferredRenderingSprite.Init(spriteInitData);
}

void RenderingEngine::InitCopyToMainRenderTargetSprite() {

	SpriteInitData copyToMainRenderTargetSpriteInitData;

	//�e�N�X�`���ɂ̓��C�������_�����O�^�[�Q�b�g�̃e�N�X�`���J���[���w��B
	copyToMainRenderTargetSpriteInitData.m_textures[0] = &RenderTarget::GetRenderTarget(enMainRT)->GetRenderTargetTexture();
	copyToMainRenderTargetSpriteInitData.m_width = c_renderTargetW1280H720.x;
	copyToMainRenderTargetSpriteInitData.m_height = c_renderTargetW1280H720.y;
	copyToMainRenderTargetSpriteInitData.m_fxFilePath = c_fxFilePath_Sprite;
	copyToMainRenderTargetSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	m_copyToMainRenderTargetSprite.Init(copyToMainRenderTargetSpriteInitData);
}

void RenderingEngine::DrawShadowMap() {

	auto& renderContext = g_graphicsEngine->GetRenderContext();
	
	//�`�惂�[�h���V���h�E�}�b�v�p�ɐݒ肷��B
	renderContext.SetRenderMode(RenderContext::EnRender_Mode::enRenderMode_Shadow);

	renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetRenderTarget(enShadowMap));

	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetRenderTarget(enShadowMap));

	renderContext.ClearRenderTargetView(*RenderTarget::GetRenderTarget(enShadowMap));

	//�V���h�E���f����`��B
	GameObjectManager::GetInstance()->ExecuteRender(renderContext);

	renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetRenderTarget(enShadowMap));
}

void RenderingEngine::DrawFont() {

	auto& renderContext = g_graphicsEngine->GetRenderContext();

	renderContext.SetRenderMode(RenderContext::EnRender_Mode::enRenderMode_Font);

	renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));

	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetRenderTarget(enMainRT));

	GameObjectManager::GetInstance()->ExecuteRender(renderContext);

	renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));
}

void RenderingEngine::ExecuteDeferredRendering() {

	auto& renderContext = g_graphicsEngine->GetRenderContext();

	RenderTarget* rts[] = {
			RenderTarget::GetGBufferRT(enAlbedoAndShadowReceiverFlgMap),   // 0�Ԗڂ̃����_�����O�^�[�Q�b�g
			RenderTarget::GetGBufferRT(enNormalAndDepthMap),  // 1�Ԗڂ̃����_�����O�^�[�Q�b�g
			RenderTarget::GetGBufferRT(enWorldPosMap) // 2�Ԗڂ̃����_�����O�^�[�Q�b�g
	};

	// �܂��A�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂ő҂�
	renderContext.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(rts), rts);

	// �����_�����O�^�[�Q�b�g��ݒ�
	renderContext.SetRenderTargets(ARRAYSIZE(rts), rts);

	//�r���[�|�[�g��ݒ�B
	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	//�A���x�h�}�b�v�Ɠ������ƍ����ɐݒ肷��B
	viewport.Width = static_cast<float>(rts[0]->GetWidth());
	viewport.Height = static_cast<float>(rts[0]->GetHeight());
	viewport.MinDepth = D3D12_MIN_DEPTH;
	viewport.MaxDepth = D3D12_MAX_DEPTH;
	renderContext.SetViewportAndScissor(viewport);

	// �����_�����O�^�[�Q�b�g���N���A
	renderContext.ClearRenderTargetViews(ARRAYSIZE(rts), rts);

	//���f���̕`��
	renderContext.SetRenderMode(RenderContext::EnRender_Mode::enRenderMode_Normal);
	GameObjectManager::GetInstance()->ExecuteRender(renderContext);

	// �����_�����O�^�[�Q�b�g�ւ̏������ݑ҂�
	renderContext.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(rts), rts);
}

void RenderingEngine::ExecuteDeferredLighting() {

	auto& renderContext = g_graphicsEngine->GetRenderContext();

	renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));

	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetRenderTarget(enMainRT));

	m_deferredRenderingSprite.Draw(renderContext);

	renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));
}

void RenderingEngine::ExecuteDrawLuminanceTexture() {

	auto& renderContext = g_graphicsEngine->GetRenderContext();

	auto& luminanceRenderTarget = *RenderTarget::GetRenderTarget(enLuminanceRT);

	// �P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
	renderContext.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);

	// �����_�����O�^�[�Q�b�g��ݒ�
	renderContext.SetRenderTargetAndViewport(luminanceRenderTarget);

	// �����_�����O�^�[�Q�b�g���N���A
	renderContext.ClearRenderTargetView(luminanceRenderTarget);

	// �P�x���o���s��
	m_postEffect->GetLuminanceSprite().Draw(renderContext);

	// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
	renderContext.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
}

void RenderingEngine::ExecuteGaussianBlur() {

	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//�K�E�V�A���u���[��4����s����
	for (int i = 0; i < c_gaussianBlurNum; i++) {

		m_postEffect->GetGaussianBlurSprite(i).ExecuteOnGPU(renderContext, c_blurPower);
	}

	//4���̃{�P�摜���������ă��C�������_�����O�^�[�Q�b�g�ɉ��Z����
	renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));

	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetRenderTarget(enMainRT));

	m_postEffect->GetFinalSprite().Draw(renderContext);

	renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));
}

void RenderingEngine::CopyToFrameBuffer() {

	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
	renderContext.SetRenderTarget(
		g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		g_graphicsEngine->GetCurrentFrameBuffuerDSV()
	);
	m_copyToMainRenderTargetSprite.Draw(renderContext);
}