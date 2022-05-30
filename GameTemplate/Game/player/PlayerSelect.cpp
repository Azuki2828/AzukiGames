#include "stdafx.h"
#include "PlayerSelect.h"
#include "../Door.h"
#include "Player.h"

namespace nsMyGame {

	void CPlayerSelect::SetSelectObject(CIGameObject* selectObj, const CVector3& playerPos) {

		//�i�[����Ă��Ȃ��Ȃ炻�̂܂ܑI����Ԃɂ���B
		if (m_selectObject == nullptr) {

			m_selectObject = selectObj;
			selectObj->SetSelectFlag(true);
		}
		//���ɉ�����I�����Ă���
		else {

			//�v���C���[�ɐL�т�x�N�g�����v�Z�B
			CVector3 vecToPlayer = playerPos - selectObj->GetPosition();

			float length = vecToPlayer.Length();
			float length2 = GetSelectObjectLengthToPlayer(playerPos);

			//���ݑI�����Ă���I�u�W�F�N�g�ƃv���C���[�Ƃ̋����ƁA
			//����̃I�u�W�F�N�g�ƃv���C���[�Ƃ̋������r���āA���Z����������I����Ԃɂ���B
			if (vecToPlayer.Length() < GetSelectObjectLengthToPlayer(playerPos)) {

				m_selectObject->SetSelectFlag(false);
				m_selectObject = selectObj;
				selectObj->SetSelectFlag(true);
			}
		}
	}

	const float CPlayerSelect::GetSelectObjectLengthToPlayer(const CVector3& playerPos) {

		//�o�^����Ă��Ȃ��Ȃ畉�̒l��Ԃ��B
		if (m_selectObject == nullptr) {

			return -1.0f;
		}

		//�v���C���[�ɐL�т�x�N�g�����v�Z�B
		CVector3 vecToPlayer = playerPos - m_selectObject->GetPosition();

		//�v���C���[�Ƃ̋�����Ԃ��B
		return vecToPlayer.Length();
	}
}