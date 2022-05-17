#pragma once
namespace nsMyGame {

	namespace nsCamera {

		//�J�����N���X
		class CCameraBase
		{
		public:
			/**
			 * @brief �������֐��B
			 * @return ���������H
			*/
			bool Start() {

				return StartSub();
			}

			/**
			 * @brief �X�V�֐��B
			*/
			void Update() {

				UpdateSub();
			}

			/**
			 * @brief ���_�̍��W���擾����֐��B
			 * @return ���_�̍��W
			*/
			const CVector3& GetPosition()const {

				return m_position;
			}

			/**
			 * @brief �����_�̍��W���擾����֐��B
			 * @return �����_�̍��W
			*/
			const CVector3& GetTarget()const {

				return m_target;
			}

			/**
			 * @brief �J�������L�������ׂ�֐��B
			 * @return �J�������L���H
			*/
			const bool IsEnable()const {

				return m_isEnable;
			}

			/**
			 * @brief �J������؂�ւ����Ƃ��ɌĂяo�����֐��B
			*/
			void Switched() {

				//�J������L�����B
				m_isEnable = true;

				//�T�u�N���X�ł̃J�����؂�ւ�������̏������Ăяo���B
				SubSwitched();
			}

			/**
			 * @brief �T�u�N���X�ł̃J�����؂�ւ�������p�̊֐��B
			*/
			virtual void SubSwitched() {}

			/**
			 * @brief ����֐��B
			*/
			void Release() {

				//�J�����𖳌����B
				m_isEnable = false;

				//�T�u�N���X�̉���B
				SubRelease();
			}

			/**
			 * @brief �e�J�����̉���֐��B
			*/
			virtual void SubRelease() {}

			/**
			 * @brief �J�����̐؂�ւ����\���H
			 * @return ���������H
			*/
			virtual const bool CanSwitch() {

				return true;
			}
		protected:
			/**
			 * @brief �h���N���X��Start()�֐��B
			 * @return ���������H
			*/
			virtual bool StartSub() = 0;

			/**
			 * @brief �h���N���X��Update()�֐��B
			*/
			virtual void UpdateSub() = 0;
		protected:
			CVector3 m_position;		//���_
			CVector3 m_target;			//�����_
			static CVector3 m_cameraToPlayerVec;	//�J��������v���C���[�ɐL�т�x�N�g��
			bool m_isEnable = false;	//�L�����ǂ���
		};
	}
}

