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
	 * @brief �A�j���[�V������ݒ肷��֐��B
	 * @param animClip �A�j���[�V�����N���b�v
	 * @param animNum �A�j���[�V�����ԍ�
	*/
	void InitAnimation(AnimationClip* animClip, int animNum) {
		m_animationClip = animClip;
		m_animNum = animNum;
	}

	/**
	 * @brief �A�j���[�V�������Đ�����t���O
	 * @param flg �A�j���[�V�����t���O
	*/
	void SetAnimFlg(bool flg) {
		m_animFlg = flg;
	}

	/**
	 * @brief �A�j���[�V�����̍Đ��B
	 * @param animNo �A�j���[�V�����N���b�v�̔ԍ�
	 * @param interpolateTime �⊮����
	*/
	void PlayAnimation(int animNo, float interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	/**
	 * @brief ���[���h�s����X�V����֐��B
	 * @param pos ���W
	 * @param rot ��]
	 * @param sca �g�嗦
	*/
	void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 sca)
	{
		m_model.UpdateWorldMatrix(pos, rot, sca);
	}

	void UpdateWorldMatrix()
	{
		m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);
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
	Skeleton m_skeleton;

	bool m_animFlg = false;
	int m_animNum = 0;
	Animation m_animation;
	AnimationClip* m_animationClip = nullptr;
};

