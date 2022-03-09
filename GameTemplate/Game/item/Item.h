#pragma once
#include "constItem.h"

namespace nsMyGame {

	//�G�C���A�X�錾
	class CAppearSprite;

	namespace nsItem {

		//�A�C�e���N���X
		class CItem : public CIGameObject
		{
		private:
			//�A�C�e�����X�g
			enum EnItemList {

				enItem_Key,		//��
			};
		private:
			/**
			 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
			 * @return StartSub()�֐������������H
			*/
			bool Start()override final;

			/**
			 * @brief �폜�֐��B
			*/
			void OnDestroy()override final;

			/**
			 * @brief �X�V�֐��B
			*/
			void Update()override final;

			/**
			 * @brief �G�t�F�N�g�̏������֐��B
			*/
			void InitEffect();

			/**
			 * @brief ���b�Z�[�W�E�B���h�E�������֐��B
			*/
			void InitSpriteAndText();

			/**
			 * @brief �G�t�F�N�g���X�V����֐��B
			*/
			void EffectUpdate();

			/**
			 * @brief �v���C���[�Ƃ̋������K��ȓ������ׂ�֐��B
			 * @param pos 
			*/
			const float CheckLengthToPlayer()const;

			/**
			 * @brief ���̃A�C�e�����I������Ă���H
			 * @return �A�C�e�����I������Ă��邩�ǂ����̃t���O
			*/
			const bool IsSelected()const {

				return m_isSelected;
			}

			/**
			 * @brief �X�v���C�g�ƃe�L�X�g��\������֐��B
			*/
			void AppearSpriteAndText();

			/**
			 * @brief �X�v���C�g�ƃe�L�X�g���\���ɂ���֐��B
			*/
			void DisappearSpriteAndText();
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
			EnItemList m_item = enItem_Key;

			CSpriteRender* m_textSprite = nullptr;				//�e�L�X�g�̃X�v���C�g
			CAppearSprite* m_getSprite = nullptr;				//�A�C�e���擾���̃X�v���C�g
			float m_textSpriteTranslucent = 0.0f;				//�X�v���C�g�̓����x
			nsFont::CFontRender* m_text = nullptr;				//�e�L�X�g
		};
	}
}

