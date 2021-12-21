#pragma once
#include "../Enemy.h"
#include "BossAttackCollisionDetection.h"
#include "../../AttackCollision.h"

namespace nsMyGame {

	namespace nsEnemy {

		//�{�X�N���X
		class CBoss : public CEnemy
		{
		private:
			//�X�e�[�g
			enum EnState {
				enState_Idle,
				enState_Walk,
				enState_JumpAttack,
				enState_SwipingAttack,
				enState_Damage,
				enState_Death,
				enState_AttackBreak,
				enState_Scream,

				enState_Num
			};

			//�A�j���[�V�����̃��X�g
			enum EnAnimationList {
				enAnim_Idle,
				enAnim_Walk,
				enAnim_JumpAttack,
				enAnim_SwipingAttack,
				enAnim_Damage,
				enAnim_Death,
				enAnim_AttackBreak,
				enAnim_Scream,

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
			 * @brief �ʏ�ړ��֐��B
			*/
			void MoveCommon();

			/**
			 * @brief �W�����v�U�����̈ړ��֐��B
			*/
			void JumpAttackMove();

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
					m_status.hp -= 30;
				}
			}

			/**
			 * @brief �K�[�h���ꂽ�H
			 * @return�K�[�h���ꂽ���ǂ����̔���
			*/
			bool IsGuarded()override final {

				return m_triggerBox.IsGuarded();
			}

			/**
			 * @brief �v���C���[�ɋC�Â����H
			 * @return �v���C���[�ɋC�Â������ǂ����̔���
			*/
			const bool NoticePlayer()const {

				return m_noticePlayer;
			}

			/**
			 * @brief �v���C���[�ɋC�Â����߂̊֐��B
			*/
			void FindPlayer();
		private:
			Bone* m_swordBone = nullptr;							//���Ɏ��t����ꂽ�{�[��
			EnState m_state = enState_Idle;							//�X�e�[�g
			CAnimationClip m_animationClip[enAnim_Num];				//�A�j���[�V�����N���b�v
			CBossCollisionDetection m_triggerBox;					//�U���p�̃g���K�[�{�b�N�X

			bool m_canMove = false;									//�ړ��ł���H
			bool m_noticePlayer = false;							//�v���C���[�ɋC�Â����H
			CPhysicsGhostObject m_noticePlayerTriggerBox;			//�v���C���[�ɋC�Â����߂̃g���K�[
			CVector3 m_vecToPlayer = CVector3::Zero;				//�v���C���[�ɐL�т�x�N�g��
		};
	}
}
