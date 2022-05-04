#include "stdafx.h"
#include "LockOnCamera.h"

namespace nsMyGame {

	namespace {

		constexpr float c_cameraFar = 80000.0f;			//�J�����̉�����
		constexpr float c_addCameraPosition = -300.0f;		//�J�����̎��_�����߂�l
		constexpr float c_addCameraPositionY = 250.0f;		//�J�����̎��_�i�����j�����߂�l
		constexpr float c_addCameraTarget = 50.0f;			//�J�����̒����_�����߂�l
		constexpr float c_searchPlayerAngle = 60.0f;		//�v���C���[�̎���p
		constexpr float c_searchDistance = 500.0f;			//���G����
		constexpr float c_enemyLockOnAddY = 100.0f;			//���b�N�I���A�C�R���̏ꏊ�����߂���Z���W
		constexpr float c_inputBorder = 0.8f;				//�E�X�e�B�b�N�̓��͔��肪�N����l
	}

	bool CLockOnCamera::StartSub() {

		//�΂˃J�����̏������B
		m_springCamera.Init(
			*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��B
			1000.0f,			//�J�����̈ړ����x�̍ő�l�B
			true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
			5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
		);

		//�����ʂ�ݒ�B
		m_springCamera.SetFar(c_cameraFar);

		return true;
	}

	void CLockOnCamera::UpdateSub() {

		//���b�N�I���Ώۂ̓G�̍��W���璍���_�����߂�B
		m_target = m_lockOnEnemy->GetPosition();

		//������ɐݒ�B
		m_target.y += c_addCameraTarget;

		//�v���C���[�������B
		nsPlayer::CPlayer* player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

		//�v���C���[�̍��W���擾�B
		CVector3 playerPosition = player->GetPosition();

		//�v���C���[�̍��W���王�_�����߂�B
		m_position = playerPosition;

		//�G�Ɍ������ĐL�т�x�N�g�������߂�B
		CVector3 toEnemyVec = m_target - playerPosition;
		toEnemyVec.y = 0.0f;
		//���K���B
		toEnemyVec.Normalize();

		//�v���C���[�̏������Ɏ��_��ݒ�B
		m_position += toEnemyVec * c_addCameraPosition;
		m_position.y += c_addCameraPositionY;

		//�o�l�J�����ɒ����_�Ǝ��_��ݒ肷��B
		m_springCamera.SetPosition(m_position);
		m_springCamera.SetTarget(m_target);

		//�΂˃J�������X�V�B
		m_springCamera.Update();

		//���b�N�I���Ώۂ��X�V�B
		ChangeLockOnEnemy();

		//�������b�N�I���Ώۂ̓G�����񂾂�J�����𖳌�������B
		if (m_lockOnEnemy->IsDeath()) {

			m_isEnable = false;
		}

		//���b�N�I�����̓G�̍��W���擾�B
		CVector3 enemyPosition = m_lockOnEnemy->GetPosition();

		//���b�N�I�����W�𒲐��B
		enemyPosition.y += c_enemyLockOnAddY;

		//�X�N���[����ԏ�ł̓G�̍��W���v�Z����B
		CVector2 screenPosEnemy = CVector2::Zero;
		m_springCamera.GetCamera()->CalcScreenPositionFromWorldPosition(screenPosEnemy, enemyPosition);

		//���b�N�I���A�C�R�����X�V�B
		m_lockOnMarker.UpdateMarker(screenPosEnemy);
	}

	const bool CLockOnCamera::LockOnEnemy(R3ButtonInput r3Input) {

		//���b�N�I���ł����H
		bool canLockOn = false;

		//�G�̍��W���i�[����ϐ��B
		CVector3 enemyPosition = CVector3::Zero;

		//����p�̒l���i�[����ϐ��B
		//�����l�͕��̒l�ōŏ��̓G�͕K���������ɓ���悤�ɁB
		float angle = -1.0f;

		//�v���C���[�̑O�����ƍ��W���擾�B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);
		CVector3 playerForward = player->GetForward();
		CVector3 playerPosition = player->GetPosition();
		playerPosition.y = 0.0f;

		//�G�������B
		QueryGOs<nsEnemy::CEnemy>(c_classNameEnemy, [&](nsEnemy::CEnemy* enemy) {

			//�G�̍��W���擾�B
			enemyPosition = enemy->GetPosition();
			enemyPosition.y = 0.0f;

			//�v���C���[����G�ɐL�т�x�N�g�������߂�B
			CVector3 toEnemyVec = enemyPosition - playerPosition;

			//�v���C���[�̎���p�ɓ����Ă��邩���߂�B
			float carentAngle = acosf(toEnemyVec.Dot(playerForward));

			//���̋����͈̔͂ɂ��āA������ł��Ȃ��B
			if (toEnemyVec.Length() < c_searchDistance
				&& !enemy->IsDeath()
				) {

				//�v���C���[����G�Ɍ������ĐL�т�x�N�g���𐳋K���B
				toEnemyVec.Normalize();

				//�����Ă�B
				if (fabsf(carentAngle) < CMath::PI * c_searchPlayerAngle
					&& fabsf(carentAngle) < angle		//������܂ł̎���p�������ɂ���B

					|| angle < 0.0f					//�������͏��߂Ă̌����B
					)
				{
					switch(r3Input){
					
					//�E�X�e�B�b�N�̓��͂�������Έ�ԋ߂��G�����b�N�I������悤��
					case No_Input:

						//����p�i���W�A���j���X�V�B
						angle = fabsf(carentAngle);

						//���b�N�I���Ώۂ����̓G�ɕύX�B
						m_lockOnEnemy = enemy;

						//���b�N�I���ł����B
						canLockOn = true;
						break;
					//�E���͏�ԂȂ�E���̓G�����b�N�I���Ώۂɐ؂�ւ���B
					case Input_Right:
						angle = Cross(toEnemyVec, playerForward).y;
						if (m_lockOnEnemy != enemy && Cross(toEnemyVec, playerForward).y < 0.0f) {

							//����p�i���W�A���j���X�V�B
							angle = fabsf(carentAngle);

							//���b�N�I���Ώۂ����̓G�ɕύX�B
							m_lockOnEnemy = enemy;

							//���b�N�I���ł����B
							canLockOn = true;
						}
						break;
						//�E���͏�ԂȂ獶���̓G�����b�N�I���Ώۂɐ؂�ւ���B
					case Input_Left:
						if (m_lockOnEnemy != enemy && Cross(toEnemyVec, playerForward).y > 0.0f) {

							//����p�i���W�A���j���X�V�B
							angle = fabsf(carentAngle);

							//���b�N�I���Ώۂ����̓G�ɕύX�B
							m_lockOnEnemy = enemy;

							//���b�N�I���ł����B
							canLockOn = true;
						}
						break;
					}
				}
			}

			return true;
		});

		return canLockOn;
	}

	void CLockOnCamera::ChangeLockOnEnemy() {

		//�E�X�e�B�b�N�����͂���Ă���H
		if (CheckR3Input()) {

			//���b�N�I���Ώۂ��X�V�B
			LockOnEnemy(m_r3Input);
			m_isR3XInput = true;
		}
	}

	const bool CLockOnCamera::CheckR3Input() {

		//���t���[���̓��͂𒲂ׂ�ϐ��B
		bool isR3XInput = false;

		//���͂𒲂ׂ�B
		float x = g_pad[0]->GetRStickXF();

		//�E�X�e�B�b�N�����E�ɓ|����Ă��邩
		if (x > c_inputBorder) {

			//���t���[���ŉE���͂��������B
			isR3XInput = true;
			m_r3Input = Input_Right;
		}
		else if (x < -c_inputBorder) {

			//���t���[���ō����͂��������B
			isR3XInput = true;
			m_r3Input = Input_Left;
		}
		else {
			//���͂��Ȃ������̂ŁA�O�t���[���̓��͏��������B
			m_isR3XInput = false;
			m_r3Input = No_Input;
		}

		//�O�t���[���œ��͂���Ă��Ȃ��āA
		//���t���[���œ��͂�����
		return !m_isR3XInput && isR3XInput;
	}
}