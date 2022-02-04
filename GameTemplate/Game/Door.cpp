#include "stdafx.h"
#include "Door.h"
#include "player/Player.h"
#include "AppearSprite.h"

namespace nsMyGame{

	bool CDoor::Start() {

		//���f�����������B
		InitModel();

		//���b�Z�[�W�E�B���h�E���������B
		InitSpriteAndText();

		return true;
	}

	void CDoor::OnDestroy() {

		DeleteGO(m_modelRender);
		m_modelRender = nullptr;

		DeleteGO(m_text);
		m_text = nullptr;

		DeleteGO(m_doorSprite);
		m_doorSprite = nullptr;
		
		QueryGOs<CAppearSprite>(c_classNameAppearSprite, [&](CAppearSprite* go) {
			DeleteGO(go);
			return true;
		});
		
	}

	void CDoor::Update() {

		//�J���Ȃ��h�A�Ȃ�X�V���Ȃ��B
		if (m_isObj) { return; }

		//�h�A���J���锻������ĊJ����ꂽ��J����B
		JudgeAndExecuteOpenDoor(m_doorRotNum);

		//���W���X�V�B
		m_modelRender->SetPosition(m_position);

		//��]���X�V�B
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

		auto textSprite = FindGO<CAppearSprite>(c_classNameAppearSprite);

		//���b�Z�[�W�E�B���h�E���\������Ă���Ȃ�
		if (m_textSprite != nullptr) {

			//�I���X�v���C�g���\���ɂ���B
			m_doorSprite->Deactivate();
			m_text->Deactivate();

			//�����x���������B
			m_doorSpriteTranslucent = c_translucentValue_Zero.w;

			//�����͂����ŏI���B
			return;
		}

		//�v���C���[�Ƃ̋��������ȉ����܂��J���ĂȂ�
		if (vecToPlayer.Length() <= c_distanceForOpenDoor && !IsOpened()) {
			 
			//�X�v���C�g�ƃe�L�X�g�����X�ɏo��������B
			AppearSpriteAndText();

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

						//�h�A�J��SE���Đ��B
						CSoundManager::GetInstance()->Play(enSE_DoorOpen);

						//�m�F�E�B���h�E�𐶐��B
						m_textSprite = NewGO<CAppearSprite>(enPriority_Zeroth, c_classNameAppearSprite);
						m_textSprite->SetText(L"Key used.  A:OK");
						m_textSprite->SetTextPosition(c_textPosition_getKey);

					}
					//���������Ă��Ȃ�
					else {

						//�����������Ă��Ȃ��m�F�̃E�B���h�E�𐶐��B
						m_textSprite = NewGO<CAppearSprite>(enPriority_Zeroth, c_classNameAppearSprite);
						m_textSprite->SetText(L"It's locked.  A:OK");
						m_textSprite->SetTextPosition(c_textPosition_getKey);

					}
				}
				//���͂������Ă��Ȃ�
				else {

					//�h�A����]�����邽�߂̉񐔂�ݒ�B
					rotNum = c_openDoorRotValue / c_openDoorRotNum;

					//�J������Ԃɐݒ�B
					m_isOpened = true;

					//�h�A�J��SE���Đ��B
					CSoundManager::GetInstance()->Play(enSE_DoorOpen);
				}
			}
		}
		else {

			//���񂾂�X�v���C�g��������悤�ɂ���B
			DisappearSpriteAndText();
		}
	}

	void CDoor::UpdateRotation(unsigned int& rotNum) {

		//�h�A����]�����邽�߂̉񐔂�0���傫���Ȃ�
		if (rotNum > 0) {

			//��]��ݒ�B
			m_rotation.AddRotationY(CMath::DegToRad(c_openDoorRotNum));

			//���f���̉�]���X�V�B
			m_modelRender->SetRotation(m_rotation);

			//�񐔂����炷�B
			rotNum--;
		}
	}

	void CDoor::AppearSpriteAndText() {

		//�J���X�v���C�g��\���B
		m_doorSprite->Activate();
		//�e�L�X�g��\���B
		m_text->Activate();

		//���񂾂�X�v���C�g�������悤�ɂ���B
		if (m_doorSpriteTranslucent < c_translucentValue_Max.w) {

			//�e�L�X�g�J���[��ݒ�B
			float textColor = m_doorSpriteTranslucent;
			m_text->SetColor({ textColor ,textColor ,textColor,m_doorSpriteTranslucent });

			//�X�v���C�g�̓����x��ݒ�B
			m_doorSpriteTranslucent += GameTime().GameTimeFunc().GetFrameDeltaTime() * c_appearSpriteTranslucent;
			m_doorSprite->SetMulColor({ CVector4::White.x,CVector4::White.y,CVector4::White.z, m_doorSpriteTranslucent });
		}
	}

	void CDoor::DisappearSpriteAndText() {

		if (m_doorSpriteTranslucent > c_translucentValue_Zero.w) {

			//�e�L�X�g�J���[��ݒ�B
			float textColor = m_doorSpriteTranslucent;
			m_text->SetColor({ textColor,textColor,textColor,m_doorSpriteTranslucent });

			//�X�v���C�g�̓����x��ݒ�B
			m_doorSpriteTranslucent -= GameTime().GameTimeFunc().GetFrameDeltaTime() * c_appearSpriteTranslucent;
			m_doorSprite->SetMulColor({ CVector4::White.x,CVector4::White.y,CVector4::White.z, m_doorSpriteTranslucent });
		}
		//�J���X�v���C�g���\���B
		//�e�L�X�g���\���B
		else {
			m_doorSpriteTranslucent = c_translucentValue_Zero.w;
			m_doorSprite->Deactivate();
			m_text->Deactivate();
		}
	}

	void CDoor::InitModel() {

		//���f���𐶐��B
		m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);

		//tkm�̃t�@�C���p�X��ݒ�B
		m_modelRender->SetFilePathTkm(c_filePathTkmDoor);

		//�V���h�E�L���X�^�[�t���O��ݒ�B
		m_modelRender->SetShadowCasterFlag(true);

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
	}

	void CDoor::InitSpriteAndText() {

		//�e�L�X�g�̃X�v���C�g���������B
		m_doorSprite = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_doorSprite->Init(c_filePathTextSprite, c_textSpriteWH.x, c_textSpriteWH.y);
		m_doorSprite->SetPosition(c_textSpritePosition);
		m_doorSprite->SetScale(c_textSpriteSize);

		//��\���ɐݒ�B
		m_doorSprite->Deactivate();

		//�e�L�X�g��ݒ�B
		m_text = NewGO<nsFont::CFontRender>(enPriority_Zeroth);
		m_text->Init(L"A: Open");
		m_text->SetPosition(c_textPosition);
		m_text->SetScale(c_textSize);
		m_text->SetColor(CVector4::White);

		//��\���ɐݒ�B
		m_text->Deactivate();
	}
}