#include "stdafx.h"
#include <random>
#include "LockOnCamera.h"
#include "constCamera.h"
#include "../enemy/boss/Boss.h"

namespace nsMyGame {

	namespace nsCamera {

		namespace {

			constexpr float c_lockOnCameraVelocityMax = 1000.0f;	//�ړ����x�̍ő�l
			constexpr float c_searchPlayerAngle = 60.0f;			//�v���C���[�̎���p
			constexpr float c_searchDistance = 800.0f;				//���G����
			constexpr float c_enemyLockOnAddY = 80.0f;				//���b�N�I���A�C�R���̏ꏊ�����߂���Z���W
			constexpr float c_inputBorder = 0.5f;					//�E�X�e�B�b�N�̓��͔��肪�N����l
			constexpr float c_addCameraTargetPlayerY = 30.0f;		//�ǂ��𒍎��_�ɂ���̂���������l
			constexpr float c_addLockOnMarkerPosition = 100.0f;		//���b�N�I���A�C�R���̍��W�𒲐�����l
		}

		bool CLockOnCamera::StartSub() {

			//�΂˃J�����̏������B
			m_springCamera.Init(
				*g_camera3D,							//�΂˃J�����̏������s���J�������w�肷��B
				c_lockOnCameraVelocityMax,				//�J�����̈ړ����x�̍ő�l�B
				/*isEnableCollisionSolver*/true,		//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
				c_cameraCollisionRadius					//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
			);

			//�����ʂ�ݒ�B
			m_springCamera.SetFar(c_cameraFar);

			//�J�������u�ԓI�ɐ؂�ւ��Ȃ��悤�ɐݒ�B
			m_springCamera.NonRefresh();

			return true;
		}

		void CLockOnCamera::UpdateSub() {

			//���b�N�I���J�������X�V�B
			UpdateLockOnCamera();

			CVector3 shakeTarget = CVector3::Zero;

			//�J�������h���ԂȂ�^�[�Q�b�g��h�炷�B
			if (m_state == enShake) {

				std::random_device seed_gen;
				std::mt19937 random(seed_gen());

				float shakeRange = static_cast<float>(random() % c_cameraShakeRange) - c_cameraShakeRangeAdjustment;

				shakeTarget = { shakeRange,shakeRange ,shakeRange };
			}

			//�o�l�J�����ɒ����_�Ǝ��_��ݒ肷��B
			m_springCamera.SetPosition(m_position + shakeTarget);
			m_springCamera.SetTarget(m_target + shakeTarget);

			//�΂˃J�������X�V�B
			m_springCamera.Update();

			//���b�N�I���A�C�R�����X�V�B
			UpdateLockOnMarker();
		}

		const bool CLockOnCamera::LockOnEnemy(R3ButtonInput r3Input) {



			//���b�N�I���ł����H
			bool canLockOn = false;

			//�G�̍��W���i�[����ϐ��B
			CVector3 enemyPosition = CVector3::Zero;

			//����p�̒l���i�[����ϐ�
			//�����l�͕��̒l�ōŏ��̓G�͕K���������ɓ���悤��
			float angle = -1.0f;

			//�v���C���[�̑O�����ƍ��W���擾�B
			auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);
			CVector3 playerForward = player->GetForward();
			CVector3 playerPosition = player->GetPosition();
			playerPosition.y = 0.0f;


			auto boss = FindGO<nsEnemy::CBoss>(c_classNameBoss);

			//�{�X���o�����Ă���ꍇ�̓{�X�������B
			if (boss != nullptr && boss->NoticePlayer()) {

				//�{�X�����b�N�I���ΏۂɁB
				m_lockOnEnemy = boss;
				canLockOn = true;
			}
			else {
				//�G�������B
				QueryGOs<nsEnemy::CEnemy>(c_classNameEnemy, [&](nsEnemy::CEnemy* enemy) {


					//�G�̍��W���擾�B
					enemyPosition = enemy->GetPosition();
					enemyPosition.y = 0.0f;

					//�v���C���[����G�ɐL�т�x�N�g�������߂�B
					CVector3 toEnemyVec = enemyPosition - playerPosition;

					CVector3 toEnemyVecNormal = toEnemyVec;
					toEnemyVecNormal.Normalize();

					//�J�����̎���p�ɓ����Ă��邩���߂�B
					float carentAngle = acosf(toEnemyVecNormal.Dot(playerForward));

					//���̋����͈̔͂ɂ��āA������ł��Ȃ��B
					if (toEnemyVec.Length() < c_searchDistance
						&& !enemy->IsDeath()
						) {

						//�v���C���[����G�Ɍ������ĐL�т�x�N�g���𐳋K���B
						toEnemyVec.Normalize();

						//�����Ă�B
						if (fabsf(carentAngle) < CMath::PI * (c_searchPlayerAngle / 180.0f)
							&& fabsf(carentAngle) < angle		//������܂ł̎���p�������ɂ���B

							|| angle < 0.0f					//�������͏��߂Ă̌����B
							)
						{
							switch (r3Input) {

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
								if (m_lockOnEnemy != enemy && Cross(toEnemyVec, playerForward).y <= 0.0f) {

									//����p�i���W�A���j���X�V�B
									angle = fabsf(carentAngle);

									//���b�N�I���Ώۂ����̓G�ɕύX�B
									m_lockOnEnemy = enemy;

									//���b�N�I���ł����B
									canLockOn = true;
									return false;
								}
								break;
								//�E���͏�ԂȂ獶���̓G�����b�N�I���Ώۂɐ؂�ւ���B
							case Input_Left:
								if (m_lockOnEnemy != enemy && Cross(toEnemyVec, playerForward).y >= 0.0f) {

									//����p�i���W�A���j���X�V�B
									angle = fabsf(carentAngle);

									//���b�N�I���Ώۂ����̓G�ɕύX�B
									m_lockOnEnemy = enemy;

									//���b�N�I���ł����B
									canLockOn = true;
									return false;
								}
								break;
							}
						}
					}

					return true;
					});

				return canLockOn;
			}
		}

		void CLockOnCamera::ChangeLockOnEnemy() {

			//�E�X�e�B�b�N�����͂���Ă���H
			if (CheckR3Input()) {

				//���b�N�I���Ώۂ��X�V�B
				LockOnEnemy(m_r3Input);
				m_isR3XInput = true;
			}
		}

		void CLockOnCamera::InitCameraToPlayerVec() {

			//���b�N�I���Ώۂ̓G�̍��W���璍���_�����߂�B
			m_target = m_lockOnEnemy->GetPosition();

			//������ɐݒ�B
			m_target.y += c_addCameraTarget;

			//�v���C���[�������B
			nsPlayer::CPlayer* player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

			//�v���C���[�̍��W���擾�B
			CVector3 playerPosition = player->GetPosition();
			playerPosition.y += c_addCameraTarget;

			//�G����v���C���[�Ɍ������ĐL�т�x�N�g�������߂�iy�����͍폜�j�B
			CVector3 enemyToPlayerVecYZero = playerPosition - m_target;
			enemyToPlayerVecYZero.y = 0.0f;

			//���K���B
			CVector3 enemyToPlayerVecNormal = enemyToPlayerVecYZero;
			enemyToPlayerVecNormal.Normalize();

			//�v���C���[����J�����ɐL�т�x�N�g����y������ۑ��B
			float cameraToPlayerVecY = c_defaultCameraVec.y;

			//�J�����x�N�g���̒�����ۑ��B
			float cameraVecLength = m_cameraToPlayerVec.Length();

			//���W���v�Z�B
			m_cameraToPlayerVec = enemyToPlayerVecNormal * m_cameraToPlayerVec.Length();

			//y������萔�ɕύX�B
			m_cameraToPlayerVec.y = c_defaultCameraVec.y;

			//���K���B
			m_cameraToPlayerVec.Normalize();

			//�ۑ����Ă������x�N�g���̒����{���ăJ�����x�N�g���̋��������ɂ���B
			m_cameraToPlayerVec *= cameraVecLength;
		}

		void CLockOnCamera::UpdateLockOnCamera() {

			//�G�̍��W���擾����B
			CVector3 enemyPosition = m_lockOnEnemy->GetPosition();

			//������ɐݒ�B
			enemyPosition.y += c_addCameraTarget;

			//�v���C���[�������B
			nsPlayer::CPlayer* player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

			//�v���C���[�̍��W���擾�B
			CVector3 playerPosition = player->GetPosition();
			playerPosition.y += c_addCameraTarget;

			//�G����v���C���[�Ɍ������ĐL�т�x�N�g�������߂�B
			CVector3 enemyToPlayerVec = playerPosition - enemyPosition;

			//�v���C���[�̓���𒍎��_�ɐݒ�B
			playerPosition.y += c_addCameraTargetPlayerY;
			m_target = playerPosition;

			CVector3 enemyToPlayerVecYZero = enemyToPlayerVec;
			enemyToPlayerVecYZero.y = 0.0f;

			//���K���B
			CVector3 enemyToPlayerVecNormal = enemyToPlayerVecYZero;
			enemyToPlayerVecNormal.Normalize();

			//�v���C���[����J�����ɐL�т�x�N�g����y������ۑ��B
			float cameraToPlayerVecY = m_cameraToPlayerVec.y;

			//y�����������ĎΕӂ̒������J�b�g�B
			m_cameraToPlayerVec.y = 0.0f;

			m_cameraToPlayerVec = enemyToPlayerVecNormal * m_cameraToPlayerVec.Length();
			m_cameraToPlayerVec.y = cameraToPlayerVecY;

			//�v���C���[�̏������Ɏ��_��ݒ�B
			m_position = m_target + m_cameraToPlayerVec;

			//���b�N�I���Ώۂ��X�V�B
			ChangeLockOnEnemy();

			//�������b�N�I���Ώۂ̓G�����񂾂�
			//�������͍��G�����𒴂�����
			//�J�����𖳌�������B
			if (m_lockOnEnemy->IsDeath()
				|| enemyToPlayerVec.Length() > c_searchDistance
				) {

				m_isEnable = false;
			}
		}

		void CLockOnCamera::UpdateLockOnMarker() {

			//���b�N�I�����̓G�̍��W���擾�B
			CVector3 enemyPosition = m_lockOnEnemy->GetPosition();

			//���b�N�I�����W�𒲐��B
			enemyPosition.y += c_addLockOnMarkerPosition;

			//�X�N���[����ԏ�ł̓G�̍��W���v�Z����B
			CVector2 screenPosEnemy = CVector2::Zero;
			m_springCamera.GetCamera()->CalcScreenPositionFromWorldPosition(
				/*screenPos*/screenPosEnemy,
				/*worldPos*/enemyPosition
			);

			//���b�N�I���A�C�R�����X�V�B
			m_lockOnMarker.UpdateMarker(screenPosEnemy);
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
}