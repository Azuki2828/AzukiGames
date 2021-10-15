#pragma once


namespace nsMyGame {

	namespace nsPlayer {

		enum EnAnimationList {
			enAnim_Walk,
			enAnim_Idle,
			enAnim_Death,

			enAnimNum

		};
		class CPlayer : public CIGameObject
		{
			//�v���C���[�̏��
			enum class EnPlayerState {
				enState_Normal,
				enState_Yoi,
				enState_Death,

				enStateNum
			};

			//�����t�H���g�̃J���[���
			enum EnColor {
				en1,
				en2,
				en3,
				en4,
				en5,
				en6,
			};


			/**
			 * @brief ���W���[�����C���|�[�g����֐��B
			 * @param moduleName ���W���[����(Python�t�@�C����)
			*/
			void ImportModule(const char* moduleName) {
				// ���W���[�����C���|�[�g
				try {
					m_playerPyModule = pybind11::module::import(moduleName);
				}
				catch (pybind11::error_already_set& e) {
					MessageBoxA(nullptr, e.what(), "�G���[", MB_OK);
				}
			}

			/**
			 * @brief ���C�g�J�������X�V����֐��B
			*/
		public:
			void LightCameraUpdate();
			bool Start()override final;
			void Update()override final;

			/**
			 * @brief �X�e�[�g���X�V����֐��B
			*/
			void StateUpdate();

			/**
			 * @brief ���W���擾����֐��B
			 * @return
			*/
			const CVector3& GetPosition()const {

				return m_position;
			}

			/**
			 * @brief ���f�������_�[�̃C���X�^���X���擾����֐��B
			 * @return ���f�������_�[�̃C���X�^���X
			*/
			CModelRender* GetModelRender() {

				return m_modelRender;
			}

			/**
			 * @brief �����p�����[�^�[��ݒ肷��֐��B
			 * @param param  �����p�����[�^�[
			*/
			void SetYoiParam(const int param) {

				m_yoiParam = param;
			}

			/**
			 * @brief �����p�����[�^�[���擾����֐��B
			 * @return �����p�����[�^�[
			*/
			int GetYoiParam() {

				return m_yoiParam;
			}

			/**
			 * @brief �ړ��������s���֐��B
			*/
			void Move();

			/**
			 * @brief �t�H���g���X�V����֐��B
			*/
			void FontUpdate();

			/**
			 * @brief �X�e�[�g��ω�������֐��B
			 * @param state
			*/
			void SetState(int state) {
				switch (state) {
				case 0:
					m_playerState = EnPlayerState::enState_Normal;
					break;
				case 1:
					m_playerState = EnPlayerState::enState_Yoi;
					break;
				case 2:
					m_playerState = EnPlayerState::enState_Death;
					break;
				}

			}
		private:
			int m_yoiParam = 0;
			CVector4 m_color = CVector4::White;
			EnColor m_colorState = en1;
			int m_count = 0;
			EnPlayerState m_playerState = EnPlayerState::enState_Normal;
			CModelRender* m_modelRender = nullptr;
			CAnimationClip m_animationClip[enAnimNum];

			CVector3 m_position = {0.0f,0.0f,0.0f};
			CVector3 m_moveSpeed = CVector3::Zero;
			CharacterController m_charaCon;
			pybind11::module m_playerPyModule;

			nsFont::CFontRender* m_fontRender = nullptr;
			nsFont::CFontRender* m_fontRender2 = nullptr;
		};
	}
}

