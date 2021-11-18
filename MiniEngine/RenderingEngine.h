#pragma once
#include "../MiniEngine/postEffect/PostEffect.h"

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
		void InitDeferredRenderingSprite();

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
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void DrawShadowMap(CRenderContext& rc);


		/**
		 * @brief �X�v���C�g��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void RenderSprite(CRenderContext& rc);

		/**
		 * @brief �t�H���g��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void DrawFont(CRenderContext& rc);

		/**
		 * @brief �f�B�t�@�[�h�����_�����O�����s����֐��B
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void ExecuteDeferredRendering(CRenderContext& rc);

		/**
		 * @brief �f�B�t�@�[�h���C�e�B���O�����s����֐��B
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void ExecuteDeferredLighting(CRenderContext& rc);

		/**
		 * @brief �t���[���o�b�t�@�p�ɁA���C�������_�����O�^�[�Q�b�g�̓��e���R�s�[����֐��B
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void SnapShotMainRenderTarget(CRenderContext& rc);


		/**
		 * @brief �t���[���o�b�t�@�ɃX�v���C�g���R�s�[����֐��B
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void CopyToFrameBuffer(CRenderContext& rc);

	private:
		static CRenderingEngine* m_renderingEngine;	//�����_�����O�G���W���̃C���X�^���X
		CRenderTarget m_snapShotMainRT;				//���C�������_�����O�^�[�Q�b�g�̃X�i�b�v�V���b�g����邽�߂̃����_�����O�^�[�Q�b�g
		nsPostEffect::CPostEffect m_postEffect;		//�|�X�g�G�t�F�N�g
		CSprite m_copyToMainRenderTargetSprite;		//���C�������_�����O�^�[�Q�b�g�̃X�v���C�g
		CSprite m_deferredRenderingSprite;			//�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g
	};
}

