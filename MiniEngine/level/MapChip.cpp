#include "stdafx.h"
#include "MapChip.h"
#include "Level.h"
#include "Material.h"


namespace nsMyGame {


	struct LevelObjectData;

	MapChip::MapChip(const LevelObjectData& objData) {

		char objName[256];
		wcstombs(objName, objData.name, 256);


		m_modelRender = NewGO<CModelRender>(0);
		//m_skinModelRender->SetFileNametks("Assets/modelData/Player_N.tks");
		//m_skinModelRender->Init(true, false);


		char filePathtkm[256];
		sprintf(filePathtkm, "Assets/modelData/backGround/%s.tkm", objName);
		m_modelRender->SetFilePathTkm(static_cast<const char*>(filePathtkm));

		//char filePathtks[256];
		//sprintf(filePathtks, "Assets/modelData/backGround/%s.tks", objName);
		//m_modelRender->SetFilePathTks(static_cast<const char*>(filePathtks));

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

	MapChip::~MapChip() {
		DeleteGO(m_modelRender);
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