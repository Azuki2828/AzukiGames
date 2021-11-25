#include "stdafx.h"
#include "EffectManager.h"

namespace nsMyGame {

	namespace nsEffect {

		CEffectManager* CEffectManager::m_effectManager = nullptr;	//�G�t�F�N�g�Ǘ��N���X�̃C���X�^���X

		void CEffectManager::Init(const char16_t* filePath) {

			Effect* effect = NewGO<Effect>(enPriority_Zeroth);
			effect->Init(filePath);
		}
	}
}