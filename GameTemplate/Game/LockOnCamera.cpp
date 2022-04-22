#include "stdafx.h"
#include "LockOnCamera.h"

namespace nsMyGame {

	namespace {

		constexpr float c_addCameraPosition = -300.0f;
		constexpr float c_addCameraTarget = 50.0f;
		constexpr float c_addCameraPositionY = 250.0f;
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
		m_springCamera.SetFar(80000.0f);

		//�G�������B
		LockOnEnemy();

		return true;
	}

	void CLockOnCamera::UpdateSub() {

		//�J�������؂�ւ������G���Č����B
		if (m_switched) { LockOnEnemy(); }

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
	}

	void CLockOnCamera::LockOnEnemy() {

		//�G�Ƃ̋������擾����ϐ��B
		float enemyPosition = 0.0f;

		//�G�������B
		QueryGOs<nsEnemy::CEnemy>(c_classNameEnemy, [&](nsEnemy::CEnemy* enemy) {

			//���߂Č��������G�Ȃ�A���̂܂ܑ���B
			//�Q�l�ڈȍ~�̓G�Ȃ�A����܂ł̓G�Ƃ̋����Ɣ�r���Ă��Z���ق��̓G���擾�B
			if (enemyPosition == 0.0f
				|| enemyPosition > enemy->GetPosition().Length()
			)
			{
				//�����̃T���v�����X�V�B
				enemyPosition = enemy->GetPosition().Length();

				//���b�N�I���Ώۂ̓G���X�V�B
				m_lockOnEnemy = enemy;
			}

			return true;
			});
	}
}