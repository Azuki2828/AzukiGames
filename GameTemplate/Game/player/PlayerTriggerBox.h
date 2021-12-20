#pragma once
namespace nsMyGame {

	namespace nsPlayer {

		//�v���C���[�̍U�������Ɏg���g���K�[�{�b�N�X�̃N���X
		class CPlayerTriggerBox
		{
		public:
			/**
			 * @brief �U���̓����蔻����쐬����֐��B
			 * @param pos ���W
			 * @param rot ��]
			*/
			void Create(const CVector3& pos, const CQuaternion& rot) {

				m_attackCollision.CreateBox(pos, rot, c_attackTriggerBoxSize);
			}
			
			/**
			 * @brief �g���K�[�{�b�N�X��L���ɂ���֐��B
			*/
			void Activate() {

				m_isActive = true;
			}

			/**
			 * @brief �g���K�[�{�b�N�X�𖳌��ɂ���֐��B
			*/
			void Deactivate() {

				m_isActive = false;
			}

			/**
			 * @brief ���W�Ɖ�]���X�V����֐��B
			 * @param worldMatrix ���[���h�s��
			*/
			void UpdatePositionAndRotation(const CMatrix& worldMatrix) {

				CVector3 position;
				position.x = worldMatrix.m[3][0];
				position.y = worldMatrix.m[3][1];
				position.z = worldMatrix.m[3][2];
				m_attackCollision.SetPosition(position);
				m_position = position;

				CQuaternion rotation;
				rotation.SetRotation(worldMatrix);
				m_attackCollision.SetRotation(rotation);
			}

			/**
			 * @brief �g���K�[�{�b�N�X���X�V����֐��B
			*/
			void Update();

		private:
			bool m_isActive = false;			//�g���K�[�{�b�N�X���L�����ǂ����H
			CVector3 m_position = CVector3::Zero;	//���W
			CPhysicsGhostObject m_attackCollision;		//�g���K�[�{�b�N�X
		};
	}
}

