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

	/*------�N���X�̖��O------*/
	constexpr const char* c_classNamePlayer = "player";								//�v���C���[�N���X�̖��O
	constexpr const char* c_classNameEnemy = "enemy";								//�G�N���X�̖��O
	constexpr const char* c_classNameAppearSprite = "appearSprite";					//�E�B���h�E�N���X�̖��O
	constexpr const char* c_classNameBackGround = "backGround";						//�w�i�N���X�̖��O
	constexpr const char* c_playerAttackCollisionName = "playerAttackCollision";	//�v���C���[�̍U������̖��O
	constexpr const char* c_enemyAttackCollisionName = "enemyAttackCollision";		//�G�̍U������̖��O
	/*------------------------*/

	constexpr const char* c_entryPointVSMain = "VSMain";						//���_�V�F�[�_�[�̃G���g���[�|�C���g
	constexpr const char* c_entryPointVSSkinMain = "VSSkinMain";				//�X�L������̒��_�V�F�[�_�[�̃G���g���[�|�C���g
	constexpr const char* c_fxFilePath_Model = "Assets/shader/model.fx";		//G-Buffer�쐬�Ɏg���V�F�[�_�[�̃t�@�C���p�X
	constexpr float c_attackCollisionActiveTime = 0.2f;							//�U���p�����蔻��̗L������

	constexpr const char* c_filePathYouDiedSprite = "Assets/image/youDied2.dds";	//���S�X�v���C�g�̃t�@�C���p�X
	const CVector2 c_spriteYouDiedWH = { 1740.0f, 180.0f };							//���S�X�v���C�g�̕��ƍ���
	const CVector3 c_spriteSizeYouDied = { 0.8f,0.8f,0.8f };						//���S�X�v���C�g�̊g�嗦

	constexpr const char* c_filePathTkmDoor = "Assets/modelData/backGround/door.tkm";	//�h�A��tkm�t�@�C���p�X
	constexpr float c_distanceForOpenDoor = 200.0f;										//�h�A���J����̂ɕK�v�ȋ���
	constexpr int c_openDoorRotValue = 90;												//�h�A���J�����Ƃ��̉�]�p�x
	constexpr int c_openDoorRotNum = 1;													//�h�A���J�����Ƃ��ɉ��x����]�����邩
	constexpr const char* c_filePathTextSprite = "Assets/image/text.dds";				//�e�L�X�g�X�v���C�g�̃t�@�C���p�X
	const CVector3 c_textSpritePosition = { 0.0f,-250.0f, 0.0f };						//�e�L�X�g�̃X�v���C�g�̍��W
	const CVector3 c_textSpriteSize = { 0.45f, 0.1f, 0.2f };							//�e�L�X�g�̃X�v���C�g�̊g�嗦
	const CVector2 c_textSpriteWH = { 1280.0f,720.0f };									//�e�L�X�g�̃X�v���C�g�̕��ƍ���

	const CVector2 c_textPosition = { -50.0f,-240.0f };									//�e�L�X�g�̍��W
	const CVector2 c_textPosition_getKey = { -80.0f,-240.0f };							//[Key get.]�e�L�X�g�̍��W
	constexpr float c_textSize = 0.5f;													//�e�L�X�g�̊g�嗦


	constexpr const char16_t* c_filePathFireEffect = u"Assets/effect/fire.efk";			//���G�t�F�N�g�̃t�@�C���p�X
	const CVector3 c_fireEffectScale = { 10.0f,10.0f,10.0f };							//���G�t�F�N�g�̊g�嗦

	constexpr UINT c_frameBufferWidth = 1280;		//�t���[���o�b�t�@�̕�
	constexpr UINT c_frameBufferHeight = 720;		//�t���[���o�b�t�@�̍���
	constexpr int c_tileWidth = 16;					//TBR�ŕ�������^�C���̉��̐�
	constexpr int c_tileHeight = 16;				//TBR�ŕ�������^�C���̏c�̐�

	const CVector3 c_firePointLightColor = { 10.0f,5.0f,5.0f };		//���p�̃|�C���g���C�g�̃J���[
	constexpr float c_firePointLightRange = 600.0f;					//���p�̃|�C���g���C�g�̉e���͈�
	constexpr float c_firePointLightAffectParam = 5.5f;				//���p�̃|�C���g���C�g�̌�����

	const CVector3 c_addFireEffectPosition = { 0.0f,5.0f,35.0f };	//���G�t�F�N�g�̍��W�����̂��߂ɉ��Z�������

	namespace nsPlayer {

		constexpr const char* c_filePathTkmPlayer = "Assets/modelData/player2.tkm";		//�v���C���[��tkm�t�@�C���p�X
		constexpr const char* c_filePathTksPlayer = "Assets/modelData/player2.tks";		//�v���C���[��tks�t�@�C���p�X
		constexpr const float c_animationInterpolateTime = 0.6f;						//�A�j���[�V�����̕�Ԏ���
		constexpr float c_rollingCoolTime = 1.2f;										//���[�����O���̃N�[���^�C��
		constexpr float c_attackCoolTime = 0.8f;										//�ʏ�U�����̃N�[���^�C��
		constexpr float c_threeComboCoolTime = 3.0f;									//3�A���U�����̃N�[���^�C��
		const CVector3 c_playerStartPosition = { 0.0f,200.0f,0.0f };					//�J�n���̃v���C���[�̍��W

		const CVector3 c_attackTriggerBoxSize = { 150.0f,150.0f,100.0f };				//�v���C���[�U�����̃g���K�[�{�b�N�X�̃T�C�Y
		constexpr float c_attackTriggerBoxMul = 80.0f;									//�v���C���[�U�����̃g���K�[�{�b�N�X�̑O�����ւ̏�Z�l
		constexpr float c_attackTriggerBoxAddYPos = 50.0f;								//�v���C���[�U�����̃g���K�[�{�b�N�X��Y�����ւ̉��Z�l

		//�v���C���[�̃X�e�[�g
		enum EnPlayerState {
			enState_Idle,
			enState_Walk,
			enState_Run,
			enState_Attack,
			enState_AttackBreak,
			enState_Damage,
			enState_Rolling,
			enState_ThreeCombo,
			enState_Guard,
			enState_GuardSuccess,
			enState_Death,

			enState_Num
		};
	}

	namespace nsEnemy {

		constexpr const char* c_filePathTkmEnemy = "Assets/modelData/player2.tkm";		//�G��tkm�t�@�C���p�X
		constexpr const char* c_filePathTksEnemy = "Assets/modelData/player2.tks";		//�G��tks�t�@�C���p�X

		constexpr float c_threeComboCoolTime = 3.0f;									//3�A���U�����̃N�[���^�C��
		const CVector3 c_attackTriggerBoxSize = { 15.0f, 110.0f, 15.0f };				//�G�U�����̃g���K�[�{�b�N�X�̃T�C�Y
		constexpr float c_attackTriggerBoxMul = 80.0f;									//�G�U�����̃g���K�[�{�b�N�X�̑O�����ւ̏�Z�l
		constexpr float c_attackTriggerBoxAddYPos = 50.0f;								//�G�U�����̃g���K�[�{�b�N�X��Y�����ւ̉��Z�l
	}

	namespace nsItem {

		constexpr float c_needToDistanceForGetItem = 100.0f;							//�A�C�e�����������̂ɕK�v�ȋ���
		constexpr const char16_t* c_itemEffectFilePath = u"Assets/effect/item.efk";		//�A�C�e���G�t�F�N�g�̃t�@�C���p�X
		const CVector3 c_itemEffectSize = { 10.0f,10.0f,10.0f };						//�A�C�e���G�t�F�N�g�̊g�嗦
		constexpr float c_itemEffectReplayTime = 1.0f;									//�G�t�F�N�g���Đ�������Ԋu


	}

	namespace nsLight {

		constexpr int c_maxDirectionLightNum = 4;	//�f�B���N�V�������C�g�̏����
		constexpr int c_maxPointLightNum = 1000;	//�|�C���g���C�g�̏����
		constexpr int c_tileNum = 3600;				//�^�C���̐��B
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
	const CVector2 c_shadowMapWH = { 4096.0f,4096.0f };									//�V���h�E�}�b�v�̕��ƍ���
	const int c_mipLevel1 = 1;															//�����_�����O�^�[�Q�b�g�Ŏg�p����~�b�v�}�b�v���x��
	const int c_renderArraySize1 = 1;													//�����_�����O�^�[�Q�b�g�Ŏg�p����e�N�X�`���z��̃T�C�Y
	const int c_gaussianBlurNum = 4;													//�K�E�V�A���u���[���������
	const int c_blurPower = 10;															//�u���[�̋���
	const char* c_fxFilePath_DeferredLighting = "Assets/shader/deferredLighting.fx";	//�f�B�t�@�[�h���C�e�B���O�Ɏg���V�F�[�_�[�̃t�@�C���p�X
	const char* c_fxFilePath_Sprite = "Assets/shader/sprite.fx";						//�X�v���C�g�V�F�[�_�[�̃t�@�C���p�X
	const char* c_fxFilePath_ShadowMap = "Assets/shader/sampleDrawShadowMap.fx";		//�V���h�E�}�b�v�`��Ɏg���V�F�[�_�[�̃t�@�C���p�X

	const int c_initializeTime = 0;
	const int c_restInitialTime = 0;		//�X�s�����b�N���̑҂��^�C���̏�������
	const int c_spinLockCriteria = 16;		//�X�s�����b�N���̊�ƂȂ鎞��

	const CVector4 c_translucentValue_Half = { 1.0f,1.0f,1.0f,0.5f };		//������50%
	const CVector4 c_translucentValue_OneThird = { 1.0f,1.0f,1.0f,0.3f };	//������70%
	const CVector4 c_translucentValue_Zero = { 1.0f,1.0f,1.0f,0.0f };		//������100%
	const CVector4 c_translucentValue_Max = { 1.0f,1.0f,1.0f,1.0f };		//������0%

	const float c_textShadowThickness = 1.0f;								//�e�L�X�g�̉e�i�g���j�̌���

	const CVector3 c_scaleValue_Half = { 0.5f,0.5f,0.5f };					//�g�嗦50%
	const CVector3 c_scaleValue_ATenth = { 0.1f,0.1f,0.1f };				//�g�嗦10%
	const CVector3 c_scaleValue_AFifth = { 0.2f,0.2f,0.2f };				//�g�嗦20%
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