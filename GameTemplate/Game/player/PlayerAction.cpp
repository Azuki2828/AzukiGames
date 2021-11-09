#include "stdafx.h"
#include "PlayerAction.h"

namespace nsMyGame {

	namespace nsPlayer {

		void CPlayerAction::Init(const CVector3& position, const CQuaternion& rotation, const CVector3& forward) {

			//�L�����N�^�[�R���g���[���[���������B
			m_charaCon.Init(
				20.0f,			//���a�B
				100.0f,			//�����B
				position		//���W�B
			);
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

			//�N�[���^�C�����łȂ��A�K�[�h���łȂ�������
			if (!IsCoolTime() && !IsGuard()) {
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

			if ((playerState == enState_ThreeCombo)) {

				if (c_threeComboCoolTime - m_coolTime < 2.4f) {
					m_moveSpeed += forward * 50.0f;
				}
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
				if (c_rollingCoolTime - value > 0.2f) {
					m_rollingSpeed = forward * 150.0f * (-1.5f * pow((value - 1.0f), 2.0f) + 2.0f);
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

			//�ړ��{�^�������͂���Ă��Ȃ�������
			if (fabsf(m_moveSpeed.x) < 0.001f
				&& fabsf(m_moveSpeed.z) < 0.001f) {
				//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
				return;
			}
			//��]�p�x�����߂�B
			float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);

			//��]��ݒ�B
			rotation.SetRotationY(-angle);
		}

		void CPlayerAction::Action(EnPlayerState& playerState) {

			//�N�[���^�C�����łȂ�
			if (!IsCoolTime()) {

				//R1�{�^���������ꂽ��
				if (g_pad[0]->IsTrigger(enButtonRB1)) {

					//��U����ԂɁB
					playerState = enState_Attack;

					//�N�[���^�C����ݒ�B
					m_coolTime = 1.2f;
				}

				//L1�{�^����������Ă�����
				if (g_pad[0]->IsPress(enButtonLB1)) {

					//�K�[�h��ԂɁB
					playerState = enState_Guard;
					m_isGuard = true;
				}
				else {

					//�K�[�h��Ԃ������B
					m_isGuard = false;
				}

				//A�{�^���������ꂽ��
				if (g_pad[0]->IsTrigger(enButtonA)) {

					//���[�����O��ԂɁB
					playerState = enState_Rolling;

					//�N�[���^�C����ݒ�B
					m_coolTime = c_rollingCoolTime;
				}

				//X�{�^���������ꂽ��
				if (g_pad[0]->IsTrigger(enButtonX)) {

					//3�A�U����ԂɁB
					playerState = enState_ThreeCombo;

					//�N�[���^�C����ݒ�B
					m_coolTime = c_threeComboCoolTime;
				}
			}
		}

		void CPlayerAction::Update(const CVector3& pos, const CQuaternion& rot, const CVector3& forward, EnPlayerState& playerState) {

			//�N�[���^�C�����Ȃ�
			if (IsCoolTime()) {

				//�N�[���^�C�����X�V�B
				m_coolTime -= g_gameTime->GetFrameDeltaTime();
			}

			//�U����ԂȂ�
			if (playerState == enState_Attack) {

				//�a��^�C�~���O�Ńg���K�[�{�b�N�X��L���ɂ���B
				if (m_coolTime > 0.2f && m_coolTime < 0.6f) {

					m_triggerBox.Activate(pos, rot);
				}
				//����ȊO�͖����ɂ���B
				else {
					
					m_triggerBox.Deactivate();
				}
			}
			//�U�����ȊO�͖����ɂ���B
			else {

				m_triggerBox.Deactivate();
			}

			//�g���K�[�{�b�N�X���X�V�B
			m_triggerBox.Update(pos, rot, forward);
		}
	}
}