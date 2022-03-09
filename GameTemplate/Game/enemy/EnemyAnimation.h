#pragma once
#include "constEnemy.h"

namespace nsMyGame {

	namespace nsEnemy {

		class CEnemyAnimation
		{
		protected:
			/**
			 * @brief �������֐��B
			*/
			virtual void Init() = 0;

			/**
			 * @brief �A�j���[�V�������Đ�����֐��B
			*/
			//virtual void PlayAnimation(CModelRender& modelRender, const EnEnemyState& enemyState) = 0;
		public:
			/**
			 * @brief �A�j���[�V�����N���b�v���擾����֐��B
			 * @return �A�j���[�V�����N���b�v
			*/
			virtual CAnimationClip* GetAnimationClip() {

				return m_animClip;
			}

			/**
			 * @brief �A�j���[�V���������擾����֐��B
			 * @return �A�j���[�V������ 
			*/
			const int GetAnimationNum()const {
				
				return m_animNum;
			}
		public:
			CAnimationClip* m_animClip;
			int m_animNum;
		};
		

	}
}

