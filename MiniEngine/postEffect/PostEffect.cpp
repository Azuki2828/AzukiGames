#include "stdafx.h"
#include "PostEffect.h"


namespace nsMyGame {

	namespace nsPostEffect {

		void CPostEffect::Init() {

			//�u���[���̏������B
			m_bloom.Init();

			//FXAA�̏������B
			m_fxaa.Init();
		}

		void CPostEffect::Render(RenderContext& rc) {
			
			//�u���[���B
			m_bloom.Render(rc);

			//FXAA�B
			m_fxaa.Render(rc);
		}
	}
}