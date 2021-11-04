#pragma once
#include "stdafx.h"


namespace nsMyGame {

	//�D��x�BenPriority_Zeroth���ł���ɕ`�悳���B
	enum PriorityNum {
		enPriority_Zeroth,
		enPriority_First,
		enPriority_Second,
		enPriority_Third,
		enPriority_Fourth,
		enPriority_Fifth
	};

	constexpr const char* c_entryPointVSMain = "VSMain";
	constexpr const char* c_entryPointVSSkinMain = "VSSkinMain";
	constexpr const char* c_fxFilePath_Model = "Assets/shader/model.fx";

	namespace nsPlayer {

		constexpr const char* c_filePathTkmPlayer = "Assets/modelData/player.tkm";		//�v���C���[��tkm�t�@�C���p�X
		constexpr const char* c_filePathTksPlayer = "Assets/modelData/player.tks";		//�v���C���[��tks�t�@�C���p�X
		const CVector3 c_addLightCameraPos = { 0.0f,300.0f,300.0f };					//�v���C���[�p�̃��C�g�J�����ɉ��Z������W
		constexpr const float c_animationInterpolateTime = 0.6f;						//�A�j���[�V�����̕�Ԏ���
		constexpr float c_rollingCoolTime = 1.2f;										//���[�����O���̃N�[���^�C��
		constexpr float c_threeComboCoolTime = 3.0f;									//3�A���U�����̃N�[���^�C��

		const CVector3 c_attackTriggerBoxSize = { 150.0f,150.0f,100.0f };				//�v���C���[�U�����̃g���K�[�{�b�N�X�̃T�C�Y
		constexpr float c_attackTriggerBoxMul = 80.0f;									//�v���C���[�U�����̃g���K�[�{�b�N�X�̑O�����ւ̏�Z�l
		constexpr float c_attackTriggerBoxAddYPos = 50.0f;								//�v���C���[�U�����̃g���K�[�{�b�N�X��Y�����ւ̉��Z�l

		//�v���C���[�̃X�e�[�g
		enum EnPlayerState {
			enState_Idle,
			enState_Walk,
			enState_Run,
			enState_Attack,
			enState_Damage,
			enState_Rolling,
			enState_ThreeCombo,

			enState_Num
		};
	}

	namespace nsEnemy {

		constexpr const char* c_filePathTkmEnemy = "Assets/modelData/player.tkm";		//�G��tkm�t�@�C���p�X
		constexpr const char* c_filePathTksEnemy = "Assets/modelData/player.tks";		//�G��tks�t�@�C���p�X

		constexpr float c_threeComboCoolTime = 3.0f;									//3�A���U�����̃N�[���^�C��
		const CVector3 c_attackTriggerBoxSize = { 150.0f,150.0f,100.0f };				//�G�U�����̃g���K�[�{�b�N�X�̃T�C�Y
		constexpr float c_attackTriggerBoxMul = 80.0f;									//�G�U�����̃g���K�[�{�b�N�X�̑O�����ւ̏�Z�l
		constexpr float c_attackTriggerBoxAddYPos = 50.0f;								//�G�U�����̃g���K�[�{�b�N�X��Y�����ւ̉��Z�l
	}

	namespace nsLight {

		constexpr int c_maxDirectionLightNum = 4;	//�f�B���N�V�������C�g�̏����
		constexpr int c_maxPointLightNum = 100;		//�|�C���g���C�g�̏����
	}


	namespace nsFont {

		constexpr int c_maxTextSize = 256;		//�e�L�X�g�̏����
	}


	namespace nsPostEffect {


		/*------PostEffectComponentBase------*/
		constexpr const char* c_fxFilePathCopySprite = "Assets/shader/Sprite.fx";			//���C�������_�����O�^�[�Q�b�g�ɃR�s�[���鎞�Ɏg�p����V�F�[�_�[�̃t�@�C���p�X
		/*-----------------------------------*/


		/*------GaussianBlur------*/
		constexpr const char* c_fxFilePathGaussianBlur = "Assets/shader/gaussianBlur.fx";	//�K�E�V�A���u���[�Ŏg�p����V�F�[�_�[�̃t�@�C���p�X
		constexpr const char* c_vsEntryPointFuncXBlur = "VSXBlur";							//���u���[�p�̃X�v���C�g�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const char* c_vsEntryPointFuncYBlur = "VSYBlur";							//�c�u���[�p�̃X�v���C�g�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const char* c_psEntryPointFuncBlur = "PSBlur";							//�u���[�p�̃X�v���C�g�̃s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const int c_gaussianBlurNumWeight = 8;									//�K�E�V�A���u���[�̏d�݂̐�
		/*------------------------*/


		/*------Bloom------*/
		constexpr const int c_gaussianBlurNum = 4;												//�K�E�V�A���u���[�̐�
		constexpr const char* c_fxFilePathBloom = "Assets/shader/bloom.fx";						//�u���[���p�̃V�F�[�_�[�̃t�@�C���p�X
		constexpr const char* c_vsEntryPointFuncBloom = "VSMain";								//�u���[���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const char* c_psEntryPointFuncSamplingLuminance = "PSSamplingLuminance";		//�P�x���o�p�̃s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const char* c_psEntryPointFuncBloomFinal = "PSBloomFinal";					//�u���[���ŏI�̃s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
		/*-----------------*/


		/*------FXAA------*/
		constexpr const char* c_fxFilePathFXAA = "Assets/shader/fxaa.fx";	//FXAA�Ŏg�p����V�F�[�_�[�̃t�@�C���p�X
		constexpr const char* c_vsEntryPointFuncFXAA = "VSMain";			//FXAA�p�̃X�v���C�g�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const char* c_psEntryPointFuncFXAA = "PSMain";			//FXAA�p�̃X�v���C�g�̃s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
		/*----------------*/
	}
}




/**
 * @brief �T�E���h���X�g
*/
enum SoundList {

	enSound_Num
};

/**
 * @brief HUD�ɓo�^����Ă���X�v���C�g
*/
enum HUDList {

	enSprite_HUDNum
};

namespace {

	const int c_pad0 = 0;											//0�Ԗڂ̃p�b�h
	const int c_nameSize = 256;										//���O�̍ő�̃T�C�Y
	const int c_textSize = 64;										//�e�L�X�g�̕W���T�C�Y
	const float c_textBitSize = 16.0f;								//�e�L�X�g�̃r�b�g�T�C�Y

	const CVector3 c_gravityScale = { 0.0f,-300.0f,0.0f };			//�W���̏d��

	const CVector3 c_cameraUp = { 0.0f,1.0f,0.0f };					//�J�����̕W���̏����

	const CVector2 c_renderTargetW1280H720 = { 1280.0f,720.0f };						//�����_�����O�^�[�Q�b�g�Ŏg�p���镝�ƍ���
	const CVector2 c_shadowMapWH = { 1024.0f,1024.0f };
	const int c_mipLevel1 = 1;														//�����_�����O�^�[�Q�b�g�Ŏg�p����~�b�v�}�b�v���x��
	const int c_renderArraySize1 = 1;												//�����_�����O�^�[�Q�b�g�Ŏg�p����e�N�X�`���z��̃T�C�Y
	const int c_gaussianBlurNum = 4;												//�K�E�V�A���u���[���������
	const int c_blurPower = 10;														//�u���[�̋���
	const char* c_fxFilePath_DeferredLighting = "Assets/shader/deferredLighting.fx";//�X�v���C�g�V�F�[�_�[�̃t�@�C���p�X
	const char* c_fxFilePath_Sprite = "Assets/shader/sprite.fx";
	const char* c_fxFilePath_ShadowMap = "Assets/shader/sampleDrawShadowMap.fx";

	const int c_initializeTime = 0;
	const int c_restInitialTime = 0;		//�X�s�����b�N���̑҂��^�C���̏�������
	const int c_spinLockCriteria = 16;		//�X�s�����b�N���̊�ƂȂ鎞��

	const CVector4 c_translucentValue_Half = { 1.0f,1.0f,1.0f,0.5f };			//������50%
	const CVector4 c_translucentValue_OneThird = { 1.0f,1.0f,1.0f,0.3f };	//������70%
	const CVector4 c_translucentValue_Max = { 1.0f,1.0f,1.0f,1.0f };			//������0%

	const float c_textShadowThickness = 1.0f;					//�e�L�X�g�̉e�i�g���j�̌���

	const CVector3 c_scaleValue_Half = { 0.5f,0.5f,0.5f };		//�g�嗦50%
	const CVector3 c_scaleValue_ATenth = { 0.1f,0.1f,0.1f };		//�g�嗦10%
	const CVector3 c_scaleValue_AFifth = { 0.2f,0.2f,0.2f };		//�g�嗦20%
}

/**
 * @brief �����̌������擾����֐�
 * @tparam Num �e���v���[�g
 * @param num �������m���߂�������
 * @return ����
*/
template<typename Num>
int GetDigit(Num num) {

	int digit = 0;
	while (num >= 1) {
		num /= 10;
		digit++;
	}

	return digit;
}