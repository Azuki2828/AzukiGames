#include "stdafx.h"
#include "system/system.h"
#include "enemy/firstWinEnemy/FirstWinEnemy.h"
#include "player/Player.h"
#include "BackGround.h"
#include "MainCamera.h"

namespace nsMyGame {

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
		CGameObjectManager::CreateInstance();
		CPhysicsWorld::CreateInstance();
		nsLight::CLightManager::CreateInstance();
		CCamera::CreateLightCamera();
		CRenderingEngine::CreateRenderingEngine();

		CRenderingEngine::GetInstance()->Init();

		//���C���[�t���[���\����ON�ɂ���B
		//CPhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

		//////////////////////////////////////
		// ���������s���R�[�h�������̂͂����܂�
		//////////////////////////////////////
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		// �Ƃ肠�����e�X�g�œG��ǉ��B
		NewGO<nsEnemy::CFirstWinEnemy>(0, "Enemy");

		NewGO<nsPlayer::CPlayer>(0, "player");
		NewGO<CBackGround>(0);
		NewGO<CMainCamera>(0);
		/*CSpriteRender* m_spriteRender = NewGO<CSpriteRender>(0);
		m_spriteRender->Init("Assets/image/beer.dds", 1280.0f, 720.0f);
		m_spriteRender->SetPosition({ -400.0f,-200.0f,0.0f });
		m_spriteRender->SetScale({ 0.2f,0.2f,0.2f });
		m_spriteRender->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });*/

		nsLight::CDirectionLight* dirLight = NewGO<nsLight::CDirectionLight>(0);
		dirLight->SetLigDirection({ 1.0f,-1.0f,-1.0f });
		dirLight->SetLigColor({ 0.3f,0.3f,0.3f });

		nsLight::CPointLight* poiLight = NewGO<nsLight::CPointLight>(0);
		poiLight->SetPosition({ 100.0f,100.0f,0.0f });
		poiLight->SetColor({ 5.0f,0.0f,0.0f });
		poiLight->SetRange(200.0f);
		poiLight->SetAffectPowParam(3.0f);

		nsLight::CPointLight* poiLight2 = NewGO<nsLight::CPointLight>(0);
		poiLight2->SetPosition({ -50.0f,100.0f,0.0f });
		poiLight2->SetColor({ 0.0f,0.0f,5.0f });
		poiLight2->SetRange(200.0f);
		poiLight2->SetAffectPowParam(3.0f);

		// ��������Q�[�����[�v�B
		while (DispatchWindowMessage())
		{
			//�����_�����O�J�n�B
			g_engine->BeginFrame();


			





			//////////////////////////////////////
			//��������G��`���R�[�h���L�q����B
			//////////////////////////////////////

			//sprite[1].Update(pos[1], Quaternion::Identity, Vector3::One);

			CGameObjectManager::GetInstance()->ExecuteUpdate();
			nsLight::CLightManager::GetInstance()->Update();

			CRenderingEngine::GetInstance()->Render();
			//////////////////////////////////////
			//�G��`���R�[�h�������̂͂����܂ŁI�I�I
			//////////////////////////////////////

			g_engine->EndFrame();
		}
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
		CGameObjectManager::DeleteInstance();

		// python�̏I�������B
		FinalPython(program);

		return 0;
	}
}

