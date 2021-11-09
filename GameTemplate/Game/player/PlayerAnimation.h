#pragma once

namespace nsMyGame {

	namespace nsPlayer {

		//�A�j���[�V�����̃��X�g
		enum EnAnimationList {
			enAnim_Idle,
			enAnim_Walk,
			enAnim_Run,
			enAnim_Attack,
			enAnim_AttackBreak,
			enAnim_Damage,
			enAnim_Rolling,
			enAnim_ThreeCombo,
			enAnim_Guard,

			enAnim_Num

		};

		class CPlayerAnimation
		{
		public:
			/**
			 * @brief �������֐��B
			*/
			void Init();

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
			const int GetAnimationNum()const {

				return enAnim_Num;
			}

		private:
			CAnimationClip m_animationClip[enAnim_Num];		//�A�j���[�V�����N���b�v
		};
	}
}

