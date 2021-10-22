#include "stdafx.h"
#include "Enemy.h"

namespace nsMyGame {

	namespace nsEnemy {

		CEnemy* g_pCurrentEnemy = nullptr;

		void IdleFunc() {
			MessageBox(nullptr, L"Idle...", L"�ʒm", MB_OK);
		}

		void AttackFunc() {

			MessageBox(nullptr, L"Attack!!", L"�ʒm", MB_OK);
		}

		void GuardFunc() {

			MessageBox(nullptr, L"Guard!!", L"�ʒm", MB_OK);
		}


		PYBIND11_MODULE(Game, m) {
			m.def("IdleFunc", &IdleFunc);
			m.def("AttackFunc", &AttackFunc);
			m.def("GuardFunc", &GuardFunc);
		}


		bool CEnemy::Start()
		{
			return true;
		}
		void CEnemy::Update()
		{
			// ���ݍX�V���������s���̃G�l�~�[�̃A�h���X����
			g_pCurrentEnemy = this;
			switch (m_enemyState) {
			case EnEnemyState::enState_Idle:
				ImportModule("EnemyIdle");
				break;
			case EnEnemyState::enState_Attack:
				ImportModule("EnemyAttack");
				break;
			}
			auto updateFunc = m_enemyPyModule.attr("Update");
			updateFunc();
		}
		void CEnemy::Render(CRenderContext& rc)
		{

		}
	}
}