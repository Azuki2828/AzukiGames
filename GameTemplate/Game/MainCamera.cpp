#include "stdafx.h"
#include "MainCamera.h"
#include "Player.h"

bool MainCamera::Start() {

	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(m_tar);

	return true;
}

void MainCamera::Update() {

	m_player = FindGO<Player>("player");
	if (m_player != nullptr) {
		m_tar = m_player->GetPosition();
		m_tar.y += 50.0f;
	}

	m_pos = m_tar + toPos;

	g_camera3D->SetTarget(m_tar);
	g_camera3D->SetPosition(m_pos);
	g_camera3D->Update();

}