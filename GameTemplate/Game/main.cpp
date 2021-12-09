#include "stdafx.h"
#include "system/system.h"
#include "Game.h"

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
		
		
		
		NewGO<CGameMain>(enPriority_Zeroth);

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

