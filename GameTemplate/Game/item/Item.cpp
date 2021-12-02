#include "stdafx.h"
#include "Item.h"
#include "../player/Player.h"
#include "../AppearSprite.h"

namespace nsMyGame {

	namespace nsItem {

		bool CItem::Start() {

			//�G�t�F�N�g���������B
			m_itemEffect = NewGO<Effect>(enPriority_Zeroth);
			m_itemEffect->Init(c_itemEffectFilePath);
			m_itemEffect->SetPosition(m_position);
			m_itemEffect->SetScale(c_itemEffectSize);

			//�Đ��B
			m_itemEffect->Play();

			//�e�L�X�g�̃X�v���C�g���������B
			m_textSprite = NewGO<CSpriteRender>(enPriority_Zeroth);
			m_textSprite->Init(c_filePathTextSprite, c_textSpriteWH.x, c_textSpriteWH.y);
			m_textSprite->SetPosition(c_textSpritePosition);
			m_textSprite->SetScale(c_textSpriteSize);

			//��\���ɐݒ�B
			m_textSprite->Deactivate();

			//�e�L�X�g��ݒ�B
			m_text = NewGO<nsFont::CFontRender>(enPriority_Zeroth);
			m_text->Init(L"A: Pick up");
			m_text->SetPosition(c_textPosition);
			m_text->SetScale(c_textSize);
			m_text->SetColor(CVector4::White);

			//��\���ɐݒ�B
			m_text->Deactivate();

			return true;
		}

		void CItem::Update() {

			//�v���C���[�������B
			auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

			//�v���C���[�Ƃ̋������K��ȉ��Ȃ玩�g���I������Ă����Ԃɂ���B
			if (CheckLengthToPlayer() <= c_needToDistanceForGetItem) {

				//�v���C���[��I����Ԃɐݒ�B
				player->SetSelectFlag(true);
				m_isSelected = true;
			}
			//��������Ȃ��Ȃ�I����Ԃ���O���B
			else {
				
				m_isSelected = false;
			}

			//���g���I����Ԃɂ���A����A�{�^�������͂��ꂽ��
			if (IsSelected()){

				//�X�v���C�g�ƃe�L�X�g�����X�ɏo��������B
				AppearSpriteAndText();
				
				if (g_pad[0]->IsTrigger(enButtonA)) {

					//�A�C�e���̎��
					switch (m_item) {
					case enItem_Key:		//��

						//�v���C���[�̌��̏�������+1����B
						player->GetKey();

						auto getSprite = NewGO<CAppearSprite>(enPriority_Zeroth);
						getSprite->SetText(L"[Key] get. A: OK");
						getSprite->SetTextPosition(c_textPosition_getKey);
						break;
					}

					//���M���폜�B
					DeleteGO(this);
					DeleteGO(m_textSprite);
					DeleteGO(m_text);

					//�G�t�F�N�g���폜�B
					DeleteGO(m_itemEffect);
				}
			}
			else {

				//���񂾂�X�v���C�g��������悤�ɂ���B
				DisappearSpriteAndText();
			}

			//�G�t�F�N�g���X�V�B
			EffectUpdate();
		}

		void CItem::EffectUpdate() {

			//�G�t�F�N�g���Đ������邽�߂̎��Ԃ��X�V�B
			m_itemEffectReplayTime += GameTime().GameTimeFunc().GetFrameDeltaTime();

			//�K�莞�Ԃ��ƂɃG�t�F�N�g��ǉ��Đ��B
			if (m_itemEffectReplayTime >= c_itemEffectReplayTime) {

				m_itemEffect->Play();
				m_itemEffectReplayTime = 0.0f;
			}
		}

		const float CItem::CheckLengthToPlayer()const {

			//�v���C���[�������B
			auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

			//������Ȃ�������K��l���1000.0f�傫���l��Ԃ��B
			if (player == nullptr) { return c_needToDistanceForGetItem + 1000.0f; }

			//�v���C���[�̍��W���擾�B
			CVector3 playerPos = player->GetPosition();

			//�v���C���[�Ɍ������x�N�g�������߂�B
			CVector3 vecToPlayer = playerPos - m_position;

			//�v���C���[�Ƃ̋�����Ԃ��B
			return vecToPlayer.Length();
		}

		void CItem::AppearSpriteAndText() {

			//�X�v���C�g�ƃe�L�X�g��\���B
			m_textSprite->Activate();
			m_text->Activate();

			//���񂾂�X�v���C�g�������悤�ɂ���B
			if (m_textSpriteTranslucent < 1.0f) {

				//�e�L�X�g�J���[��ݒ�B
				float textColor = m_textSpriteTranslucent;
				m_text->SetColor({ textColor ,textColor ,textColor,m_textSpriteTranslucent });

				//�X�v���C�g�̓����x��ݒ�B
				m_textSpriteTranslucent += GameTime().GameTimeFunc().GetFrameDeltaTime() * 5.0f;
				m_textSprite->SetMulColor({ 1.0f,1.0f,1.0f, m_textSpriteTranslucent });
			}
		}

		void CItem::DisappearSpriteAndText() {

			if (m_textSpriteTranslucent > 0.0f) {

				//�e�L�X�g�J���[��ݒ�B
				float textColor = m_textSpriteTranslucent;
				m_text->SetColor({ textColor,textColor,textColor,m_textSpriteTranslucent });

				//�X�v���C�g�̓����x��ݒ�B
				m_textSpriteTranslucent -= GameTime().GameTimeFunc().GetFrameDeltaTime() * 5.0f;
				m_textSprite->SetMulColor({ 1.0f,1.0f,1.0f, m_textSpriteTranslucent });
			}
			//�J���X�v���C�g���\���B
			//�e�L�X�g���\���B
			else {
				m_textSpriteTranslucent = 0.0f;
				m_textSprite->Deactivate();
				m_text->Deactivate();
			}
		}
	}
}