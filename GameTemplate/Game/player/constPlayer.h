#pragma once

namespace nsMyGame {

	namespace nsPlayer {

		constexpr const char* c_filePathTkmPlayer = "Assets/modelData/player2.tkm";		//�v���C���[��tkm�t�@�C���p�X
		constexpr const char* c_filePathTksPlayer = "Assets/modelData/player2.tks";		//�v���C���[��tks�t�@�C���p�X
		constexpr const float c_animationInterpolateTime = 0.6f;						//�A�j���[�V�����̕�Ԏ���
		constexpr float c_rollingCoolTime = 1.2f;										//���[�����O���̃N�[���^�C��
		constexpr float c_attackCoolTime = 0.8f;										//�ʏ�U�����̃N�[���^�C��
		constexpr float c_threeComboCoolTime = 3.0f;									//3�A���U�����̃N�[���^�C��
		const CVector3 c_playerStartPosition = { 0.0f,0.0f,0.0f };						//�J�n���̃v���C���[�̍��W
		constexpr float c_rotSpeed = 8.0f;												//��]�����ɗp����x��

		constexpr const int c_playerMaxHP = 100;										//�v���C���[�̍ő�HP
		const CVector3 c_attackTriggerBoxSize = { 110.0f, 15.0f, 15.0f };				//�v���C���[�U�����̃g���K�[�{�b�N�X�̃T�C�Y
		constexpr float c_attackTriggerBoxMul = 80.0f;									//�v���C���[�U�����̃g���K�[�{�b�N�X�̑O�����ւ̏�Z�l
		constexpr float c_attackTriggerBoxAddYPos = 50.0f;								//�v���C���[�U�����̃g���K�[�{�b�N�X��Y�����ւ̉��Z�l


		//�v���C���[�̃X�e�[�g
		enum EnPlayerState {
			enState_Idle,
			enState_Walk,
			enState_LeftWalk,
			enState_RightWalk,
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
}