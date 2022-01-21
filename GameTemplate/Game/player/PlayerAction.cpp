#include "stdafx.h"
#include "PlayerAction.h"
#include "Player.h"
#include "../AttackCollision.h"

namespace nsMyGame {

	namespace nsPlayer {

		void CPlayerAction::Init(const CVector3& position, const CQuaternion& rotation, const CVector3& forward, Bone* swordBone) {

			//�L�����N�^�[�R���g���[���[���������B
			m_charaCon.Init(
				20.0f,			//���a�B
				100.0f,			//�����B
				position		//���W�B
			);

			m_swordBone = swordBone;

			//���̃{�[���̃��[���h�s����擾�B
			CMatrix swordBaseMatrix = m_swordBone->GetWorldMatrix();

			//�����蔻��̃C���X�^���X���������B
			m_attackCollision.Create(m_position, m_rotation);

			//�����蔻��̍��W�Ɖ�]���X�V�B
			m_attackCollision.UpdatePositionAndRotation(swordBaseMatrix);

			//�����蔻������Ȃ��悤�ɐݒ�B
			m_attackCollision.Deactivate();
		}

		void CPlayerAction::Move(CVector3& position, CVector3& forward, EnPlayerState& playerState) {

			//�ړ����x���������B
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
			m_rollingSpeed.x = 0.0f;
			m_rollingSpeed.z = 0.0f;

			//�J�����̑O�������ƉE�������擾�B
			CVector3 cameraForward = g_camera3D->GetForward();
			CVector3 cameraRight = g_camera3D->GetRight();

			//XZ���ʂł̑O�������A�E�����ɕϊ�����B
			cameraForward.y = 0.0f;
			cameraForward.Normalize();
			cameraRight.y = 0.0f;
			cameraRight.Normalize();

			//�N�[���^�C�����łȂ��A�K�[�h���A�K�[�h�������łȂ�������
			if (!IsCoolTime() && !IsGuard() && !IsGuardSccessCoolTime()) {
				//���̃t���[���̈ړ��ʂ����߂�B
				//���X�e�B�b�N�̓��͗ʂ��󂯎��B
				float lStick_x = g_pad[0]->GetLStickXF();
				float lStick_y = g_pad[0]->GetLStickYF();

				//XZ�����̈ړ����x���N���A�B
				m_moveSpeed += cameraForward * lStick_y * 200.0f;	//�������ւ̈ړ����x�����Z�B
				m_moveSpeed += cameraRight * lStick_x * 200.0f;		//�E�����ւ̈ړ����x�����Z�B

				//�ړ����Ă�����ړ��A�j���[�V�������Đ��B
				if (lStick_x != 0.0f || lStick_y != 0.0f) {

					//����B�{�^����������Ă�����
					if (g_pad[0]->IsPress(enButtonB)) {

						//�ړ����x��1.5�{��
						m_moveSpeed.x *= 1.5f;
						m_moveSpeed.z *= 1.5f;

						//�_�b�V����Ԃɂ���B
						playerState = enState_Run;
						m_isDash = true;
					}
					else {
						//������Ԃɂ���B
						playerState = enState_Walk;
						m_isDash = false;
					}
				}
				//�ړ����͂��Ă��Ȃ�
				else {
					//�ҋ@��Ԃɂ���B
					playerState = enState_Idle;
				}

			}

			//�ʏ�U�����Ȃ�
			if ((playerState == enState_Attack)) {
			
				float value = c_attackCoolTime - m_coolTime;
				if (c_attackCoolTime - m_coolTime > 0.1f && c_attackCoolTime - m_coolTime < 0.4f) {
					m_rollingSpeed = forward * 20.0f *(-4.0f * pow((value - 1.0f), 2.0f) + 8.0f);
				}
			}

			//�K�[�h�������̃m�b�N�o�b�N
			if (IsGuardSccessCoolTime()) {

				m_moveSpeed -= forward * 150.0f;
			}

			//�W�����v�����B
			if (g_pad[0]->IsTrigger(enButtonY) //A�{�^���������ꂽ�� 
				//&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
				) {
				//�W�����v����B
				m_moveSpeed.y = 400.0f;	//������ɑ��x��ݒ�B
			}

			//���[�����O���̈ړ������B
			if (playerState == enState_Rolling) {

				float value = c_rollingCoolTime - m_coolTime;

				//�w���֐��I�ɑ��x�����߂�B
				//���X�g��0.2�b�Ԃ����͒��n�̂��߁A�ړ����Ȃ��B
				if (c_rollingCoolTime - value > 0.8f) {
					m_rollingSpeed = forward * 400.0f;// *(-1.5f * pow((value - 1.0f), 2.0f) + 2.0f);
				}
				else if (c_rollingCoolTime - value > 0.2f) {
					m_rollingSpeed = forward * 100.0f;
				}

				//�_�b�V�����Ȃ�ړ������𑝂₷�B
				if (IsDash()) {
					m_rollingSpeed *= 1.5f;
				}
			}

			//�d�͂�������B
			m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();


			//���[�����O�̑��x�����Z�B
			m_moveSpeed += m_rollingSpeed;

			//�L�����R�����g�p���āA���W���X�V�B
			position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());


			//�n�ʂɂ��Ă��邩����B
			if (m_charaCon.IsOnGround()) {

				//�n�ʂɂ��Ă���Ȃ牺�����ɂ͗͂������Ȃ��B
				m_moveSpeed.y = 0.0f;
			}
		}

		void CPlayerAction::Rotate(CQuaternion& rotation) {

			//���͗ʂ𒲂ׂ�B
			float lStick_x = g_pad[0]->GetLStickXF();
			float lStick_y = g_pad[0]->GetLStickYF();

			//�ړ��{�^�������͂���Ă��Ȃ�������
			if (fabsf(lStick_x) < 0.001f
				&& fabsf(lStick_y) < 0.001f) {
				//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
				return;
			}

			//�J�����̑O�������ƉE�������擾�B
			CVector3 cameraForward = g_camera3D->GetForward();
			CVector3 cameraRight = g_camera3D->GetRight();

			//XZ���ʂł̑O�������A�E�����ɕϊ�����B
			cameraForward.y = 0.0f;
			cameraForward.Normalize();
			cameraRight.y = 0.0f;
			cameraRight.Normalize();

			//XZ�����̈ړ����x���N���A�B
			CVector3 rotSource = CVector3::Zero;
			rotSource += cameraForward * lStick_y;		//���������v�Z�B
			rotSource += cameraRight * lStick_x;		//�E�������v�Z�B

			//��]�p�x�����߂�B
			float angle = atan2(-rotSource.x, rotSource.z);

			//��]��ݒ�B
			rotation.SetRotationY(-angle);
		}

		void CPlayerAction::Action(EnPlayerState& playerState, const bool selectFlag) {

			//�N�[���^�C�����łȂ�
			if (!IsCoolTime()) {

				//R1�{�^���������ꂽ��
				if (g_pad[0]->IsTrigger(enButtonRB1)) {

					//��U����ԂɁB
					playerState = enState_Attack;

					//�N�[���^�C����ݒ�B
					m_coolTime = c_attackCoolTime;
				}

				//L1�{�^����������Ă�����
				if (g_pad[0]->IsPress(enButtonLB1) && !IsGuardSccessCoolTime()) {

					//�K�[�h��ԂɁB
					playerState = enState_Guard;
					m_isGuard = true;
				}
				else {

					//�K�[�h��Ԃ������B
					m_isGuard = false;
				}

				//�����I��ł��Ȃ���Ԃ�A�{�^���������ꂽ��
				if (g_pad[0]->IsTrigger(enButtonA) && !selectFlag) {

					//���[�����O��ԂɁB
					playerState = enState_Rolling;

					//�N�[���^�C����ݒ�B
					m_coolTime = c_rollingCoolTime;
				}
			}
		}

		void CPlayerAction::CreateAttackCollision() {

			auto player = FindGO<CPlayer>(c_classNamePlayer);
			
			//���̃{�[���̃��[���h�s����擾����B
			CMatrix swordBaseMatrix = player->GetModelRender()->GetSkeleton()->GetBone(66)->GetWorldMatrix();

			//�R���W�����I�u�W�F�N�g���쐬����B
			auto collisionObject = NewGO<CAttackCollision>(enPriority_Zeroth, c_classNamePlayerAttackCollision);

			//�L�����Ԃ�ݒ�B
			collisionObject->SetActiveTime(0.2f);

			//�{�b�N�X��̃R���W�������쐬����B
			collisionObject->CreateBox(player->GetPosition(), CQuaternion::Identity, c_attackTriggerBoxSize);

			//���̃{�[���̃��[���h�s����R���W�����ɓK�p������B
			collisionObject->SetWorldMatrix(swordBaseMatrix);
		}

		void CPlayerAction::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
		{
			//�L�[�̖��O���uattack�v�̎��B
			if (wcscmp(eventName, L"attack") == 0)
			{
				//�U�����ɂ���B
				m_attackCollision.Activate();
			}
			//�L�[�̖��O���uattack_end�v�̎��B
			else if (wcscmp(eventName, L"attackEnd") == 0)
			{
				//�U�����I���B
				m_attackCollision.Deactivate();
			}
			else if (wcscmp(eventName, L"startRolling") == 0)
			{
				//���[�����OSE���Đ��B
				CSoundManager::GetInstance()->Play(enSE_Rolling);
			}
			else if (wcscmp(eventName, L"walk") == 0
				|| wcscmp(eventName, L"run") == 0
			)
			{
				//���sSE���Đ��B
				CSoundManager::GetInstance()->Play(enSE_Walk);
			}
			else if (wcscmp(eventName, L"death_1") == 0)
			{
				//�|���SE���Đ��B
				CSoundManager::GetInstance()->Play(enSE_Death_1);
			}
			else if (wcscmp(eventName, L"death_2") == 0)
			{
				//�|���SE2���Đ��B
				CSoundManager::GetInstance()->Play(enSE_Death_2);
			}
		}

		void CPlayerAction::Update() {

			//���̃{�[���̃��[���h�s����擾�B
			CMatrix swordBaseMatrix = m_swordBone->GetWorldMatrix();

			//�����蔻��̍��W�Ɖ�]���X�V�B
			m_attackCollision.UpdatePositionAndRotation(swordBaseMatrix);

			//�����蔻����X�V�B
			m_attackCollision.Update();

			//�N�[���^�C�����Ȃ�
			if (IsCoolTime()) {

				//�N�[���^�C�����X�V�B
				m_coolTime -= g_gameTime->GetFrameDeltaTime();
			}

			//�K�[�h���̃N�[���^�C�����Ȃ�
			if (IsGuardSccessCoolTime()) {

				//�K�[�h���̃N�[���^�C�����X�V�B
				m_guardSccessCoolTime -= g_gameTime->GetFrameDeltaTime();
			}
		}
	}
}