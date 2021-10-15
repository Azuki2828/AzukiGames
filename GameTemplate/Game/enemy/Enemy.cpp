#include "stdafx.h"
#include "Enemy.h"

CEnemy* g_pCurrentEnemy = nullptr;

void IdleFunc(){
	MessageBox(nullptr, L"Idle...", L"�ʒm", MB_OK);
}

void AttackFunc() {

	MessageBox(nullptr, L"Attack!!", L"�ʒm", MB_OK);
}

void GuardFunc() {

	MessageBox(nullptr, L"Guard!!", L"�ʒm", MB_OK);
}


//PYBIND11_MODULE(Game, m) {
//	m.def("IdleFunc", &IdleFunc);
//	m.def("AttackFunc", &AttackFunc);
//	m.def("GuardFunc", &GuardFunc);
//	
//	/*pybind11::class_<Enemy>(m, "Enemy")
//		.def(pybind11::init())
//		.def("CallTest", &Enemy::CallTest)
//		;*/
//}


bool CEnemy::Start()
{
	return true;
}
void CEnemy::Update()
{
	// ���ݍX�V���������s���̃G�l�~�[�̃A�h���X����
	g_pCurrentEnemy = this;
	switch (m_state) {
		case enState::enState_Idle:	
			ImportModule("EnemyIdle");
			m_state = enState::enState_Attack;
			break;
		case enState::enState_Attack:
			ImportModule("EnemyAttack");
			m_state = enState::enState_Guard;
			break;
		case enState::enState_Guard:
			ImportModule("EnemyGuard");
			m_state = enState::enState_Idle;
			break;
	}
	auto updateFunc = m_enemyPyModule.attr("Update");
	//updateFunc();
}
void CEnemy::Render(CRenderContext& rc)
{

}