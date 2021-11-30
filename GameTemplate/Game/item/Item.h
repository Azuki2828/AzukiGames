#pragma once
namespace nsMyGame {

	namespace nsItem {

		//�A�C�e���N���X
		class CItem : public CIGameObject
		{
		private:
			//�A�C�e�����X�g
			enum ItemList {

				enItem_Key,		//��
			};
		private:
			/**
			 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
			 * @return StartSub()�֐������������H
			*/
			bool Start()override final;

			/**
			 * @brief �X�V�֐��B
			*/
			void Update()override final;

			/**
			 * @brief �G�t�F�N�g���X�V����֐��B
			*/
			void EffectUpdate();

			/**
			 * @brief �v���C���[�Ƃ̋������K��ȓ������ׂ�֐��B
			 * @param pos 
			*/
			const float CheckLengthToPlayer()const;
		public:

			/**
			 * @brief ���̃A�C�e�����I����Ԃɂ���H
			 * @return �I����Ԃ��ǂ����̃t���O�B
			*/
			bool IsSelected() {

				return m_isSelected;
			}

			/**
			 * @brief ���W��ݒ肷��֐��B
			 * @param pos ���W
			*/
			void SetPosition(const CVector3& pos) {

				m_position = pos;
			}

			/**
			 * @brief ���W���擾����֐��B
			 * @return ���W
			*/
			const CVector3& GetPosition()const {

				return m_position;
			}
		private:
			bool m_isSelected = false;				//�I����Ԃɂ���H
			float m_itemEffectReplayTime = 0.0f;	//�A�C�e���G�t�F�N�g���Đ������邽�߂̎���
			CVector3 m_position = CVector3::Zero;	//���W
			Effect* m_itemEffect = nullptr;			//�A�C�e���̈�
		};
	}
}

