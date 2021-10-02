#pragma once
#include "stdafx.h"

//////////////////////////////////////////////////
///�@�Q�ȏ�̃N���X�Ŏg���萔���܂Ƃ߂Ă���@///
//////////////////////////////////////////////////



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

	const int PAD_0 = 0;
	const int NAME_SIZE = 256;										//���O�̍ő�̃T�C�Y
	const int TEXT_SIZE = 64;										//�e�L�X�g�̕W���T�C�Y
	const float TEXT_BIT_SIZE = 16.0f;								//�e�L�X�g�̃r�b�g�T�C�Y

	const Vector3 GRAVITY_VALUE = { 0.0f,-300.0f,0.0f };			//�W���̏d��

	const Vector3 CAMERA_UP = { 0.0f,1.0f,0.0f };					//�J�����̕W���̏����

	const Vector2 RENDER_TARGET_W1280H720 = { 1280.0f,720.0f };						//�����_�����O�^�[�Q�b�g�Ŏg�p���镝�ƍ���
	const int MIP_LEVEL1 = 1;														//�����_�����O�^�[�Q�b�g�Ŏg�p����~�b�v�}�b�v���x��
	const int RENDER_ARRAY_SIZE1 = 1;												//�����_�����O�^�[�Q�b�g�Ŏg�p����e�N�X�`���z��̃T�C�Y
	const int GAUSSIAN_BLUR_NUM = 4;												//�K�E�V�A���u���[���������
	const int BLUR_POWER = 10;														//�u���[�̋���
	const char* SPRITE_SHADER_FILE_PATH = "Assets/shader/defferdLighting.fx";		//�X�v���C�g�V�F�[�_�[�̃t�@�C���p�X
	const char* SPRITE_SHADER_MONOCHROME_FILE_PATH = "Assets/shader/sample2D.fx";	//���m�N���\���p�̃V�F�[�_�[�̃t�@�C���p�X
	const char* HUD_FILE_PATH = "Assets/shader/sprite.fx";
	const char* FX_FILE_PATH_SHADOW_MAP = "Assets/shader/sampleDrawShadowMap.fx";

	const int INITIALIZE_TIME = 0;
	const int REST_INITIAL_TIME = 0;		//�X�s�����b�N���̑҂��^�C���̏�������
	const int SPIN_LOCK_CRITERIA = 16;		//�X�s�����b�N���̊�ƂȂ鎞��

	const Vector4 TRANSLUCENT_VALUE_HALF = { 1.0f,1.0f,1.0f,0.5f };			//������50%
	const Vector4 TRANSLUCENT_VALUE_ONE_THIRD = { 1.0f,1.0f,1.0f,0.3f };	//������70%
	const Vector4 TRANSLUCENT_VALUE_MAX = { 1.0f,1.0f,1.0f,1.0f };			//������0%

	const float TEXT_SHADOW_THICKNESS = 1.0f;					//�e�L�X�g�̉e�i�g���j�̌���

	const Vector3 SCALE_VALUE_HALF = { 0.5f,0.5f,0.5f };		//�g�嗦50%
	const Vector3 SCALE_VALUE_A_TENTH = { 0.1f,0.1f,0.1f };		//�g�嗦10%
	const Vector3 SCALE_VALUE_A_FIFTH = { 0.2f,0.2f,0.2f };		//�g�嗦20%
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