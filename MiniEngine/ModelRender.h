#pragma once

namespace nsMyGame {

	//���f���Ǘ��N���X
	class CModelRender : public IGameObject
	{
		//�R���X�^���g�o�b�t�@�ɓ]������f�[�^
		struct SModelData {
			int shadowReceiverFlg = 0;		//�V���h�E���V�[�o�[�t���O
		};
	public:
		/**
		 * @brief �X�V�֐��B
		*/
		void Update()override final;

		/**
		 * @brief �`��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
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
		 * @param animNum �A�j���[�V�������B
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
		 * @brief ���[���h�s����X�V����֐��B(��������)
		 * @param pos ���W
		 * @param rot ��]
		 * @param sca �g�嗦
		*/
		void UpdateWorldMatrix(const Vector3& pos, const Quaternion& rot, const Vector3& sca)
		{
			m_model.UpdateWorldMatrix(pos, rot, sca);
		}

		/**
		 * @brief ���[���h�s����X�V����֐��B(�����Ȃ�)
		*/
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
		const Vector3& GetPosition()const {

			return m_pos;
		}

		/**
		 * @brief ��]����ݒ肷��֐��B
		 * @param rot ��]��
		*/
		void SetRotation(const Quaternion& rot) {

			m_rot = rot;
		}

		/**
		 * @brief ��]�����擾����֐��B
		 * @return ��]��
		*/
		const Quaternion& GetRotation()const {

			return m_rot;
		}

		/**
		 * @brief �g�嗦��ݒ肷��֐��B
		 * @param sca �g�嗦
		*/
		void SetScale(const Vector3& sca) {

			m_sca = sca;
		}

		/**
		 * @brief �g�嗦���擾����֐��B
		 * @return �g�嗦
		*/
		const Vector3& GetScale()const {

			return m_sca;
		}

		/**
		 * @brief �V���h�E�L���X�^�[�t���O��ݒ肷��֐��B
		 * @param flg �V���h�E�L���X�^�[�t���O�B
		*/
		void SetShadowCasterFlag(bool flg) {

			m_shadowCasterFlag = flg;
		}

		/**
		 * @brief �V���h�E���V�[�o�[�t���O��ݒ肷��֐��B
		 * @param flg �V���h�E���V�[�o�[�t���O
		*/
		void SetShadowReceiverFlag(bool flg) {

			m_sModelData.shadowReceiverFlg = flg;
		}

		/**
		 * @brief ���f���̏㎲��ݒ肷��֐��B
		 * @param modelUpAxis ��ɂ�������
		*/
		void SetModelUpAxis(EnModelUpAxis modelUpAxis) {
			m_modelInitData.m_modelUpAxis = modelUpAxis;
		}
	private:
		/**
		 * @brief �V���h�E���f�����쐬����֐��B
		*/
		void CreateShadowModel();

		/**
		 * @brief tkm�t�@�C����tks�t�@�C���̃p�X��ݒ肷��֐��B
		*/
		void SetFilePathTkmAndTks();
	private:
		const char* m_filePathTkm = nullptr;		//tkm�t�@�C���p�X
		const char* m_filePathTks = nullptr;		//tks�t�@�C���p�X

		bool m_shadowCasterFlag = false;			//�V���h�E�L���X�^�[�t���O�B

		Vector3 m_pos = Vector3::Zero;				//���W
		Quaternion m_rot = Quaternion::Identity;	//��]��
		Vector3 m_sca = Vector3::One;				//�g�嗦

		Model m_model;								//���f��
		Model m_shadowModel;						//�V���h�E�쐬�p�̃��f���B
		SModelData m_sModelData;					//�R���X�^���g�o�b�t�@�ɓ]������f�[�^
		ModelInitData m_modelInitData;				//���f���f�[�^
		Skeleton m_skeleton;						//�X�P���g��

		bool m_animFlg = false;						//�A�j���[�V�����Đ��t���O
		int m_animNum = 0;							//�A�j���[�V������
		Animation m_animation;						//�A�j���[�V����
		AnimationClip* m_animationClip = nullptr;	//�A�j���[�V�����N���b�v
	};
}

