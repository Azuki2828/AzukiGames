#include "stdafx.h"
#include "Door.h"
#include "player/Player.h"

namespace nsMyGame{

	bool CDoor::Start() {

		//���f���𐶐��B
		m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);

		//tkm�̃t�@�C���p�X��ݒ�B
		m_modelRender->SetFilePathTkm(c_filePathTkmDoor);

		//�V���h�E�L���X�^�[�t���O��ݒ�B
		m_modelRender->SetShadowReceiverFlag(true);

		//���W��ݒ�B
		m_modelRender->SetPosition(m_position);

		//��]��ݒ�B
		m_modelRender->SetRotation(m_rotation);

		//�g���ݒ�B
		m_modelRender->SetScale(m_scale);

		//���f�����������B
		m_modelRender->Init();

		//�ÓI�����I�u�W�F�N�g���������B
		m_physicsStaticObject.CreateFromModel(
			*m_modelRender->GetModel(),
			m_modelRender->GetModel()->GetWorldMatrix()
		);

		//�ÓI�����I�u�W�F�N�g���X�V�B
		m_physicsStaticObject.GetRigidBody().SetPositionAndRotation(m_position, m_rotation);

		return true;
	}

	void CDoor::Update() {

		//�I�u�W�F�N�g�Ȃ�X�V���Ȃ��B
		if (m_isObj) {
			return;
		}

		//�h�A���J���锻������ĊJ����ꂽ��J����B
		JudgeAndExecuteOpenDoor(m_doorRotNum);

		//�h�A�̉�]���X�V�B
		UpdateRotation(m_doorRotNum);

		//�ÓI�����I�u�W�F�N�g���X�V�B
		m_physicsStaticObject.GetRigidBody().SetPositionAndRotation(m_position, m_rotation);
	}

	void CDoor::JudgeAndExecuteOpenDoor(unsigned int& rotNum) {

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

		//�v���C���[�̍��W���擾�B
		CVector3 playerPos = player->GetPosition();

		//�v���C���[�ɐL�т�x�N�g�����v�Z�B
		CVector3 vecToPlayer = playerPos - m_position;

		//�v���C���[�Ƃ̋��������ȉ����܂��J���ĂȂ�
		if (vecToPlayer.Length() <= c_distanceForOpenDoor && !IsOpened()) {

			//�v���C���[��������I��ł����Ԃɂ���B
			player->SetSelectFlag(true);

			//A�{�^�������͂��ꂽ
			if (g_pad[0]->IsTrigger(enButtonA)) {

				//�����������Ă���H
				if (IsLocked()) {

					//�v���C���[�����������Ă���H
					if (player->HasKey()) {

						//���b�N���O���B
						m_isLocked = false;

						//�h�A����]�����邽�߂̉񐔂�ݒ�B
						rotNum = c_openDoorRotValue / c_openDoorRotNum;

						//���������B
						player->ConsumeKey();

						//�J������Ԃɐݒ�B
						m_isOpened = true;
					}
					//���������Ă��Ȃ�
					else {
						/////////////////////////////////////////////
						//���������ĂȂ���I�̃e�L�X�g��\��������B
						/////////////////////////////////////////////
					}
				}
				//���͂������Ă��Ȃ�
				else {

					//�h�A����]�����邽�߂̉񐔂�ݒ�B
					rotNum = c_openDoorRotValue / c_openDoorRotNum;

					//�J������Ԃɐݒ�B
					m_isOpened = true;
				}
			}
		}
		else {

			//�v���C���[�������I��ł��Ȃ���Ԃɂ���B
			player->SetSelectFlag(false);
		}
	}

	void CDoor::UpdateRotation(unsigned int& rotNum) {

		//�h�A����]�����邽�߂̉񐔂�0���傫���Ȃ�
		if (rotNum > 0) {

			//��]��ݒ�B
			m_rotation.AddRotationY(CMath::DegToRad(c_openDoorRotNum));

			//���f���ɉ�]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//�񐔂����炷�B
			rotNum--;
		}
	}
}