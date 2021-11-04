#pragma once
#include "../Enemy.h"
#include "FirstWinEnemyTriggerBox.h"

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

				enState_Num
			};

			//�A�j���[�V�����̃��X�g
			enum EnAnimationList {
				enAnim_Idle,
				enAnim_Walk,
				enAnim_ThreeCombo,
				enAnim_Damage,
				enAnim_Death,

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
			void SetReceiveDamage(bool receiveDamageFlag)override final {

				m_receiveDamage = receiveDamageFlag;

				//�_���[�W��^����B
				if (m_receiveDamage) {
					m_coolTime = 0.5f;
					m_status.hp -= 70;
					m_state = enState_Damage;
				}
			}
		private:
			EnState m_state = enState_Idle;					//�X�e�[�g
			CAnimationClip m_animationClip[enAnim_Num];		//�A�j���[�V�����N���b�v
			CFirstWinEnemyTriggerBox m_triggerBox;			//�U���p�̃g���K�[�{�b�N�X
		};
	}
}
