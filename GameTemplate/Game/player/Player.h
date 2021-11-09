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
			void SetReceiveDamage(const bool recieveDamageFlag) {

				//�_���[�W�t���O��ݒ�B
				m_receiveDamage = recieveDamageFlag;

				//�_���[�W���󂯂��Ȃ�_���[�W��Ԃɂ���B
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

			void AttackBreak() {

				m_playerState = enState_AttackBreak;
				m_playerAction.AttackBreak();
			}

			/**
			 * @brief �K�[�h���H
			 * @return �K�[�h���Ă��邩�ǂ����̃t���O
			*/
			bool IsGuard() {

				return m_playerAction.IsGuard();
			}
		private:
			bool m_receiveDamage = false;				//�_���[�W���󂯂����H
			SStatus m_status;							//�X�e�[�^�X
			CModelRender* m_modelRender = nullptr;		//���f��
			CPlayerAction m_playerAction;				//�v���C���[�A�N�V�����N���X
			CPlayerAnimation m_playerAnimation;			//�v���C���[�A�j���[�V�����N���X
			CVector3 m_position = CVector3::Zero;		//���W
			CQuaternion m_rotation;						//��]
			CVector3 m_forward = CVector3::Zero;		//�O����
			EnPlayerState m_playerState;				//�v���C���[�̃X�e�[�g
		};
	}
}

