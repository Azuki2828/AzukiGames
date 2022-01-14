#pragma once
#include "../../MiniEngine/SpringCamera.h"

namespace nsMyGame {

	//�G�C���A�X�錾
	namespace nsPlayer {

		class CPlayer;
	}

	//���C���J�����N���X
	class CMainCamera : public CIGameObject
	{
		//�X�e�[�g
		enum EnState {
			enNormal,		//�ʏ�
			enShake			//�h����
		};
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

		/**
		 * @brief �J������h���Ԃɂ���֐��B
		*/
		void ShakeCamera() {

			m_state = enShake;
		}

		/**
		 * @brief �J�����̏�Ԃ�ʏ��Ԃɂ���֐��B
		*/
		void SetNormalCamera() {

			m_state = enNormal;
		}
	private:
		EnState m_state = enNormal;							//�X�e�[�g
		float m_eventTimer = 0.0f;							//�C�x���g�^�C�}�[(�{�X�o�ꎞ�̃J�������[�N)
		SpringCamera m_springCamera;						//�΂˃J�����B
		CVector3 m_pos = CVector3::Zero;					//���_
		CQuaternion m_rot = CQuaternion::Identity;			//��]
		CVector3 m_sca = CVector3::One;						//�g��

		CVector3 m_tar = CVector3::Zero;					//�����_
		CVector3 m_toCameraPos = { 0.0f,150.0f,200.0f };	//�J�����̒ǉ����W

		//�e�N���X�̃|�C���^�ϐ�
		nsPlayer::CPlayer* m_player = nullptr;
	};
}

