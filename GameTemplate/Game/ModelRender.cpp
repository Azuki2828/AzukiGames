#include "stdafx.h"
#include "ModelRender.h"

namespace {
	constexpr const char* VS_ENTRY_POINT_VS_MAIN = "VSMain";
	constexpr const char* VS_ENTRY_POINT_VS_SKIN_MAIN = "VSSkinMain";
	constexpr const char* FX_FILE_PATH_MODEL = "Assets/shader/model.fx";
}

void ModelRender::Init() {

	//tkm�t�@�C���̃��[�h�B
	if (m_filePathTkm != nullptr) {
		m_modelInitData.m_tkmFilePath = m_filePathTkm;
	}
	else {
		//���[�h�G���[�B
		MessageBox(nullptr, L"tkm�t�@�C�����ǂݍ��܂�Ă��܂���B", L"�x��", MB_OK);
	}

	//tks�t�@�C���̃��[�h�B
	if (m_filePathTks != nullptr) {
		m_skeleton.Init(m_filePathTks);
	}

	//���_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
	m_modelInitData.m_vsEntryPointFunc = VS_ENTRY_POINT_VS_MAIN;
	m_modelInitData.m_vsSkinEntryPointFunc = VS_ENTRY_POINT_VS_SKIN_MAIN;

	//fx�t�@�C���p�X���w��B
	m_modelInitData.m_fxFilePath = FX_FILE_PATH_MODEL;

	//�V���h�E���V�[�o�[�t���O��true�Ȃ�V���h�E���V�[�o�[��p��fx�t�@�C�����w�肷��B
	if (m_shadowReceiverFlag) {
		m_modelInitData.m_fxFilePath = "Assets/shader/shadowReceiverModel.fx";
	}

	//�R���X�^���g�o�b�t�@�Ƀ��C�g��������B
	m_modelInitData.m_expandConstantBuffer = LightManager().GetInstance()->GetLigData();
	m_modelInitData.m_expandConstantBufferSize = sizeof(*LightManager().GetInstance()->GetLigData());

	//���W�X�^��t10�ɃV���h�E�}�b�v��ݒ�B
	m_modelInitData.m_expandShaderResoruceView = &RenderTarget::GetRenderTarget(enShadowMap)->GetRenderTargetTexture();

	//�X�P���g����ݒ�B
	if (m_skeleton.IsInited()) {
		m_modelInitData.m_skeleton = &m_skeleton;
	}

	//�V���h�E�L���X�^�[�t���O��true�Ȃ�V���h�E���f�����쐬����B
	if (m_shadowCasterFlag) {
		ModelInitData ShadowModelInitData;
		ShadowModelInitData.m_fxFilePath = FX_FILE_PATH_SHADOW_MAP;
		ShadowModelInitData.m_tkmFilePath = m_filePathTkm;
		ShadowModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32_FLOAT;
		ShadowModelInitData.m_vsEntryPointFunc = VS_ENTRY_POINT_VS_MAIN;
		ShadowModelInitData.m_vsSkinEntryPointFunc = VS_ENTRY_POINT_VS_SKIN_MAIN;

		if (m_skeleton.IsInited()) {
			ShadowModelInitData.m_skeleton = &m_skeleton;
		}
		m_shadowModel.Init(ShadowModelInitData);
		m_shadowModel.UpdateWorldMatrix(
			m_pos,
			m_rot,
			m_sca
		);
	}

	//���f���f�[�^�����Ƀ��f�����������B
	m_model.Init(m_modelInitData);

	//�A�j���[�V�������������B
	m_animation.Init(m_skeleton, m_animationClip, m_animNum);
}

void ModelRender::Update() {

	//�X�P���g�����X�V�B
	m_skeleton.Update(m_model.GetWorldMatrix());

	//�A�j���[�V������i�߂�B
	if (m_animFlg) {
		m_animation.Progress(GameTime().GameTimeFunc().GetFrameDeltaTime());
	}

	//���f���̏����X�V�B
	m_model.UpdateWorldMatrix(
		m_pos,
		m_rot,
		m_sca
	);

	//�V���h�E���f���̏����X�V�B
	m_shadowModel.UpdateWorldMatrix(
		m_pos,
		m_rot,
		m_sca
	);

	//�J�����̏���������߂�B
	Vector3 Vec_x = Vector3::AxisX;
	Vector3 TarPos = Camera::GetLightCamera()->GetTarget() - Camera::GetLightCamera()->GetPosition();
	TarPos.Normalize();
	Vector3 CameraUp;

	CameraUp.Cross(TarPos, Vec_x);
	CameraUp.Normalize();
	Camera::GetLightCamera()->SetUp(CameraUp);
	Camera::GetLightCamera()->Update();
}

void ModelRender::Render(RenderContext& rc) {

	switch (rc.GetRenderMode()) {
		case RenderContext::EnRender_Mode::enRenderMode_Normal:
			//���f����`��B
			m_model.Draw(rc);
			break;
		case RenderContext::EnRender_Mode::enRenderMode_Shadow:
			//�V���h�E���f����`��B
			m_shadowModel.Draw(rc, *Camera::GetLightCamera());
			break;
	}
}
