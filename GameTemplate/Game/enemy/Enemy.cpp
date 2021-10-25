#include "stdafx.h"
#include "Enemy.h"

namespace nsMyGame {

	namespace nsEnemy {

		CEnemy* g_pCurrentEnemy = nullptr;

		void ChangeState(int stateNum) {

			g_pCurrentEnemy->ChangeState(stateNum);
		}

		float GetLengthToPlayer() {

			return g_pCurrentEnemy->GetLengthToPlayer();
		}

		void Move() {

			g_pCurrentEnemy->Move();
		}

		void Rotate() {

			g_pCurrentEnemy->Rotate();
		}

		void SetCoolTime(const float coolTime) {

			g_pCurrentEnemy->SetCoolTime(coolTime);
		}

		float GetCoolTime() {

			return g_pCurrentEnemy->GetCoolTime();
		}


		PYBIND11_MODULE(Game, m) {
			m.def("ChangeState", &ChangeState);
			m.def("GetLengthToPlayer", &GetLengthToPlayer);
			m.def("Move", &Move);
			m.def("Rotate", &Rotate);
			m.def("SetCoolTime", &SetCoolTime);
			m.def("GetCoolTime", &GetCoolTime);
		}


		bool CEnemy::Start()
		{
			m_player = FindGO<nsPlayer::CPlayer>("player");

			//�L�����N�^�[�R���g���[���[���������B
			m_charaCon.Init(
				20.0f,			//���a�B
				200.0f,			//�����B
				m_position		//���W�B
			);

			//�h���N���X��StartSub()�֐��̌��ʂ�Ԃ��B
			return StartSub();
		}

		void CEnemy::Update()
		{
			//�h���N���X��UpdateSnb()�֐����Ăяo���B
			UpdateSub();

			UpdateForward();


			m_modelRender->SetPosition(m_position);
			m_modelRender->SetRotation(m_rotation);

			if (m_coolTime > 0.0f) {

				m_coolTime -= g_gameTime->GetFrameDeltaTime();
			}
			else {
				m_coolTime = 0.0f;
			}
		}
		void CEnemy::Render(CRenderContext& rc)
		{

		}

		void CEnemy::Rotate() {

			//�ړ��{�^�������͂���Ă��Ȃ�������
			if (fabsf(m_moveSpeed.x) < 0.001f
				&& fabsf(m_moveSpeed.z) < 0.001f) {
				//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
				return;
			}

			//��]�p�x�����߂�B
			float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);

			//��]��ݒ�B
			m_rotation.SetRotationY(-angle);
		}

		void CEnemy::UpdateForward() {

			//��]�s����v�Z�B
			auto mRot = CMatrix::Identity;
			mRot.MakeRotationFromQuaternion(m_rotation);

			//�O������ݒ�B
			m_forward.x = mRot.m[2][0];
			m_forward.y = mRot.m[2][1];
			m_forward.z = mRot.m[2][2];

			//���K���B
			m_forward.Normalize();
		}
	}
}