#include "stdafx.h"
#include <random>
#include "BackGround.h"
#include "player/Player.h"
#include "item/Item.h"
#include "Door.h"
#include "enemy/firstWinEnemy/FirstWinEnemy.h"
#include "enemy/goteWinEnemy/GoteWinEnemy.h"
#include "enemy/boss/Boss.h"


namespace nsMyGame {

	nsLight::CDirectionLight* CBackGround::m_dirLight[2] = { nullptr };

	bool CBackGround::Start() {

		//�f�B���N�V�������C�g���쐬�B
		CreateDirLight();

		//�X�e�[�W�����[�h�B
		LoadStage();

		return true;
	}

	void CBackGround::OnDestroy() {

		//�|�C���g���C�g���폜�B
		for (int i = 0; i < m_pointLightNum; i++) {

			DeleteGO(m_pointLight[i]);
			m_pointLight[i] = nullptr;
		}
		m_pointLight.clear();

		//�h�A���폜�B
		for (int i = 0; i < m_doorNum; i++) {

			DeleteGO(m_door[i]);
			m_door[i] = nullptr;
		}
		m_door.clear();

		//���K���̓G���폜�B
		for (int i = 0; i < m_fEnemyNum; i++) {

			DeleteGO(m_fWEnemy[i]);
			m_fWEnemy[i] = nullptr;
		}
		m_fWEnemy.clear();

		//���K���̓G���폜�B
		for (int i = 0; i < m_gEnemyNum; i++) {

			DeleteGO(m_gWEnemy[i]);
			m_gWEnemy[i] = nullptr;
		}
		m_gWEnemy.clear();

		//�A�C�e�����폜�B
		QueryGOs<nsItem::CItem>(c_classNameAppearSprite, [&](nsItem::CItem* go) {
			DeleteGO(go);
			return true;
		});
		m_item.clear();

		//�f�B���N�V�������C�g���폜�B
		RemoveDirLight();

		//�{�X���폜�B
		DeleteGO(m_boss);
		m_boss = nullptr;

		//����SE���~�B
		CSoundManager::GetInstance()->Release(enSE_Torch);
	}

	void CBackGround::Update() {

		//�v���C���[�̑I����Ԃ��X�V�B
		UpdatePlayerSelect();

		//�{�X���o�ꂷ�邽�߂̃g���K�[�{�b�N�X���X�V�B
		UpdateBossNoticeTriggerBox();

		//�v���C���[�Ɋւ��郉�C�g���X�V�B
		UpdatePlayerLight();

		//�����̉��G�t�F�N�g���X�V�B
		UpdateFireEffect();
	}

	void CBackGround::UpdatePlayerSelect() {

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

		//	//�v���C���[�̍��W���擾�B
		CVector3 playerPos = player->GetPosition();

		//�K��l���100.0f�傫�����������l�Ƃ���B
		float vecToPlayerLength = c_distanceForOpenDoor + 100.0f;

		//���X�g�Ɋ܂܂��I�u�W�F�N�g���Q�ƁB
		for (const auto& obj : m_door) {

			//�N���X�̖��O�𒲂ׂ�B
			const std::type_info& typeInfo = typeid(*obj);

			//�h�A��������
			if (typeInfo == typeid(CDoor)) {

				//�h�A�N���X�ɃL���X�g�B
				auto doorObj = dynamic_cast<CDoor*>(obj);

				//�v���C���[�ɐL�т�x�N�g�����v�Z�B
				CVector3 vecToPlayer = playerPos - doorObj->GetPosition();

				//�v���C���[�Ƃ̍ŒZ�������X�V�B
				if (vecToPlayer.Length() < vecToPlayerLength) {

					vecToPlayerLength = vecToPlayer.Length();

					//�ŒZ�������X�V�����h�A�ƃv���C���[�̋��������ȉ����A���̃h�A���J���Ă��Ȃ��Ȃ�
					if (vecToPlayerLength <= c_distanceForOpenDoor && !doorObj->IsOpened()) {

						//�v���C���[��I����Ԃɂ���B
						player->SetSelectFlag(true);
						break;
					}
				}
			}
		}
	}
	
	void CBackGround::UpdatePlayerLight() {

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

		//�v���C���[���S�̃|�C���g���C�g�̍��W���X�V�B
		CVector3 playerLightPosition = player->GetPosition();
		playerLightPosition.y += c_playerPointLightAddParam;
		m_pointLight[0]->SetPosition(playerLightPosition);

		//�J�����̑O�����Ɍ����ĕ������f�B���N�V�������C�g�̌������X�V�B
		m_dirLight[1]->SetLigDirection(g_camera3D->GetForward());
	}

	void CBackGround::UpdateBossNoticeTriggerBox() {

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

		if (!m_createBoss) {
			//���̂Ƃ̓����蔻��𒲂ׂ�B
			CPhysicsWorld::GetInstance()->ContactTest(player->GetCharacterController(), [&](const btCollisionObject& contactObject) {

				//�g���K�[�{�b�N�X�ƐڐG�����B
				if (m_noticePlayerTriggerBox.IsSelf(contactObject)) {

					//�{�X���o��������B
					m_boss = NewGO<nsEnemy::CBoss>(enPriority_Zeroth, c_classNameBoss);
					m_boss->SetPosition(m_bossPosition);
					m_boss->SetRotation(m_bossRotation);

					m_createBoss = true;
				}
			});
		}
	}

	void CBackGround::UpdateFireEffect() {

		//�^�C�}�[���X�V�B
		m_fireTime += GameTime().GameTimeFunc().GetFrameDeltaTime();

		//�^�C�}�[���K�莞�Ԃ𒴂�����
		if (m_fireTime >= c_fireEffectLoopTime) {

			//���G�t�F�N�g���Đ����B
			for (const auto& fireEffect : m_fireEffect) {

				fireEffect->Play();
			}
			//�^�C�}�[�����Z�b�g�B
			m_fireTime = 0.0f;
		}
	}

	void CBackGround::LoadStage() {

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

		//�v���C���[�𒆐S�Ƃ���|�C���g���C�g���쐬�B
		m_pointLight.push_back(NewGO<nsLight::CPointLight>(enPriority_Zeroth));
		m_pointLight[m_pointLightNum]->SetPosition(player->GetPosition());
		m_pointLight[m_pointLightNum]->SetColor({ CVector4::White.x,CVector4::White.y,CVector4::White.z });
		m_pointLight[m_pointLightNum]->SetRange(c_playerPointLightRange);
		m_pointLight[m_pointLightNum]->SetAffectPowParam(c_playerPointLightAffectPowParam);
		m_pointLightNum++;

		//����SE���Đ��B
		CSoundManager::GetInstance()->Play(enSE_Torch);

		//�X�e�[�W�����[�h�B
		m_level.Init("Assets/level/stage_1.tkl", [&](LevelObjectData& objData) {

			if (objData.EqualObjectName("door")) {

				m_door.push_back(NewGO<CDoor>(enPriority_Zeroth));
				m_door[m_doorNum]->SetPosition(objData.position);
				m_door[m_doorNum]->SetRotation(objData.rotation);
				m_door[m_doorNum]->SetScale(objData.scale);

				//m_door[m_doorNum]->AddEventListener([&] {
				//
				//	m_door[m_doorNum] = nullptr;
				//});

				m_doorNum++;

				return true;
			}

			if (objData.EqualObjectName("door_Lock")) {

				m_door.push_back(NewGO<CDoor>(enPriority_Zeroth));
				m_door[m_doorNum]->SetPosition(objData.position);
				m_door[m_doorNum]->SetRotation(objData.rotation);
				m_door[m_doorNum]->SetScale(objData.scale);

				//����������B
				m_door[m_doorNum]->Lock();

				//m_door[m_doorNum]->AddEventListener([&] {
				//
				//	m_door[m_doorNum] = nullptr;
				//});

				m_doorNum++;
				return true;
			}

			if (objData.EqualObjectName("doorObj")) {

				m_door.push_back(NewGO<CDoor>(enPriority_Zeroth));
				m_door[m_doorNum]->SetPosition(objData.position);
				m_door[m_doorNum]->SetRotation(objData.rotation);
				m_door[m_doorNum]->SetScale(objData.scale);
				m_door[m_doorNum]->SetObj(true);
				m_doorNum++;
				return true;
			}

			if (objData.EqualObjectName("FEnemy")) {

				m_fWEnemy.push_back(NewGO<nsEnemy::CFirstWinEnemy>(enPriority_Zeroth, c_classNameEnemy));
				m_fWEnemy[m_fEnemyNum]->SetPosition(objData.position);
				m_fWEnemy[m_fEnemyNum]->SetRotation(objData.rotation);
				m_fEnemyNum++;
				return true;
			}

			if (objData.EqualObjectName("GEnemy")) {

				//���K���̓G�͍��͍폜���B
				//m_gWEnemy.push_back(NewGO<nsEnemy::CGoteWinEnemy>(enPriority_Zeroth, c_classNameEnemy));
				//m_gWEnemy[gEnemyNum]->SetPosition(objData.position);
				//m_gWEnemy[gEnemyNum]->SetRotation(objData.rotation);
				//gEnemyNum++;
				return true;
			}

			if (objData.EqualObjectName("Boss")) {

				m_bossPosition = objData.position;
				m_bossRotation = objData.rotation;

				//�{�X���o�ꂷ�邽�߂̃g���K�[�{�b�N�X��ݒ�B
				m_noticePlayerTriggerBox.CreateBox(objData.position, CQuaternion::Identity, c_noticePlayerTriggerBoxSize);

				return true;
			}

			if (objData.EqualObjectName("key")) {

				m_item.push_back(NewGO<nsItem::CItem>(enPriority_Zeroth, c_classNameItem));
				m_item[m_itemNum]->SetPosition(objData.position);

				m_itemNum++;

				return true;
			}

			if (objData.EqualObjectName("torch")) {

				//�R����G�t�F�N�g�̍��W�Ɖ�]�𒲐��B
				CVector3 effectPos = objData.position;
				effectPos += c_addFireEffectPosition;
				CQuaternion effectRot = objData.rotation;
				effectRot.AddRotationY(CMath::DegToRad(90.0f));
				effectPos = effectPos - objData.position;
				effectRot.Apply(effectPos);
				effectPos = objData.position + effectPos;

				//�G�t�F�N�g���������B
				m_fireEffect.push_back(NewGO<Effect>(enPriority_Zeroth));
				m_fireEffect[m_fireEffectNum]->Init(c_filePathFireEffect);
				m_fireEffect[m_fireEffectNum]->SetScale(c_fireEffectScale);
				m_fireEffect[m_fireEffectNum]->SetPosition(effectPos);
				m_fireEffect[m_fireEffectNum]->SetRotation(effectRot);

				//���G�t�F�N�g�ɑΉ�����|�C���g���C�g���쐬�B
				m_pointLight.push_back(NewGO<nsLight::CPointLight>(enPriority_Zeroth));
				m_pointLight[m_pointLightNum]->SetPosition(effectPos);
				m_pointLight[m_pointLightNum]->SetColor(c_firePointLightColor);
				m_pointLight[m_pointLightNum]->SetRange(c_firePointLightRange);
				m_pointLight[m_pointLightNum]->SetAffectPowParam(c_firePointLightAffectParam);
				m_pointLightNum++;

				//�Đ��B
				m_fireEffect[m_fireEffectNum]->Play();
				m_fireEffectNum++;
			}
			if (objData.EqualObjectName("torchBowl")) {

				//�R����G�t�F�N�g�̍��W�Ɖ�]�𒲐��B
				CVector3 effectPos = objData.position;
				effectPos.y += 145.0f;

				//�G�t�F�N�g���������B
				m_fireEffect.push_back(NewGO<Effect>(enPriority_Zeroth));
				m_fireEffect[m_fireEffectNum]->Init(c_filePathFireEffect);
				m_fireEffect[m_fireEffectNum]->SetScale(c_fireEffectScale);
				m_fireEffect[m_fireEffectNum]->SetPosition(effectPos);

				//���G�t�F�N�g�ɑΉ�����|�C���g���C�g���쐬�B
				m_pointLight.push_back(NewGO<nsLight::CPointLight>(enPriority_Zeroth));
				m_pointLight[m_pointLightNum]->SetPosition(effectPos);
				m_pointLight[m_pointLightNum]->SetColor(c_firePointLightColor);
				m_pointLight[m_pointLightNum]->SetRange(c_firePointLightRange);
				m_pointLight[m_pointLightNum]->SetAffectPowParam(c_firePointLightAffectParam);
				m_pointLightNum++;

				//�Đ��B
				m_fireEffect[m_fireEffectNum]->Play();
				m_fireEffectNum++;
			}
			return false;
			});
	}
}