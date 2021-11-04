#pragma once
#include "PlayerTriggerBox.h"

namespace nsMyGame {

	namespace nsPlayer {

		//�v���C���[�A�N�V�����N���X

		class CPlayerAction
		{
		public:
			/**
			 * @brief �������֐��B
			 * @param position �v���C���[�̍��W�B
			*/
			void Init(const CVector3& position, const CQuaternion& rotation, const CVector3& forward);

			/**
			 * @brief �ړ��������s���֐��B
			 * @param position ���W
			 * @param forward �O����
			 * @param playerState �v���C���[�X�e�[�g
			*/
			void Move(CVector3& position, CVector3& forward, EnPlayerState& playerState);

			/**
			 * @brief ��]�������s���֐��B
			 * @param rotation ��]
			*/
			void Rotate(CQuaternion& rotation);

			/**
			 * @brief �A�N�V�������s���֐��B
			 * @param playerState �v���C���[�X�e�[�g
			*/
			void Action(EnPlayerState& playerState);

			/**
			 * @brief �X�V�֐��B�N�[���^�C���̍X�V�Ȃǂ��s���B
			*/
			void Update(const CVector3& pos, const CQuaternion& rot,const CVector3& forward, EnPlayerState& playerState);

			/**
			 * @brief �L�����N�^�[�R���g���[���[���擾����֐��B
			 * @return �L�����N�^�[�R���g���[���[
			*/
			CharacterController& GetCharacterController() {

				return m_charaCon;
			}
		private:
			/**
			 * @brief �N�[���^�C�������ǂ������肷��֐��B
			 * @return �N�[���^�C�����H
			*/
			const bool IsCoolTime()const {

				return m_coolTime > 0.0f;
			}

			/**
			 * @brief �_�b�V�������ǂ������肷��֐��B
			 * @return �_�b�V�����H
			*/
			const bool IsDash()const {

				return m_isDash;
			}

			const bool GetHitAttackFlag()const {

				return m_hitAttack;
			}

			void SetHitAttackFlag(bool hitAttackFlag) {

				m_hitAttack = hitAttackFlag;
			}

			
		private:
			bool m_isAttack = false;							//�A�^�b�N���H
			bool m_hitAttack = false;							//�U�������������H
			bool m_isDash = false;								//�_�b�V�����H
			float m_coolTime = 0.0f;							//�N�[���^�C��
			CVector3 m_position = CVector3::Zero;				//���W
			CQuaternion m_rotation = CQuaternion::Identity;		//��]
			CVector3 m_moveSpeed = CVector3::Zero;				//�ړ����x
			CVector3 m_rollingSpeed = CVector3::Zero;
			CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
			CPlayerTriggerBox m_triggerBox;						//�U�����Ɏg�p����g���K�[�{�b�N�X
		};
	}
}
