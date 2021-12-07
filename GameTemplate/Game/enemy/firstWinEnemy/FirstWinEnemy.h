#pragma once
#include "../Enemy.h"
#include "FirstWinEnemyAttackCollisionDetection.h"

namespace nsMyGame {

	namespace nsEnemy {
		 
		class CFirstWinEnemy : public CEnemy
		{
		private:
			//�X�e�[�g
			enum EnState {
				enState_Idle,
				enState_Walk,
				enState_ThreeCombo,
				enState_Damage,
				enState_Death,
				enState_AttackBreak,

				enState_Num
			};

			//�A�j���[�V�����̃��X�g
			enum EnAnimationList {
				enAnim_Idle,
				enAnim_Walk,
				enAnim_ThreeCombo,
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

			// �A�j���[�V�����C�x���g�p�̊֐��B
			void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
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

				m_receiveDamage = receiveDamageFlag;

				//�_���[�W��^����B
				if (m_receiveDamage) {
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
			bool m_isAttack = false;						//�U�����H
			EnState m_state = enState_Idle;					//�X�e�[�g
			CAnimationClip m_animationClip[enAnim_Num];		//�A�j���[�V�����N���b�v
			CFirstWinEnemyAttackCollisionDetection m_triggerBox;			//�U���p�̃g���K�[�{�b�N�X
		};
	}
}
