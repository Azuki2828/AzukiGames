#pragma once
#include "EnemyAction.h"
#include "EnemyAnimation.h"
#include "../player/Player.h"
#include "../../../ExEngine/physics/CharacterController.h"

namespace nsMyGame {

	namespace nsPlayer {

		class CPlayer;
	}

	namespace nsEnemy {

		//�G�l�~�[�N���X
		class CEnemy : public CIGameObject
		{
		protected:

			//�X�e�[�^�X
			struct SStatus {
				int hp = 0;			//�̗�
				int attack = 0;		//�U����
			};

			/**
			 * @brief ���W���[�����C���|�[�g����֐��B
			 * @param moduleName ���W���[����(Python�t�@�C����)
			*/
			void ImportModule(const char* moduleName) {
				// ���W���[�����C���|�[�g
				try {
					m_enemyPyModule = pybind11::module::import(moduleName);
				}
				catch (pybind11::error_already_set& e) {
					MessageBoxA(nullptr, e.what(), "�G���[", MB_OK);
				}
			}

			/**
			 * @brief �O�������X�V����֐��B
			*/
			void UpdateForward();
		public:
			/**
			 * @brief �f�X�g���N�^�B
			*/
			~CEnemy();

			/**
			 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
			 * @return ���������H
			*/
			bool Start() override;

			
			/**
			 * @brief �X�V�֐��B
			*/
			void Update() override;

			

			/**
			 * @brief �v���C���[�Ƃ̋��������߂�֐��B
			 * @return �v���C���[�Ƃ̋����B
			*/
			const float GetLengthToPlayer()const {

				//�v���C���[�ɐL�т�x�N�g�������߂�B
				CVector3 length = m_player->GetPosition() - m_position;

				//������Ԃ��B
				return length.Length();
			}

			
			/**
			 * @brief �`��֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void Render(CRenderContext& rc);

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

			/**
			 * @brief ��]���擾����֐��B
			 * @return ��]
			*/
			const CQuaternion& GetRotation()const {

				return m_rotation;
			}

			/**
			 * @brief �N�[���^�C����ݒ肷��֐��B
			 * @param coolTime �N�[���^�C��
			*/
			void SetCoolTime(const float coolTime) {

				m_coolTime = coolTime;
			}

			/**
			 * @brief �N�[���^�C�����擾����֐��B
			 * @return �N�[���^�C��
			*/
			const float GetCoolTime()const {

				return m_coolTime;
			}

			/**
			 * @brief �L�����N�^�[�R���g���[���[���擾����֐��B
			 * @return �L�����N�^�[�R���g���[���[
			*/
			CharacterController& GetCharacterController() {

				return m_charaCon;
			}

			/**
			 * @brief ���g���폜����֐��B
			*/
			void Delete() {
				DeleteGO(this);
			}

			/**
			 * @brief ����������ł���H
			 * @return HP���O�ȉ��H�i����ł���H�j
			*/
			const bool IsDeath()const {

				return m_status.hp <= 0;
			}

			/**
			 * @brief �_���[�W���󂯂Ă���H
			 * @return �_���[�W�t���O
			*/
			const bool GetReceiveDamage()const {

				return m_receiveDamage;
			}

			/**
			 * @brief �O�������擾����֐��B
			 * @return �O����
			*/
			const CVector3& GetForward()const {

				return m_forward;
			}

		public:
			/**
			 * @brief �h���N���X�p��Start()�֐��B
			 * @return ���������H
			*/
			virtual bool StartSub() = 0;

			/**
			 * @brief �h���N���X�p��Update()�֐��B
			*/
			virtual void UpdateSub() = 0;

			/**
			 * @brief �X�e�[�g��ω�������֐��B
			 * @param stateNum �X�e�[�g�ԍ�
			*/
			virtual void ChangeState(int stateNum) = 0;

			/**
			 * @brief �g���K�[�{�b�N�X���X�V����֐��B
			 * @param pos ���W
			 * @param rot ��]
			 * @param forward �O����
			*/
			virtual void UpdateTriggerBox(const CVector3& pos, const CQuaternion& rot, const CVector3& forward) = 0;

			/**
			 * @brief �ړ��֐��B
			*/
			virtual void Move() = 0;

			/**
			 * @brief ��]�֐��B
			*/
			virtual void Rotate();

			/**
			 * @brief �A�j���[�V�������X�V����֐��B
			*/
			virtual void AnimationUpdate() = 0;

			/**
			 * @brief �_���[�W�t���O��ݒ肷��֐��B
			 * @param receiveDamageFlag �_���[�W�t���O
			*/
			virtual void SetReceiveDamage(bool receiveDamageFlag) {

				m_receiveDamage = receiveDamageFlag;
			}
		protected:
			bool m_receiveDamage = false;								//�_���[�W���󂯂����H�i���Ƃ�0�_���[�W�ł��j
			SStatus m_status;											//�X�e�[�^�X
			CModelRender* m_modelRender = nullptr;						//���f��
			CVector3 m_position = {1200.0f,500.0f,-1200.0f};			//���W
			CQuaternion m_rotation = CQuaternion::Identity;				//��]
			float m_coolTime = 0.0f;									//�N�[���^�C��
			CharacterController m_charaCon;								//�L�����N�^�[�R���g���[���[
			CVector3 m_moveSpeed = CVector3::Zero;						//�ړ����x
			CVector3 m_forward = CVector3::Zero;						//�O����
			pybind11::module m_enemyPyModule;							//Python�̃��W���[��

			nsPlayer::CPlayer* m_player = nullptr;						
		};
	}
}

