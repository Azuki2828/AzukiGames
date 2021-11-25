#pragma once

namespace nsMyGame {

	namespace nsEffect {

		//�G�t�F�N�g�Ǘ��N���X
		class CEffectManager
		{
		private:
			//�G�t�F�N�g�̃f�[�^
			struct SEffectData {

				int effectNum = -1;								//�G�t�F�N�g�ԍ�
				CVector3 position = CVector3::Zero;				//���W
				CQuaternion rotation = CQuaternion::Identity;	//��]
				CVector3 scale = CVector3::One;					//�g��
			};
		public:
			/**
			 * @brief �G�t�F�N�g�Ǘ��N���X�̃C���X�^���X���쐬����֐��B
			*/
			static void CreateInstance() {

				m_effectManager = new CEffectManager;
			}

			/**
			 * @brief �G�t�F�N�g�Ǘ��N���X�̃C���X�^���X���擾����֐��B
			 * @return �G�t�F�N�g�Ǘ��N���X�̃C���X�^���X
			*/
			static CEffectManager* GetInstance() {

				return m_effectManager;
			}

			/**
			 * @brief �������֐��B
			 * @param filePath �t�@�C���p�X
			*/
			void Init(const char16_t* filePath);

			void Play(const int efkNum) {


			}
			/**
			 * @brief ���W��ݒ肷��֐��B
			 * @param efkNum �G�t�F�N�g�ԍ�
			 * @param pos ���W
			*/
			void SetPosition(const int efkNum, const CVector3& pos) {

				m_effectList[efkNum]->position = pos;
			}

			/**
			 * @brief ���W���擾����֐��B
			 * @param efkNum �G�t�F�N�g�ԍ�
			 * @return ���W
			*/
			const CVector3& GetPosition(const int efkNum) {

				return m_effectList[efkNum]->position;
			}

			/**
			 * @brief ��]��ݒ肷��֐��B
			 * @param efkNum �G�t�F�N�g�ԍ�
			 * @param rot ��]
			*/
			void SetRotation(const int efkNum, const CQuaternion& rot) {

				m_effectList[efkNum]->rotation = rot;
			}

			/**
			 * @brief ��]���擾����֐��B
			 * @param efkNum �G�t�F�N�g�ԍ�
			 * @return ��]
			*/
			const CQuaternion& GetRotation(const int efkNum) {

				return m_effectList[efkNum]->rotation;
			}

			/**
			 * @brief �g���ݒ肷��֐��B
			 * @param efkNum �G�t�F�N�g�ԍ�
			 * @param sca �g��
			*/
			void SetScale(const int efkNum, const CVector3& sca) {

				m_effectList[efkNum]->scale = sca;
			}

			/**
			 * @brief �g����擾����֐��B
			 * @param efkNum �G�t�F�N�g�ԍ�
			 * @return �g��
			*/
			const CVector3& GetScale(const int efkNum) {

				return m_effectList[efkNum]->scale;
			}
		private:
			int m_effectNum = 0;						//�G�t�F�N�g�̐�
			static CEffectManager* m_effectManager;		//�G�t�F�N�g�Ǘ��N���X�̃C���X�^���X
			std::vector<SEffectData*> m_effectList;		//�G�t�F�N�g�̃��X�g
		};
	}
}

