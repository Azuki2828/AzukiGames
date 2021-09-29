#pragma once
class Enemy : public IGameObject
{
private:
	/**
	 * @brief �X�e�[�g�B
	*/
	enum class enState {
		enState_Idle,
		enState_Attack,
		enState_Guard,
	};

	/**
	 * @brief ���W���[�����C���|�[�g����֐��B
	 * @param moduleName ���W���[����(Python�t�@�C����)
	*/
	void ImportModule(const char* moduleName) {
		// ���W���[�����C���|�[�g
		try {
			m_enemyPyModule = pybind11::module::import(moduleName);
		}
		catch (pybind11::error_already_set& e) {
			MessageBoxA(nullptr, e.what(), "�G���[", MB_OK);
		}
	}
public:
	bool Start() override;
	void Update() override;
	void CallTest() {
		MessageBox(nullptr, L"Success Connect to Class Function!!", L"�ʒm", MB_OK);
	}
	void Render(RenderContext& rc);
private:
	enState m_state = enState::enState_Idle;
	pybind11::module m_enemyPyModule;
};

