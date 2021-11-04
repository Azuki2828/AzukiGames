#pragma once
#include "PlayerAction.h"
#include "PlayerAnimation.h"

namespace nsMyGame {

	namespace nsPlayer {	

		//�v���C���[�N���X
		class CPlayer : public CIGameObject
		{
			//�X�e�[�^�X
			struct SStatus {
				int hp = 0;
				int attack = 0;
			};
			/**
			 * @brief ���C�g�J�������X�V����֐��B
			*/
			void LightCameraUpdate();

			/**
			 * @brief �ŏ��Ɉ�񂾂��Ă΂��֐��B
			 * @return ���������H
			*/
			bool Start()override final;

			/**
			 * @brief �X�V�֐��B
			*/
			void Update()override final;

			/**
			 * @brief �v���C���[�̑O�������X�V����֐��B
			*/
			void UpdateForward();
		public:
			/**
			 * @brief ���W���擾����֐��B
			 * @return
			*/
			const CVector3& GetPosition()const {

				return m_position;
			}

			/**
			 * @brief ���f�������_�[�̃C���X�^���X���擾����֐��B
			 * @return ���f�������_�[�̃C���X�^���X
			*/
			CModelRender* GetModelRender() {

				return m_modelRender;
			}

			/**
			 * @brief �L�����N�^�[�R���g���[���[���擾����֐��B
			 * @return �L�����N�^�[�R���g���[���[
			*/
			CharacterController& GetCharacterController() {

				return m_playerAction.GetCharacterController();
			}

			/**
			 * @brief �_���[�W�t���O��ݒ肷��֐��B
			 * @param recieveDamageFlag �_���[�W�t���O
			*/
			void SetReceiveDamage(bool recieveDamageFlag) {

				m_receiveDamage = recieveDamageFlag;
				if (m_receiveDamage) {
					m_playerAction.ReceiveDamage();
					m_playerState = enState_Damage;
				}
			}

			/**
			 * @brief �_���[�W�t���O���擾����֐��B
			 * @return �_���[�W�t���O
			*/
			const bool GetReceiveDamage()const {

				return m_receiveDamage;
			}
		private:
			bool m_receiveDamage = false;				//�_���[�W���󂯂����H
			SStatus m_status;							//�X�e�[�^�X
			CModelRender* m_modelRender = nullptr;		//���f��
			CPlayerAction m_playerAction;				//�v���C���[�̍s�����܂Ƃ߂��N���X
			CPlayerAnimation m_playerAnimation;			//�v���C���[�A�j���[�V����
			CVector3 m_position = CVector3::Zero;		//���W
			CQuaternion m_rotation;						//��]
			CVector3 m_forward = CVector3::Zero;		//�v���C���[�̑O����
			EnPlayerState m_playerState;				//�v���C���[�̃X�e�[�g
		};
	}
}

