#include "stdafx.h"
#include "Player.h"

namespace nsMyGame {

	namespace nsPlayer {

		Player* g_pCurrentPlayer = nullptr;

		void Normal() {
			g_pCurrentPlayer->GetModelRender()->PlayAnimation(enAnim_Idle);
		}

		void Yoi() {
			g_pCurrentPlayer->GetModelRender()->PlayAnimation(enAnim_Walk);
		}

		void Death() {
			g_pCurrentPlayer->GetModelRender()->PlayAnimation(enAnim_Death);
		}

		int GetYoiParam() {

			return g_pCurrentPlayer->GetYoiParam();
		}

		void ChangeState(int state) {

			g_pCurrentPlayer->SetState(state);
		}

		void Move() {
			g_pCurrentPlayer->Move();
		}

		void Drink() {

			if (g_pad[0]->IsTrigger(enButtonA)) {
				int yoiParam = g_pCurrentPlayer->GetYoiParam();
				yoiParam += 10;
				g_pCurrentPlayer->SetYoiParam(yoiParam);
			}
		}

		void LightCameraUpdate() {
			g_pCurrentPlayer->LightCameraUpdate();
		}

		void FontUpdate() {
			g_pCurrentPlayer->FontUpdate();
		}

		PYBIND11_MODULE(Game, m) {
			m.def("Normal", &Normal);
			m.def("Yoi", &Yoi);
			m.def("Death", &Death);
			m.def("Move", &Move);
			m.def("Drink", &Drink);
			m.def("GetYoiParam", &GetYoiParam);
			m.def("ChangeState", &ChangeState);
			m.def("LightCameraUpdate", &LightCameraUpdate);
			m.def("FontUpdate", &FontUpdate);
		}










		bool Player::Start() {

			m_modelRender = NewGO<ModelRender>(0);
			m_modelRender->SetFilePathTkm("Assets/modelData/knight.tkm");
			m_modelRender->SetFilePathTks("Assets/modelData/knight.tks");
			m_modelRender->SetFilePathTkm("Assets/unityChanBeer.tkm");
			m_modelRender->SetFilePathTks("Assets/unityChanBeer.tks");
			m_animationClip[enAnim_Walk].Load("Assets/animData/walk.tka");
			m_animationClip[enAnim_Idle].Load("Assets/animData/idle.tka");
			m_animationClip[enAnim_Death].Load("Assets/animData/KneelDown.tka");
			m_animationClip[enAnim_Walk].SetLoopFlag(true);
			m_animationClip[enAnim_Idle].SetLoopFlag(true);
			m_animationClip[enAnim_Death].SetLoopFlag(false);
			m_modelRender->InitAnimation(m_animationClip, enAnimNum);
			m_modelRender->SetAnimFlg(true);
			m_modelRender->SetShadowCasterFlag(true);
			m_modelRender->SetShadowReceiverFlag(true);
			m_modelRender->SetModelUpAxis(EnModelUpAxis::enModelUpAxisY);
			m_modelRender->Init();

			m_fontRender = NewGO<nsFont::FontRender>(0);
			m_fontRender->Init(L"�����x�F", { -550.0f,310.0f });	//�ꏊ
			m_fontRender->SetColor({ 1.0f,0.0f,0.0f,1.0f });			//�ԐF
			m_fontRender->SetShadowParam(true, 1.0f, Vector4::Black);

			m_fontRender2 = NewGO<nsFont::FontRender>(0);
			m_fontRender2->Init(L"A�F����", { 450.0f,310.0f });	//�ꏊ
			m_fontRender2->SetColor({ 1.0f,0.0f,0.0f,1.0f });			//�ԐF
			m_fontRender2->SetShadowParam(true, 1.0f, Vector4::Black);
			return true;
		}

		void Player::StateUpdate() {

			//���݂̃C���X�^���X�����B
			g_pCurrentPlayer = this;

			//Python�X�N���v�g�����[�h����B
			switch (m_playerState) {
			case EnPlayerState::enState_Normal:

				//�ʏ�
				ImportModule("PlayerNormal");
				break;
			case EnPlayerState::enState_Yoi:

				//�ق�悢
				ImportModule("PlayerYoi");
				break;
			case EnPlayerState::enState_Death:

				//�}���A���R�[������
				ImportModule("PlayerDeath");
				break;
			}

			//Python�X�N���v�g�̒���Update()�֐����Ăяo���B
			auto updateFunc = m_playerPyModule.attr("Update");
			updateFunc();
		}


		void Player::Update() {

			//�X�e�[�g�ɂ���ēǂݍ���Python�X�N���v�g��؂�ւ���B
			StateUpdate();
		}












		void Player::LightCameraUpdate() {

			//���C�g�J�����̏����X�V
			Vector3 m_lightCameraTar = m_pos;
			Vector3 m_lightCameraPos = m_lightCameraTar;

			//���C�g�J�����̍��W��ݒ�
			m_lightCameraPos.y += 300.0f;
			m_lightCameraPos.z += 300.0f;

			//���C�g�J�����̏���ݒ�
			Camera::GetLightCamera()->SetPosition(m_lightCameraPos);
			Camera::GetLightCamera()->SetTarget(m_lightCameraTar);
			Camera::GetLightCamera()->SetFar(800.0f);

			//�J�����̏���������߂�B
			Vector3 Vec_x = Vector3::AxisX;
			Vector3 TarPos = Camera::GetLightCamera()->GetTarget() - Camera::GetLightCamera()->GetPosition();
			TarPos.Normalize();
			Vector3 CameraUp;

			CameraUp.Cross(TarPos, Vec_x);
			CameraUp.Normalize();
			Camera::GetLightCamera()->SetUp(CameraUp);
			Camera::GetLightCamera()->Update();
		}

		void Player::Move() {

			if (g_pad[0]->IsPress(enButtonRight)) {
				m_pos.x -= 2.0f;
			}
			if (g_pad[0]->IsPress(enButtonLeft)) {
				m_pos.x += 2.0f;
			}
			if (g_pad[0]->IsPress(enButtonUp)) {
				m_pos.z -= 2.0f;
			}
			if (g_pad[0]->IsPress(enButtonDown)) {
				m_pos.z += 2.0f;
			}

			m_modelRender->SetPosition(m_pos);
		}

		void Player::FontUpdate() {

			wchar_t time[64];
			swprintf_s(time, L"�����x�F%d", m_yoiParam);

			if (m_yoiParam >= 60 && m_yoiParam < 100) {
				m_color = { 1.0f,0.0f,0.0f,1.0f };
			}
			else if (m_yoiParam >= 100) {
				switch (m_colorState) {
				case en1:
					m_color.y += 0.05f;
					if (m_count == 20) {
						m_colorState = en2;
						m_count = 0;
					}
					break;
				case en2:
					m_color.x -= 0.05f;
					if (m_count == 20) {
						m_colorState = en3;
						m_count = 0;
					}
					break;
				case en3:
					m_color.z += 0.05f;
					if (m_count == 20) {
						m_colorState = en4;
						m_count = 0;
					}
					break;
				case en4:
					m_color.y -= 0.05f;
					if (m_count == 20) {
						m_colorState = en5;
						m_count = 0;
					}
					break;
				case en5:
					m_color.x += 0.05f;
					if (m_count == 20) {
						m_colorState = en6;
						m_count = 0;
					}
					break;
				case en6:
					m_color.z -= 0.05f;
					if (m_count == 20) {
						m_colorState = en1;
						m_count = 0;
					}
					break;
				}
				m_count++;
				swprintf_s(time, L"�����x�F�}���A���R�[������");
			}
			m_fontRender->SetText(time);
			m_fontRender->SetColor(m_color);
		}
	}
}