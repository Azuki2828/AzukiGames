#pragma once
#include "LightBase.h"

struct PointLigData {
	Vector3 pos = Vector3::Zero;		//���W
	float pad1;							//�p�f�B���O
	Vector4 color = Vector4::White;		//�J���[
	Vector2 attn;						// �����p�����[�^�Bx�ɉe���͈́Ay�ɂ͉e�����ɗݏ悷��p�����[�^
	Vector2 pad2;						//�p�f�B���O
};

class PointLight : public LightBase
{
	bool StartSub();
	~PointLight();
public:

	/**
	 * @brief ���W��ݒ肷��֐��B
	 * @param pos ���W
	*/
	void SetPosition(const Vector3& pos) {
		m_poiLigData.pos = pos;
	}

	/**
	 * @brief ���W���擾����֐��B
	 * @return ���W
	*/
	const Vector3 GetPosition()const {

		return m_poiLigData.pos;
	}

	/**
	 * @brief �J���[��ݒ肷��֐��B
	 * @param color �J���[
	*/
	void SetColor(const Vector3& color) {

		m_poiLigData.color.x = color.x;
		m_poiLigData.color.y = color.y;
		m_poiLigData.color.z = color.z;
	}

	/**
	 * @brief �J���[��ݒ肷��֐��B
	 * @param color �J���[
	*/
	void SetColor(const float red, const float green, const float blue) {

		m_poiLigData.color.x = red;
		m_poiLigData.color.y = green;
		m_poiLigData.color.z = blue;
	}

	/**
	 * @brief �J���[���擾����֐��B
	 * @return �J���[
	*/
	const Vector4& GetColor()const {

		return m_poiLigData.color;
	}

	/**
	 * @brief �e���͈͂�ݒ肷��֐��B
	 * @param range �e���͈�
	*/
	void SetRange(float range) {

		m_poiLigData.attn.x = range;
	}

	/**
	 * @brief �e���͈͂��擾����֐��B
	 * @return �e���͈�
	*/
	const float GetRange()const {

		return m_poiLigData.attn.x;
	}

	/**
	 * @brief �e�����̗ݏ搔��ݒ肷��֐��B
	 * @param powParam �e�����̗ݏ搔
	*/
	void SetAffectPowParam(const float powParam) {

		m_poiLigData.attn.y = powParam;
	}

	/**
	 * @brief �e�����̗ݏ搔���擾����֐��B
	 * @return �e�����̗ݏ搔
	*/
	const float GetAffectpowParam()const {

		return m_poiLigData.attn.y;
	}

	/**
	 * @brief ���C�g�̏����擾�B
	 * @return ���C�g�̏��
	*/
	void* GetLigData() { return &m_poiLigData; }

private:
	ConstantBuffer m_cb;					//�R���X�^���g�o�b�t�@
	DescriptorHeap m_ds;					//�f�B�X�N���v�^�q�[�v
	PointLigData m_poiLigData;				//�|�C���g���C�g�̏��
};

