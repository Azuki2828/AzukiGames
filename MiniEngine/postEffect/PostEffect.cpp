#include "stdafx.h"
#include "PostEffect.h"


namespace nsMyGame {

	namespace nsPostEffect {

		void PostEffect::Init() {

			//�u���[���̏������B
			m_bloom.Init();

			//FXAA�̏������B
			m_fxaa.Init();
		}

		void PostEffect::Render(RenderContext& rc) {

			//�u���[���̕`��B
			m_bloom.Render(rc);

			//FXAA�̕`��B
			m_fxaa.Render(rc);
		}
	}
}