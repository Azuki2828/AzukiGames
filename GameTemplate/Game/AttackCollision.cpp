#include "stdafx.h"
#include "AttackCollision.h"

namespace nsMyGame {

	CAttackCollision::~CAttackCollision() {

		//�R���W�������폜�B
		m_ghostBox.Release();
	}

	bool CAttackCollision::Start() {

		//�L�����Ԃ��ݒ肳��ĂȂ��Ȃ�G���[�\���B
		if (m_activeTime <= 0.0f) {
			
			MessageBox(nullptr, L"�����蔻��̗L�����Ԃ��ݒ肳��Ă��܂���B", L"�x��", MB_OK);

			return false;
		}

		return true;
	}

	void CAttackCollision::CreateBox(const CVector3& pos, const CQuaternion& rot, const CVector3& size) {

		m_ghostBox.CreateBox(pos, rot, size);
	}

	void CAttackCollision::Update() {

		//�L���^�C�����؂�Ă��Ȃ��Ȃ�^�C�����X�V�B
		if (m_activeTime > 0.0f) {

			m_activeTime -= GameTime().GameTimeFunc().GetFrameDeltaTime();
		}
		//�^�C�����؂ꂽ�炱�̓����蔻����폜�B
		else {
			
			DeleteGO(this);
		}
	}
}