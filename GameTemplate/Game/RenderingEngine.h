#pragma once
#include "PostEffect.h"

class RenderingEngine
{
public:
	/**
	 * @brief �����_�����O�G���W�����쐬����֐��B
	*/
	static void CreateRenderingEngine() {

		m_renderingEngine = new RenderingEngine;
	}

	/**
	 * @brief �����_�����O�G���W�����擾����֐��B
	 * @return �����_�����O�G���W��
	*/
	static RenderingEngine* GetInstance() {

		return m_renderingEngine;
	}

	/**
	 * @brief �������֐��B
	*/
	void Init();

	void Render();
private:
	void CreateRenderTarget();

	void InitPostEffect();

	void InitCopyToMainRenderTargetSprite();

	void DrawShadowMap();

	void DrawModel();

	void ExecuteDrawLuminanceTexture();

	void ExecuteGaussianBlur();

	void CopyToFrameBuffer();
private:
	static RenderingEngine* m_renderingEngine;	//�����_�����O�G���W���̃C���X�^���X
	PostEffect* m_postEffect = nullptr;
	Sprite m_copyToMainRenderTargetSprite;
};

