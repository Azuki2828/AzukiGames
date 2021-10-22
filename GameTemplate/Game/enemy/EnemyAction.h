#pragma once

namespace nsMyGame {

	namespace nsEnemy {

		//�G�l�~�[�A�N�V�����N���X

		class CEnemyAction {

		public:
			/**
			 * @brief �������֐��B�L�����R���̐ݒ���s���B
			 * @param position �v���C���[�̍��W�B
			*/
			void Init(const CVector3& position);

			/**
			 * @brief �ړ��������s���֐��B
			 * @param position ���W
			 * @param forward �O����
			 * @param playerState �v���C���[�X�e�[�g
			*/
			void Move(CVector3& position, CVector3& forward, EnEnemyState& playerState);

			/**
			 * @brief ��]�������s���֐��B
			 * @param rotation ��]
			*/
			void Rotate(CQuaternion& rotation);

			/**
			 * @brief �A�N�V�������s���֐��B
			 * @param playerState �v���C���[�X�e�[�g
			*/
			void Action(EnEnemyState& playerState);

			/**
			 * @brief �X�V�֐��B�N�[���^�C���̍X�V�Ȃǂ��s���B
			*/
			void Update();
		private:
			/**
			 * @brief �N�[���^�C�������ǂ������肷��֐��B
			 * @return �N�[���^�C�����H
			*/
			bool IsCoolTime() {

				return m_coolTime > 0.0f;
			}

			/**
			 * @brief �_�b�V�������ǂ������肷��֐��B
			 * @return �_�b�V�����H
			*/
			bool IsDash() {

				return m_isDash;
			}
		private:
			bool m_isAttack = false;							//�A�^�b�N���H
			bool m_isDash = false;								//�_�b�V�����H
			float m_coolTime = 0.0f;							//�N�[���^�C��
			CVector3 m_position = CVector3::Zero;				//���W
			CQuaternion m_rotation = CQuaternion::Identity;		//��]
			CVector3 m_moveSpeed = CVector3::Zero;				//�ړ����x
			CVector3 m_rollingSpeed = CVector3::Zero;
			CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
		};
	}
}