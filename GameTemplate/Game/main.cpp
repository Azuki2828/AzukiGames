#include "stdafx.h"
#include "system/system.h"
#include "Enemy.h"
#include "Player.h"
#include "BackGround.h"
#include "MainCamera.h"
#include "PostEffect.h"


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

/**
 * @brief Python�̏������B
*/
void InitPython(wchar_t*& program)
{
	program = Py_DecodeLocale("MyGame", nullptr);
	// ���W���[���̃p�X��ݒ�B
	Py_SetPath(L"./Python37_64/DLLs;./Python37_64/Lib;./EnemyState;../x64/Debug/");
	Py_SetProgramName(program);
	Py_Initialize();
}
/**
 * @brief Python�̏I�������B
*/
void FinalPython(wchar_t* program)
{
	Py_Finalize();
	PyMem_RawFree(program);
}
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int WINAPI AppMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	wchar_t* program;

	// python�������B
	InitPython(program);

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	LightManager::CreateInstance();

	RenderTarget::CreateMainRenderTarget();
	RenderTarget::CreateLuminanceRenderTarget();
	RenderTarget::CreateShadowMap();
	Camera::CreateLightCamera();
	
	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂�
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// �Ƃ肠�����e�X�g�œG��ǉ��B
	NewGO<Enemy>(0, nullptr);
	NewGO<Player>(0,"player");
	NewGO<BackGround>(0);
	NewGO<MainCamera>(0);

	DirectionLight* dirLight = NewGO<DirectionLight>(0);
	dirLight->SetLigDirection({0.0f,1.0f,1.0f});
	dirLight->SetLigColor({20.0f,20.0f,20.0f});

	PointLight* poiLight = NewGO<PointLight>(0);
	poiLight->SetPosition({ 100.0f,100.0f,0.0f });
	poiLight->SetColor({ 5.0f,0.0f,0.0f });
	poiLight->SetRange(200.0f);
	poiLight->SetAffectPowParam(3.0f);

	PointLight* poiLight2 = NewGO<PointLight>(0);
	poiLight2->SetPosition({ -50.0f,100.0f,0.0f });
	poiLight2->SetColor({ 0.0f,0.0f,5.0f });
	poiLight2->SetRange(200.0f);
	poiLight2->SetAffectPowParam(3.0f);

	PostEffect* postEffect = NewGO<PostEffect>(0);
	postEffect->InitLuminance(*RenderTarget::GetRenderTarget(enMainRT));
	postEffect->InitGaussianBlur(*RenderTarget::GetRenderTarget(enLuminanceRT));

	/*SpriteInitData spriteInitData;
	spriteInitData.m_textures[0] = &RenderTarget::GetRenderTarget(enShadowMap)->GetRenderTargetTexture();
	spriteInitData.m_fxFilePath = SPRITE_SHADER_MONOCHROME_FILE_PATH;
	spriteInitData.m_width = 256;
	spriteInitData.m_height = 256;

	Sprite sprite;
	sprite.Init(spriteInitData);*/
 	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		
		//sprite[1].Update(pos[1], Quaternion::Identity, Vector3::One);

		Sprite m_copyToMainRenderTargetSprite;
		SpriteInitData copyToMainRenderTargetSpriteInitData;
		copyToMainRenderTargetSpriteInitData.m_textures[0] = &RenderTarget::GetRenderTarget(enMainRT)->GetRenderTargetTexture();
		copyToMainRenderTargetSpriteInitData.m_width = RENDER_TARGET_W1280H720.x;
		copyToMainRenderTargetSpriteInitData.m_height = RENDER_TARGET_W1280H720.y;
		copyToMainRenderTargetSpriteInitData.m_fxFilePath = SPRITE_SHADER_MONOCHROME_FILE_PATH;
		copyToMainRenderTargetSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

		m_copyToMainRenderTargetSprite.Init(copyToMainRenderTargetSpriteInitData);

		GameObjectManager::GetInstance()->ExecuteUpdate();
		LightManager::GetInstance()->Update();


		renderContext.SetRenderMode(RenderContext::EnRender_Mode::enRenderMode_Shadow);

		renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetRenderTarget(enShadowMap));

		renderContext.SetRenderTargetAndViewport(*RenderTarget::GetRenderTarget(enShadowMap));

		renderContext.ClearRenderTargetView(*RenderTarget::GetRenderTarget(enShadowMap));

		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetRenderTarget(enShadowMap));




		renderContext.SetRenderMode(RenderContext::EnRender_Mode::enRenderMode_Normal);

		renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));

		renderContext.SetRenderTargetAndViewport(*RenderTarget::GetRenderTarget(enMainRT));

		renderContext.ClearRenderTargetView(*RenderTarget::GetRenderTarget(enMainRT));

		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		
		renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));

		{
			auto& luminanceRenderTarget = *RenderTarget::GetRenderTarget(enLuminanceRT);

			// �P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
			renderContext.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);

			// �����_�����O�^�[�Q�b�g��ݒ�
			renderContext.SetRenderTargetAndViewport(luminanceRenderTarget);

			// �����_�����O�^�[�Q�b�g���N���A
			renderContext.ClearRenderTargetView(luminanceRenderTarget);

			// �P�x���o���s��
			postEffect->GetLuminanceSprite().Draw(renderContext);

			// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
			renderContext.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
		}
		//�K�E�V�A���u���[��4����s����
		for (int i = 0; i < GAUSSIAN_BLUR_NUM; i++) {

			postEffect->GetGaussianBlurSprite(i).ExecuteOnGPU(renderContext, BLUR_POWER);
		}

		//4���̃{�P�摜���������ă��C�������_�����O�^�[�Q�b�g�ɉ��Z����
		renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));

		renderContext.SetRenderTargetAndViewport(*RenderTarget::GetRenderTarget(enMainRT));

		postEffect->GetFinalSprite().Draw(renderContext);

		renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetRenderTarget(enMainRT));
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		// ���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		m_copyToMainRenderTargetSprite.Draw(renderContext);

		//sprite.Update({ FRAME_BUFFER_W / -2.0f, FRAME_BUFFER_H / 2.0f,  0.0f }, g_quatIdentity, g_vec3One, { 0.0f, 1.0f });
		//sprite.Draw(renderContext);

		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();

	// python�̏I�������B
	FinalPython(program);

	return 0;
}

