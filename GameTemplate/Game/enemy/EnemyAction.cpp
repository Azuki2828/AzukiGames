#include "stdafx.h"
#include "EnemyAction.h"

namespace nsMyGame {

	namespace nsEnemy {

		void CEnemyAction::Init(const CVector3& position, CharacterController& charaCon) {

			m_charaCon = &charaCon;

			//�L�����N�^�[�R���g���[���[���������B
			m_charaCon->Init(
				20.0f,			//���a�B
				200.0f,			//�����B
				position		//���W�B
			);
		}

		/*void CEnemyAction::Move(CVector3& position, CVector3& forward, EnEnemyState& enemyState) {


		}*/

		void CEnemyAction::Rotate(const CQuaternion& rotation) {

		}

		

		void CEnemyAction::Update() {

		}
	}
}