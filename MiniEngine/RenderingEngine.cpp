#include "stdafx.h"
#include "RenderingEngine.h"

namespace nsMyGame {

	//�����_�����O�G���W���̃C���X�^���X
	CRenderingEngine* CRenderingEngine::m_renderingEngine = nullptr;


	void CRenderingEngine::Init() {

		//�����_�����O�^�[�Q�b�g���쐬�B
		CreateRenderTarget();

		//�|�X�g�G�t�F�N�g���������B
		m_postEffect.Init();

		//�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g���������B
		InitDeferredRenderingSprite();

		//���C�������_�����O�^�[�Q�b�g�̃X�v���C�g���������B
		InitCopyToMainRenderTargetSprite();
	}

	void CRenderingEngine::Render() {

		//�����_�[�R���e�L�X�g���擾�B
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		//�V���h�E�}�b�v��`��B
		DrawShadowMap(renderContext);

		//�f�B�t�@�[�h�����_�����O�B
		ExecuteDeferredRendering(renderContext);

		//�f�B�t�@�[�h���C�e�B���O�B
		ExecuteDeferredLighting(renderContext);

		//���C�������_�����O�^�[�Q�b�g�̊G���X�i�b�v�V���b�g�B
		SnapShotMainRenderTarget(renderContext);

		//�|�X�g�G�t�F�N�g�B
		m_postEffect.Render(renderContext);

		//�t�H���g��`��B
		DrawFont(renderContext);

		//�X�v���C�g��`��B
		RenderSprite(renderContext);

		//�t���[���o�b�t�@��`��B
		CopyToFrameBuffer(renderContext);
	}

	void CRenderingEngine::CreateRenderTarget() {

		//�����_�����O�^�[�Q�b�g���쐬�B
		CRenderTarget::CreateMainRenderTarget();
		CRenderTarget::CreateShadowMap();
		CRenderTarget::CreateAlbedoAndShadowReceiverFlagRenderTarget();
		CRenderTarget::CreateNormalAndDepthRenderTarget();
		CRenderTarget::CreateWorldPosRenderTarget();
		CreateSnapShotMainRT();
	}

	void CRenderingEngine::InitDeferredRenderingSprite() {

		//�f�B�t�@�[�h�����_�����O�ɕK�v�ȃf�[�^��ݒ肷��B
		SpriteInitData spriteInitData;

		spriteInitData.m_textures[0] = &CRenderTarget::GetGBufferRT(enAlbedoAndShadowReceiverFlgMap)->GetRenderTargetTexture();
		spriteInitData.m_textures[1] = &CRenderTarget::GetGBufferRT(enNormalAndDepthMap)->GetRenderTargetTexture();
		spriteInitData.m_textures[2] = &CRenderTarget::GetGBufferRT(enWorldPosMap)->GetRenderTargetTexture();
		spriteInitData.m_width = c_renderTargetW1280H720.x;
		spriteInitData.m_height = c_renderTargetW1280H720.y;
		spriteInitData.m_fxFilePath = c_fxFilePath_DeferredLighting;
		spriteInitData.m_expandConstantBuffer = nsLight::CLightManager::GetInstance()->GetLigData();
		spriteInitData.m_expandConstantBufferSize = sizeof(*nsLight::CLightManager::GetInstance()->GetLigData());
		spriteInitData.m_expandShaderResoruceView = &CRenderTarget::GetRenderTarget(enShadowMap)->GetRenderTargetTexture();

		// �������I�u�W�F�N�g���g���āA�X�v���C�g������������
		m_deferredRenderingSprite.Init(spriteInitData);
	}


	void CRenderingEngine::CreateSnapShotMainRT() {

		//���C�������_�����O�^�[�Q�b�g�̓��e���R�s�[���郌���_�����O�^�[�Q�b�g���쐬�B
		m_snapShotMainRT.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN
		);
	}
	void CRenderingEngine::InitCopyToMainRenderTargetSprite() {

		SpriteInitData copyToMainRenderTargetSpriteInitData;

		//�e�N�X�`���ɂ̓��C�������_�����O�^�[�Q�b�g�̃e�N�X�`���J���[���w��B
		copyToMainRenderTargetSpriteInitData.m_textures[0] = &CRenderTarget::GetRenderTarget(enMainRT)->GetRenderTargetTexture();
		copyToMainRenderTargetSpriteInitData.m_width = c_renderTargetW1280H720.x;
		copyToMainRenderTargetSpriteInitData.m_height = c_renderTargetW1280H720.y;
		copyToMainRenderTargetSpriteInitData.m_fxFilePath = c_fxFilePath_Sprite;
		copyToMainRenderTargetSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

		m_copyToMainRenderTargetSprite.Init(copyToMainRenderTargetSpriteInitData);
	}

	void CRenderingEngine::DrawShadowMap(CRenderContext& rc) {

		//�`�惂�[�h���V���h�E�}�b�v�p�ɐݒ肷��B
		rc.SetRenderMode(CRenderContext::EnRender_Mode::enRenderMode_Shadow);

		//�����_�����O�^�[�Q�b�g��ݒ�B
		rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enShadowMap));

		//�r���[�|�[�g��ݒ�B
		rc.SetRenderTargetAndViewport(*CRenderTarget::GetRenderTarget(enShadowMap));

		//�����_�[�^�[�Q�b�g���N���A�B
		rc.ClearRenderTargetView(*CRenderTarget::GetRenderTarget(enShadowMap));

		//�V���h�E���f����`��B
		GameObjectManager::GetInstance()->ExecuteRender(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enShadowMap));
	}

	void CRenderingEngine::RenderSprite(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g��ݒ�B
		rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));

		//�r���[�|�[�g��ݒ�B
		rc.SetRenderTargetAndViewport(*CRenderTarget::GetRenderTarget(enMainRT));

		//�V���h�E���f����`��B
		GameObjectManager::GetInstance()->Execute2DRender(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
	}

	void CRenderingEngine::DrawFont(CRenderContext& rc) {

		//�����_�[���[�h���t�H���g�p�ɂ���B
		rc.SetRenderMode(CRenderContext::EnRender_Mode::enRenderMode_Font);

		//�����_�����O�^�[�Q�b�g��ݒ�B
		rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));

		//�r���[�|�[�g��ݒ�B
		rc.SetRenderTargetAndViewport(*CRenderTarget::GetRenderTarget(enMainRT));

		//�V���h�E���f����`��B
		GameObjectManager::GetInstance()->ExecuteRender(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
	}

	void CRenderingEngine::ExecuteDeferredRendering(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g���쐬�B
		CRenderTarget* rts[] = {
				CRenderTarget::GetGBufferRT(enAlbedoAndShadowReceiverFlgMap),   // 0�Ԗڂ̃����_�����O�^�[�Q�b�g
				CRenderTarget::GetGBufferRT(enNormalAndDepthMap),  // 1�Ԗڂ̃����_�����O�^�[�Q�b�g
				CRenderTarget::GetGBufferRT(enWorldPosMap) // 2�Ԗڂ̃����_�����O�^�[�Q�b�g
		};

		// �܂��A�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂ő҂�
		rc.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(rts), rts);

		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargets(ARRAYSIZE(rts), rts);

		//�r���[�|�[�g��ݒ�B
		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		//�A���x�h�}�b�v�Ɠ������ƍ����ɐݒ肷��B
		viewport.Width = static_cast<float>(rts[0]->GetWidth());
		viewport.Height = static_cast<float>(rts[0]->GetHeight());
		viewport.MinDepth = D3D12_MIN_DEPTH;
		viewport.MaxDepth = D3D12_MAX_DEPTH;
		rc.SetViewportAndScissor(viewport);

		// �����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetViews(ARRAYSIZE(rts), rts);

		//���f���̕`��
		rc.SetRenderMode(CRenderContext::EnRender_Mode::enRenderMode_Normal);
		GameObjectManager::GetInstance()->ExecuteRender(rc);

		// �����_�����O�^�[�Q�b�g�ւ̏������ݑ҂�
		rc.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(rts), rts);
	}

	void CRenderingEngine::ExecuteDeferredLighting(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g��ݒ�B
		rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));

		//�r���[�|�[�g��ݒ�B
		rc.SetRenderTargetAndViewport(*CRenderTarget::GetRenderTarget(enMainRT));

		//�f�B�t�@�[�h���C�e�B���O�B
		m_deferredRenderingSprite.Draw(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
	}

	void CRenderingEngine::SnapShotMainRenderTarget(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g��ݒ�B
		rc.WaitUntilToPossibleSetRenderTarget(m_snapShotMainRT);

		//�r���[�|�[�g��ݒ�B
		rc.SetRenderTargetAndViewport(m_snapShotMainRT);

		//���C�������_�����O�^�[�Q�b�g�̊G���X�i�b�v�V���b�g�B
		m_copyToMainRenderTargetSprite.Draw(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(m_snapShotMainRT);
	}

	void CRenderingEngine::CopyToFrameBuffer(CRenderContext& rc) {

		//���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		
		//�ŏI�X�v���C�g��`��B
		m_copyToMainRenderTargetSprite.Draw(rc);
	}
}