#include "stdafx.h"
#include "BackGroundObject.h"

namespace nsMyGame {

	namespace {

		constexpr float c_objFriction = 10.0f;		//���C
	}

	void CBackGroundObject::InitModel(const char* fileName,
		const CVector3& position, 
		const CQuaternion& rotation, 
		const CVector3& scale,
		const bool isCollision
	)
	{
		//���f���𐶐��B
		m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);

		//�t�@�C���p�X���w��B
		m_modelRender->SetFilePathTkm(fileName);

		//�V���h�E���V�[�o�[�t���O��ݒ�B
		m_modelRender->SetShadowReceiverFlag(true);

		//�������B
		m_modelRender->Init();

		//�e�p�����[�^��ݒ�B
		m_modelRender->SetPosition(position);	//���W
		m_modelRender->SetRotation(rotation);	//��]
		m_modelRender->SetScale(scale);			//�g��

		//�p�����[�^���X�V�B
		m_modelRender->UpdateWorldMatrix();

		//�R���W�����𐶐�����H
		if (isCollision) {

			//���f���𖳎��i�`�悵�Ȃ��悤�Ɂj����H
			if (m_isIgnoreObject) {

				m_modelRender->SetCollisionModelFlag(true);
			}

			//�R���W�����𐶐��B
			m_physicsStaticObject.CreateFromModel(
				*m_modelRender->GetModel(),
				m_modelRender->GetModel()->GetWorldMatrix()
			);

			//���C��ݒ�B
			m_physicsStaticObject.SetFriction(c_objFriction);
		}
	}

	void CBackGroundObject::OnDestroy() {

		//���f�����폜�B
		if (m_modelRender != nullptr) {
			DeleteGO(m_modelRender);
			m_modelRender = nullptr;
		}
	}
}
