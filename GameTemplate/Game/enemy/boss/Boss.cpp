#include "stdafx.h"
#include "Boss.h"
#include "../../AttackCollision.h"
#include "../../BackGround.h"
#include "../../MainCamera.h"

namespace nsMyGame {

	namespace nsEnemy {

		extern CEnemy* g_pCurrentEnemy;

		bool CBoss::StartSub() {

			//IGameObject�ɒǉ��B
			m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);

			//tkm�t�@�C����tks�t�@�C����ݒ�B
			m_modelRender->SetFilePathTkm(c_filePathTkmBoss);
			m_modelRender->SetFilePathTks(c_filePathTksBoss);

			//���W��ݒ�B
			m_modelRender->SetPosition(m_position);

			//��]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//�A�j���[�V�����N���b�v���������B
			InitAnimationClip();

			//�A�j���[�V�������������B
			m_modelRender->InitAnimation(m_animationClip, enAnim_Num);

			//�e�𗎂Ƃ��B
			m_modelRender->SetShadowCasterFlag(true);

			//�e���󂯂�B
			m_modelRender->SetShadowReceiverFlag(true);

			//�X�e�[�^�X���������B
			InitStatus();

			//�������B
			m_modelRender->Init();

			//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
			m_modelRender->AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {

				OnAnimationEvent(clipName, eventName);
			});

			//�L�����N�^�[�R���g���[���[���������B
			m_charaCon.Init(
				100.0f,			//���a�B
				100.0f,			//�����B
				m_position		//���W�B
			);

			//���Ɏ��t����ꂽ�{�[���̔ԍ���ǂݍ��ށB
			auto swordBoneNum = m_modelRender->GetSkeleton()->FindBoneID(L"RightHand");

			//���̃{�[�����擾�B
			m_swordBone = m_modelRender->GetSkeleton()->GetBone(swordBoneNum);

			//���̃{�[���̃��[���h�s����擾�B
			CMatrix swordBaseMatrix = m_swordBone->GetWorldMatrix();

			//�����蔻��̃C���X�^���X���������B
			m_triggerBox.Create(m_position, m_rotation);

			//�����蔻��̍��W�Ɖ�]���X�V�B
			m_triggerBox.UpdatePositionAndRotation(swordBaseMatrix);

			//�����蔻������Ȃ��悤�ɐݒ�B
			m_triggerBox.DeactivateAttack();
			m_triggerBox.DeactivateRangeAttack();

			//�v���C���[�ɋC�Â����߂̃g���K�[�{�b�N�X��ݒ�B
			m_noticePlayerTriggerBox.CreateBox(m_position, CQuaternion::Identity, { 1500.0f,1000.0f,1500.0f });

			//�o�ꎞ�̃N�[���^�C����2.0�b�B
			m_coolTime = 2.0f;

			//�Q�[�����y���{�X��BGM�ɕύX�B
			CSoundManager::GetInstance()->Release(enBGM_GameMain);
			CSoundManager::GetInstance()->Play(enBGM_Boss);

			return true;
		}

		void CBoss::UpdateSub() {

			// ���ݍX�V���������s���̃G�l�~�[�̃A�h���X����
			g_pCurrentEnemy = this;

			FindPlayer();

			//���̃{�[���̃��[���h�s����擾�B
			CMatrix swordBaseMatrix = m_swordBone->GetWorldMatrix();

			//�����蔻��̃��[���h�s����X�V�B
			m_triggerBox.UpdatePositionAndRotation(swordBaseMatrix);

			//�X�e�[�g�ɉ����ēǂݍ���Python�X�N���v�g��ς���B
			switch (m_state) {
			case enState_Idle:
				ImportModule("BossIdle");
				break;
			case enState_Walk:
				ImportModule("BossMove");
				break;
			case enState_JumpAttack:
				ImportModule("BossJumpAttack");
				break;
			case enState_SwipingAttack:
				ImportModule("BossSwipingAttack");
				break;
			case enState_Damage:
				ImportModule("EnemyDamage");
				break;
			case enState_Death:
				ImportModule("BossDeath");
				break;
			case enState_Scream:
				ImportModule("BossScream");
				break;
			case enState_Start:
				ImportModule("BossStart");
				break;
			}

			//Python�X�N���v�g��Update()�֐����Ăяo���B
			auto updateFunc = m_enemyPyModule.attr("Update");
			updateFunc();
		}

		void CBoss::InitStatus() {

			m_status.hp = c_bossMaxHP;
			m_status.attack = 10;
		}

		void CBoss::InitAnimationClip() {

			//�A�j���[�V�����N���b�v��ݒ�B
			m_animationClip[enAnim_Walk].Load("Assets/animData/Boss/walk.tka");
			m_animationClip[enAnim_Walk].SetLoopFlag(true);
			m_animationClip[enAnim_Idle].Load("Assets/animData/Boss/idle.tka");
			m_animationClip[enAnim_Idle].SetLoopFlag(true);
			m_animationClip[enAnim_JumpAttack].Load("Assets/animData/Boss/attack.tka");
			m_animationClip[enAnim_JumpAttack].SetLoopFlag(false);
			m_animationClip[enAnim_SwipingAttack].Load("Assets/animData/Boss/swiping.tka");
			m_animationClip[enAnim_SwipingAttack].SetLoopFlag(false);
			m_animationClip[enAnim_Damage].Load("Assets/animData/damage.tka");
			m_animationClip[enAnim_Damage].SetLoopFlag(false);
			m_animationClip[enAnim_Death].Load("Assets/animData/Boss/death.tka");
			m_animationClip[enAnim_Death].SetLoopFlag(false);
			m_animationClip[enAnim_Scream].Load("Assets/animData/Boss/scream.tka");
			m_animationClip[enAnim_Scream].SetLoopFlag(false);
			m_animationClip[enAnim_Start].Load("Assets/animData/Boss/startAnim_1.tka");
			m_animationClip[enAnim_Start].SetLoopFlag(false);
		}

		void CBoss::AnimationUpdate() {

			//�e�X�e�[�g�ɑΉ������A�j���[�V�������Đ�����B
			switch (m_state) {
			case enState_Idle:
				m_modelRender->PlayAnimation(enAnim_Idle, 0.4f);
				break;
			case enState_Walk:
				m_modelRender->PlayAnimation(enAnim_Walk, 0.4f);
				break;
			case enState_JumpAttack:
				m_modelRender->PlayAnimation(enAnim_JumpAttack, 0.4f);
				break;
			case enState_SwipingAttack:
				m_modelRender->PlayAnimation(enAnim_SwipingAttack, 0.4f);
				break;
			case enState_Damage:
				m_modelRender->PlayAnimation(enAnim_Damage, 0.4f);
				break;
			case enState_Death:
				m_modelRender->PlayAnimation(enAnim_Death, 0.4f);
				break;
			case enState_Scream:
				m_modelRender->PlayAnimation(enAnim_Scream, 0.4f);
				break;
			case enState_Start:
				m_modelRender->PlayAnimation(enAnim_Start, 0.4f);
				break;
			}
		}

		void CBoss::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
		{
			//�L�[�̖��O���uattack�v�̎��B
			if (wcscmp(eventName, L"startAttack") == 0)
			{
				//�U�����ɂ���B
				m_triggerBox.ActivateAttack();
			}
			//�L�[�̖��O���uattack_end�v�̎��B
			else if (wcscmp(eventName, L"endAttack") == 0)
			{
				//�U�����I���B
				m_triggerBox.DeactivateAttack();
			}
			//�L�[�̖��O���uattack�v�̎��B
			else if (wcscmp(eventName, L"startRangeAttack") == 0)
			{
				//�U�����ɂ���B
				m_triggerBox.ActivateRangeAttack();

				auto mainCamera = FindGO<CMainCamera>(c_classNameMainCamera);

				//�J������h���Ԃɂ���B
				mainCamera->ShakeCamera();
			}
			//�L�[�̖��O���uattack_end�v�̎��B
			else if (wcscmp(eventName, L"endRangeAttack") == 0)
			{
				//�U�����I���B
				m_triggerBox.DeactivateRangeAttack();
			}
			else if (wcscmp(eventName, L"ready") == 0)
			{
				//�W�����v�U���̏����B
				//�v���C���[�ɐL�т�x�N�g�������߂�B
				m_vecToPlayer = m_player->GetPosition() - m_position;
			}
			else if (wcscmp(eventName, L"startJump") == 0) {

				//�ړ��ł���B
				m_canMove = true;
			}
			else if (wcscmp(eventName, L"endJump") == 0) {

				//�ړ��ł��Ȃ��B
				m_canMove = false;

				//�Ռ�SE���Đ��B
				CSoundManager::GetInstance()->Play(enSE_Impact);
			}
			else if (wcscmp(eventName, L"impact") == 0) {

				//�Ռ�SE���Đ��B
				CSoundManager::GetInstance()->Play(enSE_Impact);
			}
			else if (wcscmp(eventName, L"endShakeCamera") == 0) {

				auto mainCamera = FindGO<CMainCamera>(c_classNameMainCamera);
				
				//�J������ʏ��Ԃɂ���B
				mainCamera->SetNormalCamera();
			}
			else if (wcscmp(eventName, L"scream") == 0) {

				//���KSE���Đ��B
				CSoundManager::GetInstance()->Play(enSE_Scream);
			}
			else if (wcscmp(eventName, L"walk") == 0) {

				//�{�X����SE���Đ��B
				CSoundManager::GetInstance()->Play(enSE_Footsteps);
			}
			else if (wcscmp(eventName, L"scratch") == 0) {

				//�����~��SE���Đ��B
				CSoundManager::GetInstance()->Play(enSE_Scratch);
			}
		}

		void CBoss::CreateAttackCollision() {

			//���̃{�[���̃��[���h�s����擾�B
			CMatrix swordBaseMatrix = m_swordBone->GetWorldMatrix();

			//�R���W�����I�u�W�F�N�g���쐬�B
			auto collisionObject = NewGO<CAttackCollision>(enPriority_Zeroth, c_classnameEnemyAttackCollision);

			//�L�����Ԃ�ݒ�B
			collisionObject->SetActiveTime(c_attackCollisionActiveTime);

			//�{�b�N�X��̃R���W�������쐬�B
			collisionObject->CreateBox(m_position, CQuaternion::Identity, c_bossAttackTriggerBoxSize);

			//���̃{�[���̃��[���h�s����R���W�����ɓK�p�B
			collisionObject->SetWorldMatrix(swordBaseMatrix);
		}

		void CBoss::Move() {

			switch (m_state) {

			case enState_JumpAttack:
				//�W�����v�U�����̈ړ������B
				JumpAttackMove();
				break;
			default:
				//�ʏ�̈ړ������B
				MoveCommon();
				break;
			}
		}

		void CBoss::MoveCommon() {

			//x������z�����̈ړ����x���������B
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;

			//�v���C���[�̍��W���擾����B
			CVector3 toPlayerVec = m_player->GetPosition() - m_position;
			toPlayerVec.y = 0.0f;

			//���K���B
			toPlayerVec.Normalize();

			//������ԂȂ�v���C���[�Ɉ�葬�x�ŋ߂Â��B
			if (m_state == enState_Walk) {

				m_moveSpeed += toPlayerVec * 200.0f;
			}

			//�d�͂�������B
			m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();

			//���W��ݒ�B
			m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			//�n�ʂɂ��Ă��邩����B
			if (m_charaCon.IsOnGround()) {

				//�n�ʂɂ��Ă���Ȃ牺�����ɂ͗͂������Ȃ��B
				m_moveSpeed.y = 0.0f;
			}
		}

		void CBoss::JumpAttackMove() {

			//�W�����v������Ȃ��Ȃ�I���B
			if (!m_canMove) { return; }

			//x������z�����̈ړ����x���������B
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;

			//���߂�ꂽ�x�N�g���Ɍ������Ĉړ�����B
			m_moveSpeed += m_vecToPlayer;

			//�d�͂�������B
			m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();

			//���W��ݒ�B
			m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			//�n�ʂɂ��Ă��邩����B
			if (m_charaCon.IsOnGround()) {

				//�n�ʂɂ��Ă���Ȃ牺�����ɂ͗͂������Ȃ��B
				m_moveSpeed.y = 0.0f;
			}
		}

		void CBoss::UpdateTriggerBox() {

			//�g���K�[�{�b�N�X���X�V�B
			m_triggerBox.Update(m_position);
		}

		void CBoss::FindPlayer() {
 
			auto backGround = FindGO<CBackGround>(c_classNameBackGround);

			//�{�X���o�ꂵ�Ă���Ȃ�
			if (backGround->CreatedBoss()) {

				//�v���C���[�ɋC�Â����B
				m_noticePlayer = true;
			}
		}
	}
}