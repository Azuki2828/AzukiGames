#pragma once
#include "PlayerAction.h"
#include "PlayerAnimation.h"
#include "PlayerSelect.h"

namespace nsMyGame {

	namespace nsPlayer {

		//�G�C���A�X�錾
		class CPlayerAnimation;

		//�v���C���[�N���X
		class CPlayer : public CIGameObject
		{
			//�X�e�[�^�X
			struct SStatus {
				int hp = 0;
				int attack = 0;
			};

			/**
			 * @brief ���C�g�J�������X�V����֐��B
			*/
			void LightCameraUpdate();

			/**
			 * @brief �ŏ��Ɉ�񂾂��Ă΂��֐��B
			 * @return ���������H
			*/
			bool Start()override final;

			/**
			 * @brief �폜�֐��B
			*/
			void OnDestroy()override final;

			/**
			 * @brief �X�V�֐��B
			*/
			void Update()override final;

			/**
			 * @brief �X�e�[�^�X������������֐��B
			*/
			void InitStatus() {

				m_status.hp = c_playerMaxHP;
				m_status.attack = 10;
			}

			/**
			 * @brief �v���C���[�̑O�������X�V����֐��B
			*/
			void UpdateForward();

			/**
			 * @brief �ʏ�̍X�V�����B
			*/
			void CommonStateProcess();

			/**
			 * @brief ���[�����O���̍X�V�����B
			*/
			void IsRollingStateProcess();

			/**
			 * @brief ����ł����Ԃ̍X�V�����B
			*/
			void IsDeathStateProcess();

			/**
			 * @brief ��e���̍X�V�����B
			*/
			void IsDamagedStateProcess();

			/**
			 * @brief �K�[�h���̍X�V�����B
			*/
			void IsGuardStateProcess();

			/**
			 * @brief �U�����̍X�V�����B
			*/
			void IsAttackStateProcess();
		public:

			/**
			 * @brief HP���擾����֐��B
			 * @return HP
			*/
			const int GetHP()const {

				return m_status.hp;
			}

			/**
			 * @brief �_���[�W���������֐��B
			*/
			void JudgeDamage(const CVector3& effectPos);

			/**
			 * @brief ����ł��邩�ǂ������肷��֐��B
			 * @return HP��0�ȉ��H
			*/
			const bool IsDeath()const {

				return m_status.hp <= 0;
			}

			/**
			 * @brief ���W���擾����֐��B
			 * @return ���W
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
			 * @brief �L�����N�^�[�R���g���[���[���擾����֐��B
			 * @return �L�����N�^�[�R���g���[���[
			*/
			CharacterController& GetCharacterController() {

				return m_playerAction.GetCharacterController();
			}

			/**
			 * @brief �_���[�W��Ԃɂ���֐��B
			*/
			void ReceiveDamage(const CVector3& effectPos) {

				//��e�B
				m_status.hp -= 30;

				//���񂾂Ȃ�
				if (m_status.hp <= 0) {

					//HP��0�ɐݒ�B
					m_status.hp = 0;

					//���S���̃{�C�X���Đ��B
					CSoundManager::GetInstance()->Play(enSE_DeathVoice);
				}

				//�_���[�W��ԂɁB
				m_playerAction.ReceiveDamage();
				m_playerState = enState_Damage;

				//�����Ԃ��G�t�F�N�g�̍��W���������B
				CVector3 effectPosition = m_position;
				effectPosition.y += 100.0f;

				//�����Ԃ��G�t�F�N�g���Đ��B
				Effect* bloodEffect = NewGO<Effect>(enPriority_Zeroth);
				bloodEffect->Init(c_bloodEffectFilePath);
				bloodEffect->SetPosition(effectPosition);
				bloodEffect->SetScale(c_bloodEffectSize);
				bloodEffect->Play();
			}

			/**
			 * @brief �U����e���ꂽ�Ƃ��ɌĂ΂��֐��B
			*/
			void AttackBreak() {

				m_playerState = enState_AttackBreak;
				m_playerAction.AttackBreak();
			}

			/**
			 * @brief �K�[�h���H
			 * @return �K�[�h���Ă��邩�ǂ����̃t���O
			*/
			bool IsGuard() {

				return m_playerAction.IsGuard();
			}

			/**
			 * @brief �����������Ă���H
			 * @return ���̏��������O���傫�����ǂ����̔���
			*/
			const bool HasKey()const {

				return m_hasKeyNum > 0;
			}

			/**
			 * @brief �����擾����֐��B
			*/
			void GetKey() {

				m_hasKeyNum++;
			}

			/**
			 * @brief ���������֐��B
			*/
			void ConsumeKey() {

				m_hasKeyNum--;
			}

			/**
			 * @brief ������I��ł��邩�ǂ����̃t���O��ݒ肷��֐��B
			 * @param selectFlag ������I��ł��邩�ǂ����̃t���O
			*/
			void SetSelectFlag(const bool selectFlag) {

				m_isSelect = selectFlag;
			}

			/**
			 * @brief ������I��ł����ԁH
			 * @return ������I��ł��邩�ǂ����̃t���O
			*/
			const bool IsSelect()const {

				return m_isSelect;
			}

			/**
			 * @brief �I�u�W�F�N�g��I����Ԃɂ���֐��B
			 * @param selectObj �I�u�W�F�N�g
			*/
			void SetSelectObject(CIGameObject* selectObj) {

				m_playerSelect.SetSelectObject(selectObj, m_position);
			}

		private:
			bool m_isSelect = false;							//������I��ł����ԁH�i�߂��̉����ɔ������Ă���H�j
			int m_hasKeyNum = 0;								//���̏�����
			SStatus m_status;									//�X�e�[�^�X
			CModelRender* m_modelRender = nullptr;				//���f��
			CPlayerAction m_playerAction;						//�v���C���[�A�N�V�����N���X
			CPlayerAnimation m_playerAnimation;					//�v���C���[�A�j���[�V�����N���X
			CPlayerSelect m_playerSelect;						//�v���C���[�̑I����ԃN���X
			CVector3 m_position = CVector3::Zero;				//���W
			CQuaternion m_rotation = CQuaternion::Identity;		//��]
			CVector3 m_forward = CVector3::Zero;				//�O����
			EnPlayerState m_playerState;						//�v���C���[�̃X�e�[�g
		};
	}
}

