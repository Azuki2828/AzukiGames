#pragma once

namespace nsMyGame {

	//���b�N�I���A�C�R���N���X
	class CLockOnMarker
	{
	public:
		/**
		 * @brief �������֐��B
		*/
		void Init();

		/**
		 * @brief �폜�֐��B
		*/
		void Release();

		/**
		 * @brief �X�V�֐��B
		*/
		void UpdateMarker(const CVector2& position);
	private:
		/**
		 * @brief �g�嗦���X�V����֐��B
		*/
		void UpdateScale();
	private:
		CSpriteRender* m_lockOnMarker = nullptr;	//���b�N�I���A�C�R��
		CVector3 m_position = CVector3::Zero;		//���W
		float m_scale = 1.0f;						//�g��
		short m_sizeStep = 0;						//�g�嗦�ϓ��̒i�K
		float m_scaleDiff = 0.0f;					//�g�嗦�ϓ��̒l
		short m_updateNum = 0;						//�g�嗦�X�V�񐔁B

		static const float m_stepScale[];			//�i�K���Ƃ̖ڕW�ƂȂ�g�嗦
	};
}

