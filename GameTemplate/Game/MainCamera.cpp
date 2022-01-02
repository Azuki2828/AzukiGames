#include "stdafx.h"
#include "MainCamera.h"
#include "player/Player.h"
#include "enemy/boss/Boss.h"

namespace nsMyGame {

	bool CMainCamera::Start() {

		g_camera3D->SetPosition(m_pos);
		g_camera3D->SetTarget(m_tar);
		g_camera3D->SetFar(80000.0f);

		//�΂˃J�����̏������B
		m_springCamera.Init(
			*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��B
			1000.0f,			//�J�����̈ړ����x�̍ő�l�B
			true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
			5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
		);

		return true;
	}

	void CMainCamera::Update() {

		CVector3 pos;
		CVector3 target;

		if (m_state == enNormal) {
			m_player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);
			//�J�������X�V�B
			//�����_���v�Z����B
			target = m_player->GetPosition();
			//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
			target.y += 80.0f;
			target += g_camera3D->GetForward() * 20.0f;

			CVector3 toCameraPosOld = m_toCameraPos;
			//�p�b�h�̓��͂��g���ăJ�������񂷁B
			float x = g_pad[0]->GetRStickXF();
			float y = g_pad[0]->GetRStickYF();
			//Y������̉�]
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
			qRot.Apply(m_toCameraPos);
			//X������̉�]�B
			CVector3 axisX;
			axisX.Cross(CVector3::AxisY, m_toCameraPos);
			axisX.Normalize();
			qRot.SetRotationDeg(axisX, 2.0f * y);
			qRot.Apply(m_toCameraPos);

			//�J�����̉�]�̏�����`�F�b�N����B
			//�����_���王�_�܂ł̃x�N�g���𐳋K������B
			//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
			//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
			CVector3 toPosDir = m_toCameraPos;
			toPosDir.Normalize();
			if (toPosDir.y < -0.5f) {
				//�J����������������B
				m_toCameraPos = toCameraPosOld;
			}
			else if (toPosDir.y > 0.8f) {
				//�J�����������������B
				m_toCameraPos = toCameraPosOld;
			}


			//���_���v�Z����B
			pos = target + m_toCameraPos;

			
		}
		else {
			m_eventTimer += GameTime::GameTimeFunc().GetFrameDeltaTime();

			if (m_eventTimer < 5.0f) {

				auto boss = FindGO<nsEnemy::CBoss>(c_classNameBoss);

				auto bossPos = boss->GetPosition();

				target = bossPos;
				//x-300
				pos = { 1380.37f,10.68f,3355.02f };

				//�������ɂ͂Ȃ�Ȃ��B
				if (target.y < 10.68f) {
					target.y = 10.68f;
				}
			}
			else {
				//x-300
				pos = { 1380.37f,10.68f + (m_eventTimer - 5.0f) * 50.0f,3355.02f };

				target = pos;

				target.x += 100.0f;
			}
		}

		//�o�l�J�����ɒ����_�Ǝ��_��ݒ肷��B
		m_springCamera.SetFar(80000.0f);
		m_springCamera.SetPosition(pos);
		m_springCamera.SetTarget(target);
		m_springCamera.Update();
	}
}