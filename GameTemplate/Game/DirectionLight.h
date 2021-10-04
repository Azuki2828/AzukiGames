#pragma once
#include "LightBase.h"


//�f�B���N�V�������C�g�̃f�[�^
struct DirectionLigData {
	Vector3 Dir	= Vector3::Zero;	//����
	float pad = 0.0f;				//�p�f�B���O
	Vector4 Col	= Vector4::White;	//�F
};

//���s�����N���X
class DirectionLight : public LightBase
{
	/**
	 * @brief �I�[�o�[���C�h���ꂽ�J�n�����֐��B
	 * @return ���������H
	*/
	bool StartSub();
	~DirectionLight();
public:
	/**
	 * @brief ���C�g�̕�����ݒ肷��֐��B
	 * @param _x x����
	 * @param _y y����
	 * @param _z z����
	*/
	void SetLigDirection(float _x = 0.0f, float _y = -1.0f, float _z = 1.0f) {
		m_dirLigData.Dir.x = _x;
		m_dirLigData.Dir.y = _y;
		m_dirLigData.Dir.z = _z;
		//���K���B
		m_dirLigData.Dir.Normalize();
	}

	/**
	 * @brief ���C�g�̕�����ݒ肷��֐��B
	 * @param dir ����
	*/
	void SetLigDirection(const Vector3& dir) {
		m_dirLigData.Dir = dir;
		//���K���B
		m_dirLigData.Dir.Normalize();
	}

	/**
	 * @brief �f�B���N�V�������C�g���擾�B
	 * @return �f�B���N�V�������C�g
	*/
	const Vector3* GetLigDirection() { 
		return &m_dirLigData.Dir;
	}

	/**
	 * @brief ���C�g�̐F��ݒ�B
	 * @param _x �Ԑ���
	 * @param _y �ΐ���
	 * @param _z ����
	*/
	void SetLigColor(float _x = 50.0f, float _y = 50.0f, float _z = 50.0f) {
		m_dirLigData.Col.x = _x;
		m_dirLigData.Col.y = _y;
		m_dirLigData.Col.z = _z;
	}

	/**
	 * @brief ���C�g�̐F��ݒ�B
	 * @param col �F���(RGB)
	*/
	void SetLigColor(const Vector3& col) {
		m_dirLigData.Col = col;
	}

	/**
	 * @brief ���C�g�̃f�[�^�擾�B
	 * @return ���C�g�̃f�[�^
	*/
	void* GetLigData() { return &m_dirLigData; }
private:
	DirectionLigData m_dirLigData;					//�f�B���N�V�������C�g�̃f�[�^
};