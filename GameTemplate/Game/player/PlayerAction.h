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
			 * @param selectFlag ������I��ł��邩�ǂ����̃t���O
			*/
			void Action(EnPlayerState& playerState, const bool selectFlag);

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

			void ReceiveDamage() {

				m_coolTime = 0.5f;
			}

			/**
			 * @brief �K�[�h�������̃N�[���^�C����ݒ�B
			*/
			void GuardSuccess() {

				m_guardSccessCoolTime = 0.3f;
			}
			/**
			 * @brief �U�����K�[�h���ꂽ���̃N�[���^�C����ݒ�B
			*/
			void AttackBreak() {

				m_coolTime = 1.0f;
			}

			/**
			 * @brief �K�[�h���H
			 * @return �K�[�h���Ă��邩�ǂ����̃t���O
			*/
			const bool IsGuard()const {

				return m_isGuard;
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
			 * @brief �K�[�h���������̃N�[���^�C�������ǂ������肷��֐��B
			 * @return �K�[�h���������̃N�[���^�C�����H
			*/
			const bool IsGuardSccessCoolTime()const {

				return m_guardSccessCoolTime > 0.0f;
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
			bool m_isGuard = false;								//�K�[�h���H
			float m_coolTime = 0.0f;							//�N�[���^�C��
			float m_guardSccessCoolTime = 0.0f;					//�K�[�h�������̃N�[���^�C��
			CVector3 m_position = CVector3::Zero;				//���W
			CQuaternion m_rotation = CQuaternion::Identity;		//��]
			CVector3 m_moveSpeed = CVector3::Zero;				//�ړ����x
			CVector3 m_rollingSpeed = CVector3::Zero;			//��]���x
			CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
			CPlayerTriggerBox m_triggerBox;						//�U�����Ɏg�p����g���K�[�{�b�N�X
		};
	}
}
