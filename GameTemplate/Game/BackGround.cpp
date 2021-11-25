#include "stdafx.h"
#include <random>
#include "BackGround.h"
#include "player/Player.h"


namespace nsMyGame {

	nsLight::CDirectionLight* CBackGround::m_dirLight[2] = { nullptr };

	bool CBackGround::Start() {

		static int doorNum = 0;
		static int fEnemyNum = 0;
		static int gEnemyNum = 0;
		static int pointLightNum = 0;
		static int fireEffectNum = 0;
		CreateDirLight();

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);
		
		//�v���C���[�𒆐S�Ƃ���|�C���g���C�g���쐬�B
		m_pointLight.push_back(NewGO<nsLight::CPointLight>(enPriority_Zeroth));
		m_pointLight[pointLightNum]->SetPosition(player->GetPosition());
		m_pointLight[pointLightNum]->SetColor({ 1.0f,1.0f,1.0f });
		m_pointLight[pointLightNum]->SetRange(300.0f);
		m_pointLight[pointLightNum]->SetAffectPowParam(2.5f);
		pointLightNum++;

		

		//�X�e�[�W�����[�h�B
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

				m_fWEnemy.push_back(NewGO<nsEnemy::CFirstWinEnemy>(enPriority_Zeroth, c_classNameEnemy));
				m_fWEnemy[fEnemyNum]->SetPosition(objData.position);
				m_fWEnemy[fEnemyNum]->SetRotation(objData.rotation);
				fEnemyNum++;
				return true;
			}

			if (objData.EqualObjectName("GEnemy")) {

				m_gWEnemy.push_back(NewGO<nsEnemy::CGoteWinEnemy>(enPriority_Zeroth, c_classNameEnemy));
				m_gWEnemy[gEnemyNum]->SetPosition(objData.position);
				m_gWEnemy[gEnemyNum]->SetRotation(objData.rotation);
				gEnemyNum++;
				return true;
			}

			if (objData.EqualObjectName("pointLight")) {

				//m_pointLight.push_back(NewGO<nsLight::CPointLight>(enPriority_Zeroth));
				//m_pointLight[pointLightNum]->SetPosition(objData.position);
				//m_pointLight[pointLightNum]->SetColor({ 5.0f,0.0f,0.0f });
				//m_pointLight[pointLightNum]->SetRange(300.0f);
				//m_pointLight[pointLightNum]->SetAffectPowParam(2.0f);
				//pointLightNum++;
				return true;
			}

			if (objData.EqualObjectName("torch")) {

				//�R����G�t�F�N�g�̍��W�Ɖ�]�𒲐��B
				CVector3 effectPos = objData.position;
				effectPos.z += 35.0f;
				effectPos.y += 5.0f;
				CQuaternion effectRot = objData.rotation;
				effectRot.AddRotationY(CMath::DegToRad(90.0f));
				effectPos = effectPos - objData.position;
				effectRot.Apply(effectPos);
				effectPos = objData.position + effectPos;

				//�G�t�F�N�g���������B
				m_fireEffect.push_back(NewGO<Effect>(enPriority_Zeroth));
				m_fireEffect[fireEffectNum]->Init(u"Assets/effect/fire.efk");
				m_fireEffect[fireEffectNum]->SetScale({ 10.0f,10.0f,10.0f });
				m_fireEffect[fireEffectNum]->SetPosition(effectPos);
				m_fireEffect[fireEffectNum]->SetRotation(effectRot);

				//���G�t�F�N�g�ɑΉ�����|�C���g���C�g���쐬�B
				m_pointLight.push_back(NewGO<nsLight::CPointLight>(enPriority_Zeroth));
				m_pointLight[pointLightNum]->SetPosition(effectPos);
				m_pointLight[pointLightNum]->SetColor({ 10.0f,5.0f,5.0f });
				m_pointLight[pointLightNum]->SetRange(600.0f);
				m_pointLight[pointLightNum]->SetAffectPowParam(5.5f);
				pointLightNum++;

				//�Đ��B
				m_fireEffect[fireEffectNum]->Play();
				fireEffectNum++;
			}
			if (objData.EqualObjectName("torchBowl")) {

				//�R����G�t�F�N�g�̍��W�Ɖ�]�𒲐��B
				CVector3 effectPos = objData.position;
				effectPos.y += 145.0f;

				//�G�t�F�N�g���������B
				m_fireEffect.push_back(NewGO<Effect>(enPriority_Zeroth));
				m_fireEffect[fireEffectNum]->Init(u"Assets/effect/fire.efk");
				m_fireEffect[fireEffectNum]->SetScale({ 10.0f,10.0f,10.0f });
				m_fireEffect[fireEffectNum]->SetPosition(effectPos);

				//���G�t�F�N�g�ɑΉ�����|�C���g���C�g���쐬�B
				m_pointLight.push_back(NewGO<nsLight::CPointLight>(enPriority_Zeroth));
				m_pointLight[pointLightNum]->SetPosition(effectPos);
				m_pointLight[pointLightNum]->SetColor({ 2.0f,1.0f,1.0f });
				m_pointLight[pointLightNum]->SetRange(300.0f);
				m_pointLight[pointLightNum]->SetAffectPowParam(1.5f);
				pointLightNum++;

				//�Đ��B
				m_fireEffect[fireEffectNum]->Play();
				fireEffectNum++;
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

				//�ŒZ�������X�V�����h�A�ƃv���C���[�̋��������ȉ����A���̃h�A���J���Ă��Ȃ��Ȃ�
				if (vecToPlayerLength <= c_distanceForOpenDoor && !door->IsOpened()) {

					//�v���C���[��I����Ԃɂ���B
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

		//�v���C���[���S�̃|�C���g���C�g�̍��W���X�V�B
		CVector3 playerLightPosition = player->GetPosition();
		playerLightPosition.y += 130.0f;
		m_pointLight[0]->SetPosition(playerLightPosition);

		//�J�����̑O�����Ɍ����ĕ������f�B���N�V�������C�g�̌������X�V�B
		m_dirLight[1]->SetLigDirection(g_camera3D->GetForward());

		m_fireTime += GameTime().GameTimeFunc().GetFrameDeltaTime();

		//1.0�b���ƂɃG�t�F�N�g���Đ��B
		if (m_fireTime >= 1.0f) {

			for (const auto& fireEffect : m_fireEffect) {

				fireEffect->Play();
			}
			m_fireTime = 0.0f;
		}
	}
}