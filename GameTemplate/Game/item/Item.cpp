#include "stdafx.h"
#include "Item.h"
#include "../player/Player.h"

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

			return true;
		}

		void CItem::Update() {

			//�v���C���[�Ƃ̋������K��ȉ��Ȃ玩�g���I������Ă����Ԃɂ���B
			if (CheckLengthToPlayer() <= c_needToDistanceForGetItem) {

				m_isSelected = true;
			}
			//��������Ȃ��Ȃ�I����Ԃ���O���B
			else {
				
				m_isSelected = false;
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

			//������Ȃ�������K����1000.0f�傫���l��Ԃ��B
			if (player == nullptr) { return c_needToDistanceForGetItem + 1000.0f; }

			//�v���C���[�̍��W���擾�B
			CVector3 playerPos = player->GetPosition();

			//�v���C���[�Ɍ������x�N�g�������߂�B
			CVector3 vecToPlayer = playerPos - m_position;

			//�v���C���[�Ƃ̋�����Ԃ��B
			return vecToPlayer.Length();
		}
	}
}