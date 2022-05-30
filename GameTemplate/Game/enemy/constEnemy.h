#pragma once

namespace nsMyGame {

	namespace nsEnemy {

		constexpr const char* c_filePathTkmEnemy = "Assets/modelData/human.tkm";		//�G��tkm�t�@�C���p�X
		constexpr const char* c_filePathTksEnemy = "Assets/modelData/human.tks";		//�G��tks�t�@�C���p�X
		constexpr const char* c_filePathTkmBoss = "Assets/modelData/boss.tkm";			//�{�X��tkm�t�@�C���p�X
		constexpr const char* c_filePathTksBoss = "Assets/modelData/boss.tks";			//�{�X��tks�t�@�C���p�X

		constexpr const float c_bossAnimBlendValue = 0.4f;								//�{�X�̃A�j���[�V�����̕�Ԏ���

		constexpr const int c_bossMaxHP = 100;											//�{�X�̍ő�HP
		constexpr const int c_bossAttack = 10;											//�{�X�̍U����
		constexpr float c_threeComboCoolTime = 3.0f;									//3�A���U�����̃N�[���^�C��
		const CVector3 c_attackTriggerBoxSize = { 15.0f, 110.0f, 15.0f };				//�G�U�����̃g���K�[�{�b�N�X�̃T�C�Y
		const CVector3 c_bossAttackTriggerBoxSize = { 145.0f, 90.0f, 90.0f };			//�{�X�U�����̃g���K�[�{�b�N�X�̃T�C�Y
		constexpr float c_attackTriggerBoxMul = 80.0f;									//�G�U�����̃g���K�[�{�b�N�X�̑O�����ւ̏�Z�l
		constexpr float c_attackTriggerBoxAddYPos = 50.0f;								//�G�U�����̃g���K�[�{�b�N�X��Y�����ւ̉��Z�l
	}
}