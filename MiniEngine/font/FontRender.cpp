#include "stdafx.h"
#include "FontRender.h"


namespace nsMyGame {

	namespace nsFont {

		void CFontRender::Init(
			const wchar_t* text,
			const Vector2& position,
			const Vector4& color,
			const float rotation,
			const float scale,
			const Vector2& pivot
		) {
			//�e�X�̃p�����[�^�[��ݒ�B
			swprintf_s(m_fontValue.text, text);
			m_fontValue.position = position;
			m_fontValue.color = color;
			m_fontValue.rotation = rotation;
			m_fontValue.scale = scale;
			m_fontValue.pivot = pivot;
		}

		void CFontRender::Render(RenderContext& rc) {


			//�`�惂�[�h���t�H���g�p�̎������`�悷��B
			if (rc.GetRenderMode() == RenderContext::EnRender_Mode::enRenderMode_Font) {
				m_font.Begin(rc);

				//�t�H���g��`��B
				m_font.Draw(
					m_fontValue.text,
					m_fontValue.position,
					m_fontValue.color,
					m_fontValue.rotation,
					m_fontValue.scale,
					m_fontValue.pivot
				);

				m_font.End(rc);
			}
		}
	}
}