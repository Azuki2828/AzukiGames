#pragma once

#include "stdafx.h"
#include "DirectionLight.h"
#include "LightBase.h"

static const int MAX_DIRECTION_LIGHT = 4;	//�f�B���N�V�������C�g�̏����

struct LigData {
	DirectionLigData directionLigData[MAX_DIRECTION_LIGHT];		//���ׂẴ��f�����󂯂�f�B���N�V�������C�g�̃f�[�^
	Matrix m_viewProj;											//�v���W�F�N�V�����s��
	Vector3 eyePos = Vector3::Zero;								//���_�̍��W
};

class LightManager
{
public:
	/**
	 * @brief ���C�g�}�l�[�W���[�̃C���X�^���X���쐬����֐��B
	*/
	static void CreateInstance() {

		m_lightManager = new LightManager;
	}
	
	/**
	 * @brief ���C�g�}�l�[�W���[�̃C���X�^���X���擾����֐��B
	 * @return �C���X�^���X
	*/
	static LightManager* GetInstance() {

		return m_lightManager;
	}

	void Update();

	/**
	 * @brief ���C�g��ǉ�����֐��B
	 * @param light ���C�g�̃C���X�^���X
	*/
	void AddLight(LightBase* light);

	/**
	 * @brief ���C�g���폜����֐��B
	 * @param light ���C�g�̃C���X�^���X
	*/
	void RemoveLight(LightBase* light);
	/**
	 * @brief �o�^����Ă��郉�C�g��S�č폜�B
	*/
	void RemoveLightAll();
	/**
	 * @brief ���C�g�̃f�[�^���擾����֐��B
	 * @return ���C�g�̃f�[�^
	*/
	LigData* GetLigData() { return &m_ligData; }
private:
	LigData m_ligData;									//���C�g�̃f�[�^
	static LightManager* m_lightManager;				//���C�g�}�l�[�W���[�̃C���X�^���X
	std::list<DirectionLigData*> m_directionLights;		//�f�B���N�V�������C�g�̃f�[�^
};

