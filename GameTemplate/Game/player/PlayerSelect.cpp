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

	//void PlayerSelect::Update() {

	//	//�I�u�W�F�N�g�̍��W��ǂݍ��ށB
	//	CVector3 pos = CVector3::Zero;

	//	//�v���C���[�������B
	//	auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

	//	//�v���C���[�̍��W���擾�B
	//	CVector3 playerPos = player->GetPosition();

	//	//�K��l���100.0f�傫�����������l�Ƃ���B
	//	float vecToPlayerLength = c_distanceForOpenDoor + 100.0f;

	//	//���X�g�Ɋ܂܂��I�u�W�F�N�g���Q�ƁB
	//	for (const auto& obj : m_objectList) {

	//		//�N���X�̖��O�𒲂ׂ�B
	//		const std::type_info& typeInfo = typeid(*obj);

	//		//�h�A��������
	//		if (typeInfo == typeid(CDoor)) {

	//			//�h�A�N���X�ɃL���X�g�B
	//			auto doorObj = dynamic_cast<CDoor*>(obj);

	//			//�v���C���[�ɐL�т�x�N�g�����v�Z�B
	//			CVector3 vecToPlayer = playerPos - doorObj->GetPosition();

	//			//�v���C���[�Ƃ̍ŒZ�������X�V�B
	//			if (vecToPlayer.Length() < vecToPlayerLength) {

	//				vecToPlayerLength = vecToPlayer.Length();

	//				//�ŒZ�������X�V�����h�A�ƃv���C���[�̋��������ȉ����A���̃h�A���J���Ă��Ȃ��Ȃ�
	//				if (vecToPlayerLength <= c_distanceForOpenDoor && !doorObj->IsOpened()) {

	//					//�v���C���[��I����Ԃɂ���B
	//					player->SetSelectFlag(true);
	//					break;
	//				}
	//			}
	//			//����ȊO�́A�v���C���[�͉����I�����Ă��Ȃ���ԁB
	//			else {

	//				player->SetSelectFlag(false);
	//			}
	//		}
	//	}
	//}
}