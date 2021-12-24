#pragma once
#include "Player.h"

////////////////////////////////////////////////////
//�v���C���[�̃X�e�[�g�ɂ��X�V���`����w�b�_�[//
////////////////////////////////////////////////////

namespace nsMyGame {

	namespace nsPlayer {

		void CPlayer::CommonStateProcess() {

			//�ړ������B
			m_playerAction.Move(m_position, m_forward, m_playerState);

			//��]�����B
			m_playerAction.Rotate(m_rotation);

			//�O�������X�V�B
			UpdateForward();

			//�A�N�V���������B
			m_playerAction.Action(m_playerState, m_isSelect);

			//�A�j���[�V���������B
			m_playerAnimation.Update(*m_modelRender, m_playerState);

			//�N�[���^�C�����X�V�B
			m_playerAction.Update();

			//����ł����Ԃ��ǂ�������B
			if (IsDeath()){ m_playerState = enState_Death; }

			//���W��ݒ�B
			m_modelRender->SetPosition(m_position);

			//��]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//���C�g�J�������X�V�B
			LightCameraUpdate();

			m_isSelect = false;
		}

		void CPlayer::IsRollingStateProcess() {

			//�ړ������B
			m_playerAction.Move(m_position, m_forward, m_playerState);

			//�O�������X�V�B
			UpdateForward();

			//�A�N�V���������B
			m_playerAction.Action(m_playerState, m_isSelect);

			//�A�j���[�V���������B
			m_playerAnimation.Update(*m_modelRender, m_playerState);

			//�N�[���^�C�����X�V�B
			m_playerAction.Update();

			//����ł����Ԃ��ǂ�������B
			if (IsDeath()) { m_playerState = enState_Death; }

			//���W��ݒ�B
			m_modelRender->SetPosition(m_position);

			//��]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//���C�g�J�������X�V�B
			LightCameraUpdate();

			m_isSelect = false;
		}

		void CPlayer::IsDeathStateProcess() {

			//����ł����Ԃɂ���B
			m_playerState = enState_Death;

			//�A�j���[�V���������B
			m_playerAnimation.Update(*m_modelRender, m_playerState);

			//���C�g�J�������X�V�B
			LightCameraUpdate();
		}

		void CPlayer::IsDamagedStateProcess() {

			//�ړ������B
			m_playerAction.Move(m_position, m_forward, m_playerState);

			//�O�������X�V�B
			UpdateForward();

			//�A�N�V���������B
			m_playerAction.Action(m_playerState, m_isSelect);

			//�A�j���[�V���������B
			m_playerAnimation.Update(*m_modelRender, m_playerState);

			//�N�[���^�C�����X�V�B
			m_playerAction.Update();

			//����ł����Ԃ��ǂ�������B
			if (IsDeath()) { m_playerState = enState_Death; }

			//���W��ݒ�B
			m_modelRender->SetPosition(m_position);

			//��]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//���C�g�J�������X�V�B
			LightCameraUpdate();

			m_isSelect = false;
		}

		void CPlayer::IsGuardStateProcess() {

			//�ړ������B
			m_playerAction.Move(m_position, m_forward, m_playerState);

			//�O�������X�V�B
			UpdateForward();

			//�A�N�V���������B
			m_playerAction.Action(m_playerState, m_isSelect);

			//�A�j���[�V���������B
			m_playerAnimation.Update(*m_modelRender, m_playerState);

			//�N�[���^�C�����X�V�B
			m_playerAction.Update();

			//���W��ݒ�B
			m_modelRender->SetPosition(m_position);

			//��]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//���C�g�J�������X�V�B
			LightCameraUpdate();

			m_isSelect = false;
		}

		void CPlayer::IsAttackStateProcess() {

			//�ړ������B
			m_playerAction.Move(m_position, m_forward, m_playerState);

			//�O�������X�V�B
			UpdateForward();

			//�A�N�V���������B
			m_playerAction.Action(m_playerState, m_isSelect);

			//�A�j���[�V���������B
			m_playerAnimation.Update(*m_modelRender, m_playerState);

			//�N�[���^�C�����X�V�B
			m_playerAction.Update();

			//����ł����Ԃ��ǂ�������B
			if (IsDeath()) { m_playerState = enState_Death; }

			//���W��ݒ�B
			m_modelRender->SetPosition(m_position);

			//��]��ݒ�B
			m_modelRender->SetRotation(m_rotation);

			//���C�g�J�������X�V�B
			LightCameraUpdate();

			m_isSelect = false;
		}
	}
}