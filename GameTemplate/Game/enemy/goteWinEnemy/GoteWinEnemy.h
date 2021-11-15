#pragma once
#include "../Enemy.h"
#include "GoteWinEnemyAttackCollisionDetection.h"

namespace nsMyGame {

	namespace nsEnemy {

		//���K���̃G�l�~�[�N���X
		class CGoteWinEnemy : public CEnemy
		{
		private:
			//�X�e�[�g
			enum EnState {
				enState_Idle,
				enState_Walk,
				enState_Attack,
				enState_Guard,
				enState_Damage,
				enState_Death,
				enState_AttackBreak,

				enState_Num
			};

			//�A�j���[�V�����̃��X�g
			enum EnAnimationList {
				enAnim_Idle,
				enAnim_Walk,
				enAnim_Attack,
				enAnim_Guard,
				enAnim_Damage,
				enAnim_Death,
				enAnim_AttackBreak,

				enAnim_Num
			};

			/**
			 * @brief �X�e�[�^�X������������֐��B
			*/
			void InitStatus();

			/**
			 * @brief �A�j���[�V�����N���b�v������������֐��B
			*/
			void InitAnimationClip();

			/**
			 * @brief �A�j���[�V�������X�V����֐��B
			*/
			void AnimationUpdate()override final;
		public:
			/**
			 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
			 * @return ���������H
			*/
			bool StartSub()override final;

			/**
			 * @brief �X�V�֐��B
			*/
			void UpdateSub()override final;

			/**
			 * @brief �X�e�[�g��ݒ肷��֐��B
			 * @param stateNum �X�e�[�g�ԍ�
			*/
			void ChangeState(int stateNum) {

				m_state = static_cast<EnState>(stateNum);
			}

			/**
			 * @brief �ړ��֐��B
			*/
			void Move()override final;

			/**
			 * @brief �g���K�[�{�b�N�X���X�V����֐��B
			 * @param pos ���W
			 * @param rot ��]
			 * @param forward �O����
			*/
			void UpdateTriggerBox(const CVector3& pos, const CQuaternion& rot, const CVector3& forward)override final;

			/**
			 * @brief �_���[�W�t���O��ݒ肷��֐��B
			 * @param receiveDamageFlag �_���[�W�t���O
			*/
			void SetReceiveDamage(const bool receiveDamageFlag)override final {

				//�_���[�W�t���O��ݒ�B
				m_receiveDamage = receiveDamageFlag;

				if (!m_receiveDamage) {
					//false�Ȃ瑁�����^�[���B
					return;
				}

				//�K�[�h��ԂȂ�
				if (m_state == enState_Guard) {

					//�v���C���[��e���B
					m_player = FindGO<nsPlayer::CPlayer>("player");
					m_player->AttackBreak();

					//�U����Ԃɐݒ�B
					m_state = enState_Attack;
					m_coolTime = 1.2f;
					return;
				}
				//�K�[�h��Ԃ���Ȃ��Ȃ�
				if (m_receiveDamage) {
					//�_���[�W�𕉂��B
					m_coolTime = 0.5f;
					m_status.hp -= 70;
					m_state = enState_Damage;
				}
			}

			/**
			 * @brief �K�[�h���ꂽ�H
			 * @return 
			*/
			bool IsGuarded()override final {

				return m_triggerBox.IsGuarded();
			}
		private:
			EnState m_state = enState_Idle;					//�X�e�[�g
			CAnimationClip m_animationClip[enAnim_Num];		//�A�j���[�V�����N���b�v
			CGoteWinEnemyCollisionDetection m_triggerBox;			//�U���p�̃g���K�[�{�b�N�X
		};
	};
}


