#pragma once
#include "constPlayer.h"

namespace nsMyGame {

	namespace nsPlayer {

		//�A�j���[�V�����̃��X�g
		enum EnAnimationList {
			enAnim_Idle,
			enAnim_Walk,
			enAnim_LeftWalk,
			enAnim_RightWalk,
			enAnim_Run,
			enAnim_Attack,
			enAnim_AttackBreak,
			enAnim_Damage,
			enAnim_Rolling,
			enAnim_Guard,
			enAnim_GuardSuccess,
			enAnim_Death,

			enAnim_Num

		};

		//�A�j���[�V�����u�����h�Ɏg�p����A�j���[�V�����̃��X�g
		enum EnAnimationBlendNum {

			enAnimation_Base,
			enAnimation_Blend1,

			enAnimation_BlendNum
		};

		//�v���C���[�̃A�j���[�V�����������N���X
		class CPlayerAnimation
		{
		public:
			/**
			 * @brief �������֐��B
			*/
			void Init(CModelRender& modelRender);

			/**
			 * @brief �X�V�֐��B
			*/
			void Update(CModelRender& modelRender, const EnPlayerState& playerState);

			/**
			 * @brief �A�j���[�V�����N���b�v���擾����֐��B
			 * @return �A�j���[�V�����N���b�v
			*/
			CAnimationClip* GetAnimationClip() {

				return m_animationClip;
			}

			/**
			 * @brief �A�j���[�V�����̐����擾����֐��B
			 * @return �A�j���[�V�����̐�
			*/
			const int GetAnimationNum()const {

				return enAnim_Num;
			}

		private:
			CAnimationClip m_animationClip[enAnim_Num];		//�A�j���[�V�����N���b�v
			Animation m_animation[enAnimation_BlendNum];	//�A�j���[�V����
			Skeleton m_skeleton[enAnimation_BlendNum];		//�X�P���g��
			float m_animationSpeed = 1.0f;				//�A�j���[�V�����̍Đ����x
		};
	}
}

