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

			//�G�̃X�e�[�^�X
			struct SEnemyStatus {
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

			void UpdateForward();
		public:
			/**
			 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
			 * @return ���������H
			*/
			bool Start() override;

			/**
			 * @brief �h���N���X�p��Start()�֐��B
			 * @return ���������H
			*/
			virtual bool StartSub() = 0;

			/**
			 * @brief �X�V�֐��B
			*/
			void Update() override;

			/**
			 * @brief �h���N���X�p��Update()�֐��B
			*/
			virtual void UpdateSub() = 0;

			/**
			 * @brief �X�e�[�g��ω�������֐��B
			 * @param stateNum �X�e�[�g�ԍ�
			*/
			virtual void ChangeState(int stateNum) = 0;


			float GetLengthToPlayer()const {

				

				CVector3 length = m_player->GetPosition() - m_position;

				return length.Length();
			}

			virtual void Move() = 0;

			virtual void Rotate();
			/**
			 * @brief �`��֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void Render(CRenderContext& rc);

			void SetPosition(const CVector3& pos) {

				m_position = pos;
			}

			void SetCoolTime(const float coolTime) {

				m_coolTime = coolTime;
			}

			float GetCoolTime()const {

				return m_coolTime;
			}


		protected:
			CModelRender* m_modelRender = nullptr;			//���f��
			CVector3 m_position = {0.0f,0.0f,500.0f};			//���W
			CQuaternion m_rotation = CQuaternion::Identity;

			float m_coolTime = 0.0f;

			CharacterController m_charaCon;
			CVector3 m_moveSpeed = CVector3::Zero;
			CVector3 m_forward = CVector3::Zero;

			nsPlayer::CPlayer* m_player = nullptr;
			pybind11::module m_enemyPyModule;				//Python�̃��W���[��
		};
	}
}

