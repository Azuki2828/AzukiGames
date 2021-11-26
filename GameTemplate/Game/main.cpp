#include "stdafx.h"
#include "system/system.h"
#include "enemy/GoteWinEnemy/GoteWinEnemy.h"
#include "enemy/FirstWinEnemy/FirstWinEnemy.h"
#include "player/Player.h"
#include "BackGround.h"
#include "MainCamera.h"
#include "Door.h"

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
#ifdef MY_DEBUG
		Py_SetPath(L"./Python37_64/DLLs;./Python37_64/Lib;./EnemyState;../x64/Debug/");
#else
		Py_SetPath(L"./Python37_64/DLLs;./Python37_64/Lib;./EnemyState;../x64/Release/");
#endif
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


		// python���������B
		wchar_t* program;
		InitPython(program);

		//////////////////////////////////////
		// �������珉�������s���R�[�h���L�q����B
		//////////////////////////////////////

		//�l�X�ȃC���X�^���X���쐬����B
		CGameObjectManager::CreateInstance();		//�Q�[���I�u�W�F�N�g�Ǘ��N���X
		CPhysicsWorld::CreateInstance();			//�������[���h
		nsLight::CLightManager::CreateInstance();	//���C�g�Ǘ��N���X
		CCamera::CreateLightCamera();				//���C�g�J����
		CRenderingEngine::CreateRenderingEngine();	//�����_�����O�G���W��
		EffectEngine::CreateInstance();				//�G�t�F�N�g�G���W��

		//���C���[�t���[���\����ON�ɂ���B
		//CPhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

		////////////////////////////////////////////////
		// ���������s���R�[�h�������̂͂����܂�
		////////////////////////////////////////////////
		auto& renderContext = g_graphicsEngine->GetRenderContext();
		
		// �Ƃ肠�����e�X�g�œG��ǉ��B
		auto fEnemy = NewGO<nsEnemy::CFirstWinEnemy>(0, c_classNameEnemy);
		fEnemy->SetPosition({ 500.0f,500.0f,500.0f });
		//NewGO<nsEnemy::CGoteWinEnemy>(0, "Enemy");
		
		NewGO<nsPlayer::CPlayer>(0, c_classNamePlayer);
		NewGO<CBackGround>(0,"backGround");
		NewGO<CMainCamera>(0);
		/*CSpriteRender* m_spriteRender = NewGO<CSpriteRender>(0);
		m_spriteRender->Init("Assets/image/beer.dds", 1280.0f, 720.0f);
		m_spriteRender->SetPosition({ -400.0f,-200.0f,0.0f });
		m_spriteRender->SetScale({ 0.2f,0.2f,0.2f });
		m_spriteRender->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });*/

		// ��������Q�[�����[�v�B
		while (DispatchWindowMessage())
		{
			//�����_�����O�J�n�B
			g_engine->BeginFrame();

			//////////////////////////////////////
			//��������G��`���R�[�h���L�q����B
			//////////////////////////////////////

			//�Q�[���I�u�W�F�N�g���X�V�B
			CGameObjectManager::GetInstance()->ExecuteUpdate();
			EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());

			//���C�g���X�V�B
			nsLight::CLightManager::GetInstance()->Update();

			//�`��B
			CRenderingEngine::GetInstance()->Render();
			////////////////////////////////////////////////
			//�G��`���R�[�h�������̂͂����܂ŁI�I�I
			////////////////////////////////////////////////

			//�����_�����O�I���B
			g_engine->EndFrame();
		}

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
		CGameObjectManager::DeleteInstance();

		// python�̏I�������B
		FinalPython(program);

		return 0;
	}
}

