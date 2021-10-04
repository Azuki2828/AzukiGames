#pragma once

#include "stdafx.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "LightBase.h"

static const int c_maxDirectionLightNum = 4;	//�f�B���N�V�������C�g�̏����
static const int c_maxPointLightNum = 100;		//�|�C���g���C�g�̏����


//���C�g�̃f�[�^
struct LigData {
	DirectionLigData directionLigData[c_maxDirectionLightNum];		//�f�B���N�V�������C�g�̃f�[�^
	PointLigData pointLigData[c_maxPointLightNum];					//�|�C���g���C�g�̃f�[�^
	Vector3 eyePos = Vector3::Zero;								//���_�̍��W
	int pointLightNum = 0;										//�|�C���g���C�g�̑���
	Matrix m_viewProj;											//�v���W�F�N�V�����s��
};

//���C�g�Ǘ��N���X
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
	 * @brief �o�^����Ă��郉�C�g��S�č폜����֐��B
	*/
	void RemoveLightAll();
	/**
	 * @brief ���C�g�̃f�[�^���擾����֐��B
	 * @return ���C�g�̃f�[�^
	*/
	LigData* GetLigData() { return &m_ligData; }

	/**
	 * @brief �X�V�֐��B
	*/
	void Update();
private:
	LigData m_ligData;									//���C�g�̃f�[�^
	static LightManager* m_lightManager;				//���C�g�}�l�[�W���[�̃C���X�^���X
	std::list<DirectionLigData*> m_directionLights;		//�f�B���N�V�������C�g�̃f�[�^
	std::list<PointLigData*> m_pointLights;				//�|�C���g���C�g�̃f�[�^
};

