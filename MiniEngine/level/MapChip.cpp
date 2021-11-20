#include "stdafx.h"
#include "MapChip.h"
#include "Level.h"
#include "Material.h"


namespace nsMyGame {


	struct LevelObjectData;

	MapChip::MapChip(const LevelObjectData& objData) {

		char objName[256];
		wcstombs(objName, objData.name, 256);

		char* p;
		p = strstr(objName, "Coll");

		if (p == nullptr) {

			m_modelRender = NewGO<CModelRender>(0);
			//m_skinModelRender->SetFileNametks("Assets/modelData/Player_N.tks");
			//m_skinModelRender->Init(true, false);


			char filePathtkm[256];
			sprintf(filePathtkm, "Assets/modelData/backGround/%s.tkm", objName);
			m_modelRender->SetFilePathTkm(static_cast<const char*>(filePathtkm));

			m_modelRender->SetShadowReceiverFlag(true);
			m_modelRender->Init();


			m_modelRender->SetPosition(objData.position);
			m_modelRender->SetRotation(objData.rotation);
			m_modelRender->SetScale(objData.scale);
			m_modelRender->UpdateWorldMatrix();

			m_physicsStaticObject.CreateFromModel(
				*m_modelRender->GetModel(),
				m_modelRender->GetModel()->GetWorldMatrix()
			);
			m_physicsStaticObject.SetFriction(10.0f);
		}
		else {
			m_modelRender = NewGO<CModelRender>(0);


			char filePathtkm[256];
			strcpy(objName, (p+4));
			sprintf(filePathtkm, "Assets/modelData/backGround/%s.tkm", objName);
			m_modelRender->SetFilePathTkm(static_cast<const char*>(filePathtkm));

			m_modelRender->SetShadowCasterFlag(true);
			m_modelRender->SetShadowReceiverFlag(true);
			m_modelRender->Init();


			m_modelRender->SetPosition(objData.position);
			m_modelRender->SetRotation(objData.rotation);
			m_modelRender->SetScale(objData.scale);
			m_modelRender->UpdateWorldMatrix();


			char filePathtkm2[256];
			sprintf(filePathtkm2, "Assets/modelData/backGround/Coll%s.tkm", p);
			m_collisionModelRender = NewGO<CModelRender>(0);
			m_collisionModelRender->SetFilePathTkm(static_cast<const char*>(filePathtkm2));

			m_collisionModelRender->Init();


			m_collisionModelRender->SetPosition(objData.position);
			m_collisionModelRender->SetRotation(objData.rotation);
			m_collisionModelRender->SetScale(objData.scale);
			m_collisionModelRender->UpdateWorldMatrix();

			m_collisionModelRender->SetCollisionModelFlag(true);

			m_physicsStaticObject.CreateFromModel(
				*m_collisionModelRender->GetModel(),
				m_collisionModelRender->GetModel()->GetWorldMatrix()
			);
			m_physicsStaticObject.SetFriction(10.0f);
		}
	}

	MapChip::~MapChip() {
		if (m_modelRender != nullptr) {
			DeleteGO(m_modelRender);
		}
		if (m_collisionModelRender != nullptr) {
			DeleteGO(m_collisionModelRender);
		}
	}

	void MapChip::Draw(CRenderContext& rc) {
		//Draw(rc,
		//	m_skinModelRender->GetModel()->GetWorldMatrix(),
		//	g_camera3D->GetViewMatrix(),
		//	g_camera3D->GetProjectionMatrix());

	}

	void MapChip::Draw(CRenderContext& rc,
		const CMatrix& mWorld,
		const CMatrix& mView,
		const CMatrix& mProj) {
		//���b�V�����ƂɃh���[
		//�v���~�e�B�u�̃g�|���W�[�̓g���C�A���O�����X�g�̂݁B
		rc.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�萔�o�b�t�@���X�V����B
		MConstantBuffer cb;
		cb.mWorld = mWorld;
		cb.mView = mView;
		cb.mProj = mProj;

		m_constantBuffer.CopyToVRAM(&cb);

		//if (m_expandData) {
		//	m_expandConstantBuffer.CopyToVRAM(m_expandData);
		//}
		//if (m_boneMatricesStructureBuffer.IsInited()) {
		//	//�{�[���s����X�V����B
		//	m_boneMatricesStructureBuffer.Update(m_skeleton->GetBoneMatricesTopAddress());
		//}
		int descriptorHeapNo = 0;
		for (auto& mesh : m_meshs) {
			//1. ���_�o�b�t�@��ݒ�B
			rc.SetVertexBuffer(mesh->m_vertexBuffer);
			//�}�e���A�����ƂɃh���[�B
			for (int matNo = 0; matNo < mesh->m_materials.size(); matNo++) {
				//���̃}�e���A�����\���Ă��郁�b�V���̕`��J�n�B
				mesh->m_materials[matNo]->BeginRender(rc, mesh->skinFlags[matNo]);
				//2. �f�B�X�N���v�^�q�[�v��ݒ�B
				rc.SetDescriptorHeap(m_descriptorHeap.at(descriptorHeapNo));
				//3. �C���f�b�N�X�o�b�t�@��ݒ�B
				auto& ib = mesh->m_indexBufferArray[matNo];
				rc.SetIndexBuffer(*ib);

				//4. �h���[�R�[�������s�B
				rc.DrawIndexed(ib->GetCount());
				descriptorHeapNo++;
			}
		}
	}
}