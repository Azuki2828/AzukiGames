#include "stdafx.h"
#include "Door.h"
#include "player/Player.h"

namespace nsMyGame{

	bool CDoor::Start() {

		//���f���𐶐��B
		m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);

		//tkm�̃t�@�C���p�X��ݒ�B
		m_modelRender->SetFilePathTkm(c_filePathTkmDoor);

		//���W��ݒ�B
		m_modelRender->SetPosition(m_position);

		//��]��ݒ�B
		m_modelRender->SetRotation(m_rotation);

		//�g���ݒ�B
		m_modelRender->SetScale(m_scale);

		//���f�����������B
		m_modelRender->Init();

		return true;
	}

	void CDoor::Update() {

		//�h�A����]�����邽�߂̉񐔂��������B
		static unsigned int doorRotNum = 0;

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

		//�v���C���[�̍��W���擾�B
		CVector3 playerPos = player->GetPosition();

		//�v���C���[�ɐL�т�x�N�g�����v�Z�B
		CVector3 vecToPlayer = playerPos - m_position;

		//�����v���C���[�Ƃ̋��������ȉ�����A�{�^�������͂��ꂽ��
		if (vecToPlayer.Length() <= c_distanceForOpenDoor && g_pad[0]->IsTrigger(enButtonA)) {

			//���������������Ă���Ȃ�
			if (IsLocked()) {

				//�v���C���[�����������Ă���Ȃ�B
				if (player->HasKey()) {

					//���b�N���O���B
					m_isLocked = false;

					//�h�A����]�����邽�߂̉񐔂�ݒ�B
					doorRotNum = c_openDoorRotValue / c_openDoorRotNum;

					//���������B
					player->ConsumeKey();
				}
			}
			//���������Ă��Ȃ��Ȃ�
			else {
				/////////////////////////////////////////////
				//���������ĂȂ���I�̃e�L�X�g��\��������B
				/////////////////////////////////////////////
			}
		}

		//�h�A����]�����邽�߂̉񐔂�0���傫���Ȃ�
		if (doorRotNum > 0) {

			//��]��ݒ�B
			m_rotation.SetRotationDegY(static_cast<float>(c_openDoorRotNum));

			//���f���ɉ�]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//�񐔂����炷�B
			doorRotNum--;
		}
	}
}