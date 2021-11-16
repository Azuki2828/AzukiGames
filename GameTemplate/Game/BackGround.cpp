#include "stdafx.h"
#include "BackGround.h"
#include "player/Player.h"


namespace nsMyGame {

	bool CBackGround::Start() {

		static int doorNum = 0;
		static int fEnemyNum = 0;
		static int gEnemyNum = 0;
		/*m_modelRender = NewGO<CModelRender>(0);
		m_modelRender->SetFilePathTkm("Assets/modelData/bg/bg.tkm");
		m_modelRender->SetPosition(m_pos);
		m_modelRender->SetRotation(m_rot);
		m_modelRender->SetScale(m_sca);
		m_modelRender->SetShadowReceiverFlag(true);
		m_modelRender->Init();
		m_modelRender->Update();*/

		/*m_wall = NewGO<CModelRender>(0);
		m_wall->SetFilePathTkm("Assets/modelData/BackGround/testStage.tkm");
		m_wall->SetPosition(m_pos);
		m_wall->SetRotation(m_rot);
		m_wall->SetScale(m_sca);
		m_wall->SetShadowReceiverFlag(true);
		m_wall->Init();
		m_physicsStaticObject.CreateFromModel(
			*m_wall->GetModel(),
			m_wall->GetModel()->GetWorldMatrix()
		);
		m_physicsStaticObject.SetFriction(10.0f);
		m_wall->Update();*/

		m_level.Init("Assets/level/stage_1.tkl", [&](LevelObjectData& objData) {

			if (objData.EqualObjectName("door")) {
				
				m_door.push_back(NewGO<CDoor>(enPriority_Zeroth));
				m_door[doorNum]->SetPosition(objData.position);
				m_door[doorNum]->SetRotation(objData.rotation);
				m_door[doorNum]->SetScale(objData.scale);
				doorNum++;
				return true;
			}

			if (objData.EqualObjectName("doorObj")) {

				m_door.push_back(NewGO<CDoor>(enPriority_Zeroth));
				m_door[doorNum]->SetPosition(objData.position);
				m_door[doorNum]->SetRotation(objData.rotation);
				m_door[doorNum]->SetScale(objData.scale);
				m_door[doorNum]->SetObj(true);
				doorNum++;
				return true;
			}

			if (objData.EqualObjectName("FEnemy")) {

				m_fWEnemy.push_back(NewGO<nsEnemy::CFirstWinEnemy>(enPriority_Zeroth, "Enemy"));
				m_fWEnemy[fEnemyNum]->SetPosition(objData.position);
				m_fWEnemy[fEnemyNum]->SetRotation(objData.rotation);
				fEnemyNum++;
				return true;
			}

			if (objData.EqualObjectName("GEnemy")) {

				m_gWEnemy.push_back(NewGO<nsEnemy::CGoteWinEnemy>(enPriority_Zeroth, "Enemy"));
				m_gWEnemy[gEnemyNum]->SetPosition(objData.position);
				m_gWEnemy[gEnemyNum]->SetRotation(objData.rotation);
				gEnemyNum++;
				return true;
			}
			return false;
		});
		return true;
	}

	void CBackGround::Update() {

		/*----------�v���C���[�̑I����Ԃ��X�V���邽�߂̏���----------*/

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

		//�v���C���[�̍��W���擾�B
		CVector3 playerPos = player->GetPosition();
		
		//�K��l���100.0f�傫�����������l�Ƃ���B
		float vecToPlayerLength = c_distanceForOpenDoor + 100.0f;

		//�X�e�[�W��̃h�A���Q�ƁB
		for (const auto& door : m_door) {

			//�v���C���[�ɐL�т�x�N�g�����v�Z�B
			CVector3 vecToPlayer = playerPos - door->GetPosition();

			//�v���C���[�Ƃ̍ŒZ�������X�V�B
			if (vecToPlayer.Length() < vecToPlayerLength) {

				vecToPlayerLength = vecToPlayer.Length();

				//�ŒZ�������X�V�����h�A�ƃv���C���[�̋��������ȉ����A���̃h�A���J���Ă��Ȃ��Ȃ�v���C���[��I����Ԃɂ���B
				if (vecToPlayerLength <= c_distanceForOpenDoor && !door->IsOpened()) {

					player->SetSelectFlag(true);
					break;
				}
			}
			//����ȊO�́A�v���C���[�͉����I�����Ă��Ȃ���ԁB
			else {

				player->SetSelectFlag(false);
			}
		}

		/*------------------------------------------------------------*/
	}
}