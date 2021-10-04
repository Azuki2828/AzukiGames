#pragma once
#include "PostEffect.h"

//�����_�����O�G���W���N���X
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

	/**
	 * @brief �`��֐��B
	*/
	void Render();
private:
	/**
	 * @brief �����_�����O�^�[�Q�b�g���쐬����֐��B
	*/
	void CreateRenderTarget();

	/**
	 * @brief �|�X�g�G�t�F�N�g������������֐��B
	*/
	void InitPostEffect();

	/**
	 * @brief �f�B�t�@�[�h���C�e�B���O�Ŏg�p����X�v���C�g������������֐��B
	*/
	void InitDeferredRenderingSprite();

	/**
	 * @brief �t���[���o�b�t�@�ɃR�s�[����X�v���C�g���쐬����֐��B
	*/
	void InitCopyToMainRenderTargetSprite();

	/**
	 * @brief �V���h�E�}�b�v��`�悷��֐��B
	*/
	void DrawShadowMap();

	/**
	 * @brief �t�H���g��`�悷��֐��B
	*/
	void DrawFont();

	/**
	 * @brief �f�B�t�@�[�h�����_�����O�����s����֐��B
	*/
	void ExecuteDeferredRendering();

	/**
	 * @brief �f�B�t�@�[�h���C�e�B���O�����s����֐��B
	*/
	void ExecuteDeferredLighting();

	/**
	 * @brief �P�x�e�N�X�`����`�悷��֐��B
	*/
	void ExecuteDrawLuminanceTexture();

	/**
	 * @brief �K�E�V�A���u���[��������֐��B
	*/
	void ExecuteGaussianBlur();

	/**
	 * @brief �t���[���o�b�t�@�ɃX�v���C�g���R�s�[����֐��B
	*/
	void CopyToFrameBuffer();
private:
	static RenderingEngine* m_renderingEngine;	//�����_�����O�G���W���̃C���X�^���X
	PostEffect* m_postEffect = nullptr;			//�|�X�g�G�t�F�N�g
	Sprite m_copyToMainRenderTargetSprite;		//���C�������_�����O�^�[�Q�b�g�̃X�v���C�g
	Sprite m_deferredRenderingSprite;			//�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g
};

