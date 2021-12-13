#include "stdafx.h"
#include "GameTitle.h"
#include "Game.h"

namespace nsMyGame {

	bool CGameTitle::Start() {

		//�^�C�g���摜���������B
		m_titleSprite = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_titleSprite->Init(c_filePathTitleSprite, FRAME_BUFFER_W, FRAME_BUFFER_H);

		return true;
	}

	void CGameTitle::OnDestroy() {

		//�^�C�g���摜���폜�B
		DeleteGO(m_titleSprite);
	}

	void CGameTitle::Update() {

		//A�{�^���������ꂽ��
		if (g_pad[0]->IsTrigger(enButtonA)) {

			//�Q�[���V�[���Ɉڍs�B
			NewGO<CGameMain>(enPriority_Zeroth);

			//�^�C�g����ʂ��폜�B
			DeleteGO(this);
		}
	}
}