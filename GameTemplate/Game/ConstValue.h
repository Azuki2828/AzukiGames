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
	constexpr const char* c_classNameGameMain = "gameMain";							//�Q�[�����C���N���X�̖��O
	constexpr const char* c_classNamePlayer = "player";								//�v���C���[�N���X�̖��O
	constexpr const char* c_classNameEnemy = "enemy";								//�G�N���X�̖��O
	constexpr const char* c_classNameBoss = "boss";									//�{�X�N���X�̖��O
	constexpr const char* c_classNameAppearSprite = "appearSprite";					//�E�B���h�E�N���X�̖��O
	constexpr const char* c_classNameBackGround = "backGround";						//�w�i�N���X�̖��O
	constexpr const char* c_classNamePlayerAttackCollision = "playerAttackCollision";	//�v���C���[�̍U������̖��O
	constexpr const char* c_classnameEnemyAttackCollision = "enemyAttackCollision";		//�G�̍U������̖��O
	constexpr const char* c_classNameFade = "fade";									//�t�F�[�h�N���X�̖��O
	constexpr const char* c_classNameGameHUD = "gameHUD";							//HUD�N���X�̖��O
	constexpr const char* c_classNameMainCamera = "mainCamera";					//�J�����N���X�̖��O
	/*------------------------*/

	//�T�E���h���X�g
	enum EnSoundList {
		enBGM_GameMain,
		enBGM_Boss,
		enSE_Kill,
		enSE_Guard,
		enSE_Rolling,
		enSE_Walk,
		enSE_Death_1,
		enSE_Death_2,
		enSE_GameOver,
		enSE_Select,
		enSE_Scream,
		enSE_Impact,
		enSE_Footsteps,
		enSE_Scratch,
		enSE_DeathVoice,
		enSE_GetItem,
		enSE_DoorOpen,
		enSE_Torch,

		enSound_Num
	};

	/*------�T�E���h�̃t�@�C���p�X------*/
	constexpr const wchar_t* c_filePathBGM_Boss = L"Assets/sound/BGM_Boss.wav";			//�{�X��BGM
	constexpr const wchar_t* c_filePathBGM_GameMain = L"Assets/sound/BGM_GameMain.wav";	//�Q�[����BGM
	constexpr const wchar_t* c_filePathSE_Kill = L"Assets/sound/SE_Kill.wav";			//�a��SE
	constexpr const wchar_t* c_filePathSE_Guard = L"Assets/sound/SE_Guard.wav";			//�K�[�hSE
	constexpr const wchar_t* c_filePathSE_Rolling = L"Assets/sound/SE_Rolling.wav";		//���[�����OSE
	constexpr const wchar_t* c_filePathSE_Walk = L"Assets/sound/SE_Walk.wav";			//���sSE
	constexpr const wchar_t* c_filePathSE_Death_1 = L"Assets/sound/SE_Death_1.wav";		//�|���SE
	constexpr const wchar_t* c_filePathSE_Death_2 = L"Assets/sound/SE_Death_2.wav";		//�|���SE2
	constexpr const wchar_t* c_filePathSE_GameOver = L"Assets/sound/SE_GameOver.wav";	//�Q�[���I�[�o�[SE
	constexpr const wchar_t* c_filePathSE_Select = L"Assets/sound/SE_Select.wav";		//�I��SE
	constexpr const wchar_t* c_filePathSE_Scream = L"Assets/sound/SE_Roar.wav";			//���KSE
	constexpr const wchar_t* c_filePathSE_Impact = L"Assets/sound/SE_Impact.wav";		//�Ռ�SE
	constexpr const wchar_t* c_filePathSE_Footsteps = L"Assets/sound/SE_Footsteps.wav";	//�{�X����SE
	constexpr const wchar_t* c_filePathSE_Scratch = L"Assets/sound/SE_Scratch.wav";		//�����~��SE
	constexpr const wchar_t* c_filePathSE_DeathVoice = L"Assets/sound/SE_DeathVoice.wav";	//���񂾂Ƃ��̃{�C�XSE
	constexpr const wchar_t* c_filePathSE_GetItem = L"Assets/sound/SE_GetItem.wav";		//�A�C�e���擾SE
	constexpr const wchar_t* c_filePathSE_DoorOpen = L"Assets/sound/SE_DoorOpen.wav";	//�h�A�J��SE
	constexpr const wchar_t* c_filePathSE_Torch = L"Assets/sound/SE_Torch.wav";			//����SE
	/*----------------------------------*/

	constexpr const char* c_entryPointVSMain = "VSMain";						//���_�V�F�[�_�[�̃G���g���[�|�C���g
	constexpr const char* c_entryPointVSSkinMain = "VSSkinMain";				//�X�L������̒��_�V�F�[�_�[�̃G���g���[�|�C���g
	constexpr const char* c_fxFilePath_Model = "Assets/shader/model.fx";		//G-Buffer�쐬�Ɏg���V�F�[�_�[�̃t�@�C���p�X
	constexpr float c_attackCollisionActiveTime = 0.2f;							//�U���p�����蔻��̗L������

	constexpr const char* c_filePathYouDiedSprite = "Assets/image/youDied2.dds";	//���S�X�v���C�g�̃t�@�C���p�X
	constexpr const char* c_filePathGameClearSprite = "Assets/image/Victory.dds";	//�Q�[���N���A�X�v���C�g�̃t�@�C���p�X
	const CVector2 c_spriteYouDiedWH = { 1740.0f, 180.0f };							//���S�X�v���C�g�̕��ƍ���
	const CVector3 c_spriteSizeYouDied = { 0.8f,0.8f,0.8f };						//���S�X�v���C�g�̊g�嗦

	constexpr const char* c_filePathFadeSprite = "Assets/image/fade.dds";			//�t�F�[�h�摜�̃t�@�C���p�X
	constexpr const char* c_filePathNewGameSprite = "Assets/image/NEWGAME.dds";		//NEW GAME�e�L�X�g�摜�̃t�@�C���p�X
	constexpr const char* c_filePathTextBackSprite = "Assets/image/TextBack.dds";	//�e�L�X�g�̌��ɔz�u����摜�̃t�@�C���p�X

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

	const CVector2 c_hpBarSize = { 400.0f, 25.0f };		//HP�o�[�̉𑜓x
	const CVector3 c_hpBarPosition = { -570.0f,300.0f,0.0f };		//HP�o�[�̍��W
	const CVector3 c_bossHpBarPosition = { -400.0f,-300.0f,0.0f };		//�{�X��HP�o�[�̍��W

	const CVector4 c_bossTextColor = { 0.8f,0.8f,0.8f,1.0f };	//�{�X�̖��O�̃J���[
	const float c_bossTextScale = 0.5f;		//�{�X�̖��O�̊g�嗦
	const CVector2 c_bossTextPosition = { -400.0f,-250.0f };	//�{�X�̖��O�̍��W

	constexpr float c_textDisappearTime = 3.0f;		//�m�F�e�L�X�g�������n�߂�܂ł̎���

	constexpr UINT c_frameBufferWidth = 1280;		//�t���[���o�b�t�@�̕�
	constexpr UINT c_frameBufferHeight = 720;		//�t���[���o�b�t�@�̍���
	constexpr int c_tileWidth = 16;					//TBR�ŕ�������^�C���̉��̐�
	constexpr int c_tileHeight = 16;				//TBR�ŕ�������^�C���̏c�̐�

	const CVector3 c_firePointLightColor = { 10.0f,5.0f,5.0f };		//���p�̃|�C���g���C�g�̃J���[
	constexpr float c_firePointLightRange = 600.0f;					//���p�̃|�C���g���C�g�̉e���͈�
	constexpr float c_firePointLightAffectParam = 5.5f;				//���p�̃|�C���g���C�g�̌�����

	const CVector3 c_addFireEffectPosition = { 0.0f,5.0f,35.0f };	//���G�t�F�N�g�̍��W�����̂��߂ɉ��Z�������

	constexpr float c_playerPointLightRange = 300.0f;		//�v���C���[���S�̃|�C���g���C�g�̉e���͈�
	constexpr float c_playerPointLightAffectPowParam = 2.5f;		//�v���C���[���S�̃|�C���g���C�g�̌�����
	constexpr float c_playerPointLightAddParam = 130.0f;			//�v���C���[���S�̃|�C���g���C�g�̉��Z���W
	constexpr float c_fireEffectLoopTime = 1.0f;					//�����̉��G�t�F�N�g�̃��[�v�܂ł̎���

	const CVector3 c_noticePlayerTriggerBoxSize = { 1300.0f,3000.0f,1300.0f };	//�{�X���o�ꂷ�邽�߂̃g���K�[�{�b�N�X�̃T�C�Y

	constexpr const char* c_filePathTitleSprite = "Assets/image/title.dds";	//�^�C�g���摜�̃t�@�C���p�X

	namespace nsPlayer {

		constexpr const char* c_filePathTkmPlayer = "Assets/modelData/player3.tkm";		//�v���C���[��tkm�t�@�C���p�X
		constexpr const char* c_filePathTksPlayer = "Assets/modelData/player3.tks";		//�v���C���[��tks�t�@�C���p�X
		constexpr const float c_animationInterpolateTime = 0.6f;						//�A�j���[�V�����̕�Ԏ���
		constexpr float c_rollingCoolTime = 1.2f;										//���[�����O���̃N�[���^�C��
		constexpr float c_attackCoolTime = 0.8f;										//�ʏ�U�����̃N�[���^�C��
		constexpr float c_threeComboCoolTime = 3.0f;									//3�A���U�����̃N�[���^�C��
		const CVector3 c_playerStartPosition = { 0.0f,0.0f,0.0f };					//�J�n���̃v���C���[�̍��W

		constexpr const int c_playerMaxHP = 100;									//�v���C���[�̍ő�HP
		const CVector3 c_attackTriggerBoxSize = { 15.0f, 110.0f, 15.0f };				//�v���C���[�U�����̃g���K�[�{�b�N�X�̃T�C�Y
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
			enState_Guard,
			enState_GuardSuccess,
			enState_Death,

			enState_Num
		};
	}

	namespace nsEnemy {

		constexpr const char* c_filePathTkmEnemy = "Assets/modelData/player2.tkm";		//�G��tkm�t�@�C���p�X
		constexpr const char* c_filePathTksEnemy = "Assets/modelData/player2.tks";		//�G��tks�t�@�C���p�X
		constexpr const char* c_filePathTkmBoss = "Assets/modelData/boss.tkm";			//�{�X��tkm�t�@�C���p�X
		constexpr const char* c_filePathTksBoss = "Assets/modelData/boss.tks";			//�{�X��tks�t�@�C���p�X

		constexpr const int c_bossMaxHP = 100;											//�{�X�̍ő�HP
		constexpr float c_threeComboCoolTime = 3.0f;									//3�A���U�����̃N�[���^�C��
		const CVector3 c_attackTriggerBoxSize = { 15.0f, 110.0f, 15.0f };				//�G�U�����̃g���K�[�{�b�N�X�̃T�C�Y
		const CVector3 c_bossAttackTriggerBoxSize = { 145.0f, 90.0f, 90.0f };			//�{�X�U�����̃g���K�[�{�b�N�X�̃T�C�Y
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

	const float c_appearSpriteTranslucent = 5.0f;							//AppearSprite�N���X�Ŏg���A�����x�̒萔�l
	

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