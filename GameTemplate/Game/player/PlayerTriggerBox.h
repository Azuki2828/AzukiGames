#pragma once
namespace nsMyGame {

	namespace nsPlayer {

		//�v���C���[�̍U�������Ɏg���g���K�[�{�b�N�X�̃N���X
		class CPlayerTriggerBox
		{
		private:

			/**
			 * @brief �g���K�[�{�b�N�X���쐬����֐��B
			 * @param pos ���W
			 * @param rot ��]
			*/
			void Create(const CVector3& pos, const CQuaternion& rot);
		public:

			/**
			 * @brief �g���K�[�{�b�N�X��L���ɂ���֐��B
			 * @param pos ���W
			 * @param rot ��]
			*/
			void Activate(const CVector3& pos, const CQuaternion& rot);

			/**
			 * @brief �g���K�[�{�b�N�X�𖳌��ɂ���֐��B
			*/
			void Deactivate();

			/**
			 * @brief �g���K�[�{�b�N�X���X�V����֐��B
			 * @param pos ���W
			 * @param rot ��]
			 * @param forward �O����
			*/
			void Update(const CVector3& pos, const CQuaternion& rot, const CVector3& forward);

		private:
			bool m_isActive = false;			//�g���K�[�{�b�N�X���L�����ǂ����H
			CVector3 m_position;				//���W
			CQuaternion m_rotation;				//��]
			CVector3 m_forward;					//�O����
			CPhysicsGhostObject m_ghostBox;		//�g���K�[�{�b�N�X
		};
	}
}

