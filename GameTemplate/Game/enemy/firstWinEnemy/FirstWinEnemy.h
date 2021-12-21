#pragma once
#include "../Enemy.h"
#include "FirstWinEnemyAttackCollisionDetection.h"
#include "../../AttackCollision.h"

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
				enState_Back,

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
				enAnim_Back,

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

			/**
			 * @brief �A�j���[�V�����C�x���g�p�̊֐��B
			 * @param clipName �A�j���[�V�����̖��O
			 * @param eventName �A�j���[�V�����C�x���g�̃L�[�̖��O
			*/
			void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

			/**
			 * @brief �U���p�̓����蔻����쐬����֐��B
			*/
			void CreateAttackCollision();
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
			void UpdateTriggerBox()override final;

			/**
			 * @brief �_���[�W�t���O��ݒ肷��֐��B
			 * @param receiveDamageFlag �_���[�W�t���O
			*/
			void SetReceiveDamage(const bool receiveDamageFlag)override final {

				m_receiveDamage = receiveDamageFlag;

				//�_���[�W��^����B
				if (m_receiveDamage) {
					m_coolTime = 0.3f;
					m_status.hp -= 30;
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
			Bone* m_swordBone = nullptr;							//���Ɏ��t����ꂽ�{�[��
			EnState m_state = enState_Idle;							//�X�e�[�g
			CAnimationClip m_animationClip[enAnim_Num];				//�A�j���[�V�����N���b�v
			CFirstWinEnemyAttackCollisionDetection m_triggerBox;	//�U���p�̃g���K�[�{�b�N�X
		};
	}
}
