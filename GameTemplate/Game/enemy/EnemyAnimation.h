#pragma once
namespace nsMyGame {

	namespace nsEnemy {

		//�A�j���[�V�����̃��X�g
		enum EnAnimationList {
			enAnim_Idle,
			enAnim_Walk,
			enAnim_Run,
			enAnim_Attack,
			enAnim_Rolling,
			enAnim_ThreeCombo,

			enAnim_Num
		};

		class CEnemyAnimation
		{
		public:
			/**
			 * @brief �������֐��B
			*/
			void Init();

			/**
			 * @brief �X�V�֐��B
			*/
			void Update(CModelRender& modelRender, const EnEnemyState& enemyState);

			/**
			 * @brief �A�j���[�V�����N���b�v���擾����֐��B
			 * @return �A�j���[�V�����N���b�v
			*/
			CAnimationClip* GetAnimationClip() {

				return m_animationClip;
			}
			int GetAnimationNum()const {

				return enAnim_Num;
			}
		private:
			CAnimationClip m_animationClip[enAnim_Num];		//�A�j���[�V�����N���b�v
		};

	}
}

