#pragma once
#include "../MiniEngine/postEffect/PostEffect.h"

namespace nsMyGame {
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
		void DrawShadowMap(RenderContext& rc);

		/**
		 * @brief �t�H���g��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void DrawFont(RenderContext& rc);

		/**
		 * @brief �f�B�t�@�[�h�����_�����O�����s����֐��B
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void ExecuteDeferredRendering(RenderContext& rc);

		/**
		 * @brief �f�B�t�@�[�h���C�e�B���O�����s����֐��B
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void ExecuteDeferredLighting(RenderContext& rc);

		/**
		 * @brief �t���[���o�b�t�@�p�ɁA���C�������_�����O�^�[�Q�b�g�̓��e���R�s�[����֐��B
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void SnapShotMainRenderTarget(RenderContext& rc);


		/**
		 * @brief �t���[���o�b�t�@�ɃX�v���C�g���R�s�[����֐��B
		 * @param rc �����_�[�R���e�L�X�g�B
		*/
		void CopyToFrameBuffer(RenderContext& rc);

	private:
		static RenderingEngine* m_renderingEngine;	//�����_�����O�G���W���̃C���X�^���X
		RenderTarget m_snapShotMainRT;				//���C�������_�����O�^�[�Q�b�g�̃X�i�b�v�V���b�g����邽�߂̃����_�����O�^�[�Q�b�g
		nsPostEffect::PostEffect m_postEffect;		//�|�X�g�G�t�F�N�g
		Sprite m_copyToMainRenderTargetSprite;		//���C�������_�����O�^�[�Q�b�g�̃X�v���C�g
		Sprite m_deferredRenderingSprite;			//�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g
	};
}

