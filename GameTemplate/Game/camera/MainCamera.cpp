#include "stdafx.h"
#include <random>
#include "MainCamera.h"
#include "../player/Player.h"

namespace nsMyGame {

	bool CMainCamera::StartSub() {

		g_camera3D->SetPosition(m_position);
		g_camera3D->SetTarget(m_target);
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

	void CMainCamera::UpdateSub() {

		m_player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);
		//�J�������X�V�B
		//�����_���v�Z����B
		m_target = m_player->GetPosition();
		//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
		m_target.y += 80.0f;
		m_target += g_camera3D->GetForward() * 20.0f;

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


		CVector3 shakeTarget = CVector3::Zero;

		//�J�������h���ԂȂ�^�[�Q�b�g��h�炷�B
		if (m_state == enShake) {

			std::random_device seed_gen;
			std::mt19937 random(seed_gen());

			
			shakeTarget = { static_cast<float>(random() % 201) - 100.0f,static_cast<float>(random() % 201) - 100.0f ,static_cast<float>(random() % 201) - 100.0f};
		}

		//���_���v�Z����B
		m_position = m_target + m_toCameraPos;

		//�o�l�J�����ɒ����_�Ǝ��_��ݒ肷��B
		m_springCamera.SetFar(80000.0f);
		m_springCamera.SetPosition(m_position + shakeTarget);
		m_springCamera.SetTarget(m_target + shakeTarget);
		m_springCamera.Update();
	}
}