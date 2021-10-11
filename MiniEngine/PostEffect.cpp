#include "stdafx.h"
#include "PostEffect.h"


namespace nsMyGame {

	bool PostEffect::Start() {

		return true;
	}
	void PostEffect::InitLuminance(RenderTarget& renderTarget) {
		// �P�x���o�p�̃X�v���C�g��������
		// �����������쐬����
		SpriteInitData luminanceSpriteInitData;

		// �P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";

		// ���_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";

		// �s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";

		// �X�v���C�g�̕��ƍ�����luminnceRenderTarget�Ɠ���
		luminanceSpriteInitData.m_width = 1280;
		luminanceSpriteInitData.m_height = 720;

		// �e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[
		luminanceSpriteInitData.m_textures[0] = &renderTarget.GetRenderTargetTexture();

		// �`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
		luminanceSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

		// �쐬�����������������ƂɃX�v���C�g������������
		m_sprite[0].Init(luminanceSpriteInitData);
	}

	void PostEffect::InitGaussianBlur(RenderTarget& renderTarget) {

		//
		m_gaussianBlur[0].Init(&renderTarget.GetRenderTargetTexture());
		m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());
		m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());
		m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

		// step-2 �{�P�摜���������ď������ނ��߂̃X�v���C�g��������

		SpriteInitData finalSpriteInitData;

		finalSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();

		finalSpriteInitData.m_width = 1280;
		finalSpriteInitData.m_height = 720;

		finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		finalSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

		m_sprite[1].Init(finalSpriteInitData);
	}

	void PostEffect::InitFXAA() {
		m_fxaa.Init();
	}

	void PostEffect::RenderFXAA(RenderContext& rc) {

		m_fxaa.Render(rc);
	}
}