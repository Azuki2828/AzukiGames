#pragma once
#include "../../MiniEngine/SpringCamera.h"


namespace nsMyGame {

	namespace nsPlayer {

		class CPlayer;
	}

	class CMainCamera : public CIGameObject
	{
	public:
		/**
		 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
		 * @return ���������H
		*/
		bool Start()override final;

		/**
		 * @brief �X�V�֐��B
		*/
		void Update()override final;
	private:
		SpringCamera m_springCamera;						//�΂˃J�����B
		CVector3 m_pos = CVector3::Zero;					//���_
		CQuaternion m_rot = CQuaternion::Identity;			//��]
		CVector3 m_sca = CVector3::One;						//�g��

		CVector3 m_tar = CVector3::Zero;					//�����_
		CVector3 m_toCameraPos = { 0.0f,150.0f,-200.0f };	//�J�����̒ǉ����W

		nsPlayer::CPlayer* m_player = nullptr;
	};
}

