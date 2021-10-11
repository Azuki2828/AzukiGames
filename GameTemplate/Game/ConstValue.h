#pragma once
#include "stdafx.h"


namespace nsMyGame {

	namespace nsLight {

		constexpr int c_maxDirectionLightNum = 4;	//�f�B���N�V�������C�g�̏����
		constexpr int c_maxPointLightNum = 100;		//�|�C���g���C�g�̏����
	}

	namespace nsFont {

		constexpr int c_maxTextSize = 256;		//�e�L�X�g�̏����
	}

	namespace nsPostEffect {

		constexpr const char* c_fxFilePathCopySprite = "Assets/shader/Sprite.fx";		//���C�������_�����O�^�[�Q�b�g�ɃR�s�[���鎞�Ɏg�p����V�F�[�_�[�̃t�@�C���p�X
		constexpr const char* c_fxFilePathGaussianBlur = "Assets/shader/gaussianBlur.fx" //�K�E�V�A���u���[�Ŏg�p����V�F�[�_�[�̃t�@�C���p�X

		constexpr int c_gaussianBlurNumWeight = 8;		//�K�E�V�A���u���[�̏d�݂̐�
	}
}


/**
 * @brief �D��x�BenPriority_Zeroth���ł���ɕ`�悳���B
*/
enum PriorityNum{
	enPriority_Zeroth,
	enPriority_First,
	enPriority_Second,
	enPriority_Third,
	enPriority_Fourth,
	enPriority_Fifth
};

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

	const Vector3 c_gravityScale = { 0.0f,-300.0f,0.0f };			//�W���̏d��

	const Vector3 c_cameraUp = { 0.0f,1.0f,0.0f };					//�J�����̕W���̏����

	const Vector2 c_renderTargetW1280H720 = { 1280.0f,720.0f };						//�����_�����O�^�[�Q�b�g�Ŏg�p���镝�ƍ���
	const Vector2 c_shadowMapWH = { 1024.0f,1024.0f };
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

	const Vector4 c_translucentValue_Half = { 1.0f,1.0f,1.0f,0.5f };			//������50%
	const Vector4 c_translucentValue_OneThird = { 1.0f,1.0f,1.0f,0.3f };	//������70%
	const Vector4 c_translucentValue_Max = { 1.0f,1.0f,1.0f,1.0f };			//������0%

	const float c_textShadowThickness = 1.0f;					//�e�L�X�g�̉e�i�g���j�̌���

	const Vector3 c_scaleValue_Half = { 0.5f,0.5f,0.5f };		//�g�嗦50%
	const Vector3 c_scaleValue_ATenth = { 0.1f,0.1f,0.1f };		//�g�嗦10%
	const Vector3 c_scaleValue_AFifth = { 0.2f,0.2f,0.2f };		//�g�嗦20%
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