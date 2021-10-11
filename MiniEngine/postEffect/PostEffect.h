#pragma once
#include "Bloom.h"
#include "FXAA.h"

namespace nsMyGame {

	namespace nsPostEffect {

		//�|�X�g�G�t�F�N�g�N���X

		class PostEffect
		{
		public:
			/**
			 * @brief �������֐��B
			*/
			void Init();

			/**
			 * @brief �`��֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void Render(RenderContext& rc);
		private:
			Bloom m_bloom;		//�u���[��
			FXAA m_fxaa;		//FXAA
		};
	}
}

