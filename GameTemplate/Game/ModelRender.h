#pragma once

//���f���Ǘ��N���X

class ModelRender : public IGameObject
{
public:
	void Update()override final;
	void Render(RenderContext& rc)override final;
public:
	/**
	 * @brief �������֐��B
	*/
	void Init();

	/**
	 * @brief tkm�t�@�C����ݒ肷��֐��B
	 * @param filePathTkm �t�@�C����(.tkm)
	*/
	void SetFilePathTkm(const char* filePathTkm) {
		m_filePathTkm = filePathTkm;
	}

	/**
	 * @brief tks�t�@�C����ݒ肷��֐��B
	 * @param filePathTks �t�@�C����(.tks)
	*/
	void SetFilePathTks(const char* filePathTks) {
		m_filePathTks = filePathTks;
	}

	/**
	 * @brief ���W��ݒ肷��֐��B
	 * @param pos ���W
	*/
	void SetPosition(const Vector3& pos) {
		m_pos = pos;
	}

	/**
	 * @brief ���W���擾����֐��B
	 * @return ���W
	*/
	Vector3 GetPosition() {

		return m_pos;
	}
private:
	const char* m_filePathTkm = nullptr;
	const char* m_filePathTks = nullptr;

	Vector3 m_pos = Vector3::Zero;
	Quaternion m_rot = Quaternion::Identity;
	Vector3 m_sca = Vector3::One;

	Model m_model;
	ModelInitData m_modelInitData;
	Animation m_animation;
	AnimationClip* m_animationClip = nullptr;
	Skeleton m_skeleton;
};

