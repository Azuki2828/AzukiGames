#include "stdafx.h"
#include "LockOnMarker.h"

namespace {

	constexpr const char* c_lockOnMarkerFilePath = "Assets/Image/lockOnMarker_white.dds";		//�A�C�R���̃t�@�C���p�X
	const CVector2 c_lockOnMarkerWH = { 200.0f,180.0f };										//�A�C�R���̕��ƍ���
	constexpr short c_markerSpeedMul = 15;														//�A�C�R�����x
	constexpr float c_scaleBase = 0.2f;															//�J�n���̊g�嗦
}

namespace nsMyGame {

	namespace nsCamera {

		//�ڕW�ƂȂ�g�嗦�̒�`
		const float CLockOnMarker::m_stepScale[] = {

			0.50f,
			0.20f,
			0.30f
		};

		void CLockOnMarker::Init() {

			//���b�N�I���A�C�R�����������B
			m_lockOnMarker = NewGO<CSpriteRender>(enPriority_Fifth);
			m_lockOnMarker->Init(c_lockOnMarkerFilePath, c_lockOnMarkerWH.x, c_lockOnMarkerWH.y);

			//�p�����[�^���������B
			m_sizeStep = 0;										//�X�e�b�v
			m_position = CVector3::Zero;						//���W
			m_scale = c_scaleBase;										//�g��
			m_scaleDiff = m_stepScale[m_sizeStep] - m_scale;	//�g�嗦�ϓ��̒l
			m_updateNum = 0;									//�g�嗦�X�V��
		}

		void CLockOnMarker::Release() {

			//����B
			if (m_lockOnMarker != nullptr) {
				DeleteGO(m_lockOnMarker);
				m_lockOnMarker = nullptr;
			}
		}

		void CLockOnMarker::UpdateMarker(const CVector2& position) {

			//�g�嗦���X�V�B
			UpdateScale();

			//���W���X�V�B
			m_lockOnMarker->SetPosition(position);
		}

		void CLockOnMarker::UpdateScale() {

			//���݂̃X�e�b�v���݌v�X�e�b�v���𒴂��Ă��Ȃ��Ȃ�(1�����z��Ȃ̂�0�Ԗڂ��Q��)
			if (std::extent<decltype(m_stepScale), 0>::value > m_sizeStep) {

				//1�t���[��������̊g�嗦�̓��������߂ĉ��Z�B
				m_scale += m_scaleDiff / static_cast<float>(c_markerSpeedMul);
				m_updateNum++;

				//���񐔂ɓ��B�����玟�̃X�e�b�v�ɁB
				if (m_updateNum == c_markerSpeedMul) {

					//�X�e�b�v�A�g�嗦�ϓ��̒l�A�񐔂�ύX�B
					m_sizeStep++;
					m_scaleDiff = m_stepScale[m_sizeStep] - m_scale;
					m_updateNum = 0;
				}

				//�g�嗦���X�V�B
				m_lockOnMarker->SetScale({ m_scale ,m_scale ,m_scale });
			}
		}
	}
}