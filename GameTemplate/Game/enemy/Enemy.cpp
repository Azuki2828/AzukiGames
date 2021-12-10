#include "stdafx.h"
#include "Enemy.h"
#include "../AttackCollision.h"

namespace nsMyGame {

	namespace nsEnemy {

		CEnemy* g_pCurrentEnemy = nullptr;

		/**
		 * @brief �X�e�[�g��ύX����֐��B
		 * @param stateNum �X�e�[�g�ԍ�
		*/
		void ChangeState(int stateNum) {

			g_pCurrentEnemy->ChangeState(stateNum);
		}

		/**
		 * @brief �v���C���[�Ƃ̋����𑪂�֐��B
		 * @return �v���C���[�Ƃ̋���
		*/
		float GetLengthToPlayer() {

			return g_pCurrentEnemy->GetLengthToPlayer();
		}

		/**
		 * @brief �ړ��֐��B
		*/
		void Move() {

			g_pCurrentEnemy->Move();
		}

		/**
		 * @brief ��]�֐��B
		*/
		void Rotate() {

			g_pCurrentEnemy->Rotate();
		}

		/**
		 * @brief �N�[���^�C����ݒ肷��֐��B
		 * @param coolTime �N�[���^�C��
		*/
		void SetCoolTime(const float coolTime) {

			g_pCurrentEnemy->SetCoolTime(coolTime);
		}

		/**
		 * @brief �N�[���^�C�����擾����֐��B
		 * @return �N�[���^�C��
		*/
		float GetCoolTime() {

			return g_pCurrentEnemy->GetCoolTime();
		}

		/**
		 * @brief �A�j���[�V�������X�V����֐��B
		*/
		void AnimationUpdate() {

			g_pCurrentEnemy->AnimationUpdate();
		}

		/**
		 * @brief ����ł���H
		 * @return ����ł��邩�ǂ����̃t���O
		*/
		bool IsDeath() {

			return g_pCurrentEnemy->IsDeath();
		}

		/**
		 * @brief ���g���폜����֐��B
		*/
		void Delete() {

			g_pCurrentEnemy->Delete();
		}

		/**
		 * @brief �g���K�[�{�b�N�X���X�V����֐��B
		*/
		void UpdateTriggerBox() {

			g_pCurrentEnemy->UpdateTriggerBox(
				g_pCurrentEnemy->GetPosition(),
				g_pCurrentEnemy->GetRotation(),
				g_pCurrentEnemy->GetForward()
			);
		}

		void SetGuardTime(const float guardTime) {

			g_pCurrentEnemy->SetGuardTime(guardTime);
		}

		float GetGuardTime() {

			return g_pCurrentEnemy->GetGuardTime();
		}

		bool IsGuarded() {

			return g_pCurrentEnemy->IsGuarded();
		}

		void JudgeDamage() {

			g_pCurrentEnemy->JudgeDamage();
		}

		//Python���Ɋ֐���n���B
		PYBIND11_MODULE(Game, m) {
			m.def("ChangeState", &ChangeState);
			m.def("GetLengthToPlayer", &GetLengthToPlayer);
			m.def("Move", &Move);
			m.def("Rotate", &Rotate);
			m.def("SetCoolTime", &SetCoolTime);
			m.def("GetCoolTime", &GetCoolTime);
			m.def("AnimationUpdate", &AnimationUpdate);
			m.def("IsDeath", &IsDeath);
			m.def("Delete", &Delete);
			m.def("UpdateTriggerBox", &UpdateTriggerBox);
			m.def("SetGuardTime", &SetGuardTime);
			m.def("GetGuardTime", &GetGuardTime);
			m.def("IsGuarded", &IsGuarded);
			m.def("JudgeDamage", &JudgeDamage);
		}


		bool CEnemy::Start()
		{
			//�v���C���[�������B
			m_player = FindGO<nsPlayer::CPlayer>(c_classNamePlayer);

			//�h���N���X��StartSub()�֐��̌��ʂ�Ԃ��B
			return StartSub();
		}

		void CEnemy::OnDestroy() {

			//���f�����폜�B
			if (m_modelRender != nullptr) {
				DeleteGO(m_modelRender);
			}
		}

		void CEnemy::Update()
		{
			//�h���N���X��UpdateSub()�֐����Ăяo���B
			UpdateSub();

			//�O�������X�V�B
			UpdateForward();

			//���W��ݒ�B
			m_modelRender->SetPosition(m_position);

			//��]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//�N�[���^�C�����X�V�B
			if (m_coolTime > 0.0f) {

				m_coolTime -= g_gameTime->GetFrameDeltaTime();
			}
			else {
				m_coolTime = 0.0f;
			}

			//�K�[�h���Ԃ��X�V�B
			if (m_guardTime > 0.0f) {

				m_guardTime -= g_gameTime->GetFrameDeltaTime();
			}
			else {

				m_guardTime = 0.0f;
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

		void CEnemy::JudgeDamage() {

			//��������Ă���G�̍U�������蔻��𒲂ׂ�B
			auto playerCollision = FindGOs<CAttackCollision>(c_playerAttackCollisionName);

			//�����蔻�菈���B
			//���̃t���[���őS�Ă̓����蔻��Ƃ̏Փ˔�������邽�߁A��C�Ƀ_���[�W���󂯂�\������B
			//���ꂪ���Ȃ�Afor���̓����ŃX�e�[�g�𒲂ׂ邱�ƁI
			for (auto& collision : playerCollision) {

				//�K�[�h�������Ȃ瑁�����^�[���B
				//if (m_playerState == enState_GuardSuccess) {
				//
				//	return;
				//}

				//���̂Ƃ̓����蔻��𒲂ׂ�B
				CPhysicsWorld::GetInstance()->ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {

					//�g���K�[�{�b�N�X�ƐڐG�����B
					if (collision->IsSelf(contactObject)) {

						////�K�[�h�����Ȃ�K�[�h������ԂɁB
						//if (m_playerState == enState_Guard) {
						//
						//	m_playerState = enState_GuardSuccess;
						//	m_playerAction.GuardSuccess();
						//
						//	//�����͂����ŏI���B
						//	return;
						//}

						//�_���[�W���󂯂�B
						SetReceiveDamage(true);
					}
					});
			}
		}
	}
}