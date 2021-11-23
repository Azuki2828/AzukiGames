#pragma once
#include "../MiniEngine/postEffect/PostEffect.h"
#include "LightCulling.h"

namespace nsMyGame {
	//�����_�����O�G���W���N���X
	class CRenderingEngine
	{
	public:
		/**
		 * @brief �����_�����O�G���W�����쐬����֐��B
		*/
		static void CreateRenderingEngine() {

			m_renderingEngine = new CRenderingEngine;

			//�����_�����O�G���W���̏������B
			m_renderingEngine->Init();
		}

		/**
		 * @brief �����_�����O�G���W�����擾����֐��B
		 * @return �����_�����O�G���W��
		*/
		static CRenderingEngine* GetInstance() {

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
		 * @brief �f�B�t�@�[�h���C�e�B���O�Ŏg�p����X�v���C�g������������֐��B
		*/
		void InitDeferredLightingSprite();

		/**
		 * @brief ���C�������_�����O�^�[�Q�b�g�̃R�s�[����邽�߂̃����_�[�^�[�Q�b�g���쐬����֐��B
		*/
		void CreateSnapShotMainRT();
		/**
		 * @brief �t���[���o�b�t�@�ɃR�s�[����X�v���C�g���쐬����֐��B
		*/
		void InitCopyToMainRenderTargetSprite();

		/**
		 * @brief �V���h�E�}�b�v��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void DrawShadowMap(CRenderContext& rc);


		/**
		 * @brief �X�v���C�g��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void RenderSprite(CRenderContext& rc);

		/**
		 * @brief �t�H���g��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void DrawFont(CRenderContext& rc);

		/**
		 * @brief �G�t�F�N�g��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void DrawEffect(CRenderContext& rc);

		/**
		 * @brief G-Buffer���쐬����֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void CreateGBuffer(CRenderContext& rc);

		/**
		 * @brief �f�B�t�@�[�h���C�e�B���O�����s����֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void ExecuteDeferredLighting(CRenderContext& rc);

		/**
		 * @brief �t���[���o�b�t�@�p�ɁA���C�������_�����O�^�[�Q�b�g�̓��e���R�s�[����֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void SnapShotMainRenderTarget(CRenderContext& rc);


		/**
		 * @brief �t���[���o�b�t�@�ɃX�v���C�g���R�s�[����֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void CopyToFrameBuffer(CRenderContext& rc);

	private:
		static CRenderingEngine* m_renderingEngine;	//�����_�����O�G���W���̃C���X�^���X
		CLightCulling m_lightCulling;				//���C�g�J�����O
		CRenderTarget m_snapShotMainRT;				//���C�������_�����O�^�[�Q�b�g�̃X�i�b�v�V���b�g����邽�߂̃����_�����O�^�[�Q�b�g
		nsPostEffect::CPostEffect m_postEffect;		//�|�X�g�G�t�F�N�g
		CSprite m_copyToMainRenderTargetSprite;		//���C�������_�����O�^�[�Q�b�g�̃X�v���C�g
		CSprite m_deferredLightingSprite;			//�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g
	};
}

