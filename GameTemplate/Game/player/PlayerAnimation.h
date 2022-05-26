#pragma once
#include "constPlayer.h"

namespace nsMyGame {

	namespace nsPlayer {

		//�A�j���[�V�����̃��X�g
		enum EnAnimationList {
			enAnim_Idle,			//�ҋ@
			enAnim_Walk,			//���s
			enAnim_LeftWalk,		//�������s
			enAnim_RightWalk,		//�E�����s
			enAnim_Run,				//����
			enAnim_Attack,			//�U��
			enAnim_AttackBreak,		//�U���͂����ꂽ
			enAnim_Damage,			//��e
			enAnim_Rolling,			//���[�����O
			enAnim_Guard,			//�K�[�h
			enAnim_GuardSuccess,	//�K�[�h����
			enAnim_Death,			//���S

			enAnim_Num

		};

		//�㔼�g�H�����g�H
		enum EnBone {

			enUpperBody,	//�㔼�g
			enLowerBody,	//�����g

			enBodyNum
		};

		//�v���C���[�̃A�j���[�V�����������N���X
		class CPlayerAnimation
		{
		public:
			/**
			 * @brief �������֐��B
			*/
			void Init(CModelRender& modelRender);

			/**
			 * @brief �X�V�֐��B
			*/
			void Update(CModelRender& modelRender, const EnPlayerState& playerState);

			/**
			 * @brief �A�j���[�V�����N���b�v���擾����֐��B
			 * @return �A�j���[�V�����N���b�v
			*/
			//CAnimationClip* GetAnimationClip() {
			//
			//	return m_animationClip;
			//}

			/**
			 * @brief �A�j���[�V�����̐����擾����֐��B
			 * @return �A�j���[�V�����̐�
			*/
			const int GetAnimationNum()const {

				return enAnim_Num;
			}

			/**
			 * @brief ���̃t���[���͈ړ����Ă���Ɣ���B
			*/
			void Move() {

				m_isMove = true;
			}

		private:
			/**
			 * @brief �A�j���[�V�����N���b�v������������֐��B
			*/
			void InitAnimationClip();

		private:
			//�㔼�g�A�����g�̃{�[���̐�
			enum {
				c_upperBoneNum = 54,
				c_lowerBoneNum = 11
			};
			bool m_isMove = false;							//�����Ă��邩�ǂ���
			CAnimationClip m_animationClip[enBodyNum][enAnim_Num];		//�A�j���[�V�����N���b�v
			Animation m_animation[enBodyNum];				//�A�j���[�V����
			Skeleton m_skeleton[enBodyNum];					//�X�P���g��
			float m_animationSpeed = 2.0f;					//�A�j���[�V�����̍Đ����x

			//�㔼�g�̃{�[���̖��O�̃��X�g
			const char* m_upperBoneName[c_upperBoneNum] = {
				
				"mixamorig5:Spine",
				"mixamorig5:Spine1",
				"mixamorig5:Spine2",
				"mixamorig5:LeftShoulder",
				"mixamorig5:LeftArm",
				"mixamorig5:LeftForeArm",
				"mixamorig5:LeftHand",
				"mixamorig5:LeftHandIndex1",
				"mixamorig5:LeftHandIndex2",
				"mixamorig5:LeftHandIndex3",
				"mixamorig5:LeftHandIndex4",
				"mixamorig5:LeftHandMiddle1",
				"mixamorig5:LeftHandMiddle2",
				"mixamorig5:LeftHandMiddle3",
				"mixamorig5:LeftHandMiddle4",
				"mixamorig5:LeftHandPinky1",
				"mixamorig5:LeftHandPinky2",
				"mixamorig5:LeftHandPinky3",
				"mixamorig5:LeftHandPinky4",
				"mixamorig5:LeftHandRing1",
				"mixamorig5:LeftHandRing2",
				"mixamorig5:LeftHandRing3",
				"mixamorig5:LeftHandRing4",
				"mixamorig5:LeftHandThumb1",
				"mixamorig5:LeftHandThumb2",
				"mixamorig5:LeftHandThumb3",
				"mixamorig5:LeftHandThumb4",
				"mixamorig5:Neck",
				"mixamorig5:Head",
				"mixamorig5:HeadTop_End",
				"mixamorig5:RightShoulder",
				"mixamorig5:RightArm",
				"mixamorig5:RightForeArm",
				"mixamorig5:RightHand",
				"mixamorig5:RightHandIndex1",
				"mixamorig5:RightHandIndex2",
				"mixamorig5:RightHandIndex3",
				"mixamorig5:RightHandIndex4",
				"mixamorig5:RightHandMiddle1",
				"mixamorig5:RightHandMiddle2",
				"mixamorig5:RightHandMiddle3",
				"mixamorig5:RightHandMiddle4",
				"mixamorig5:RightHandPinky1",
				"mixamorig5:RightHandPinky2",
				"mixamorig5:RightHandPinky3",
				"mixamorig5:RightHandPinky4",
				"mixamorig5:RightHandRing1",
				"mixamorig5:RightHandRing2",
				"mixamorig5:RightHandRing3",
				"mixamorig5:RightHandRing4",
				"mixamorig5:RightHandThumb1",
				"mixamorig5:RightHandThumb2",
				"mixamorig5:RightHandThumb3",
				"mixamorig5:RightHandThumb4"
			};
			//�����g�̃{�[���̖��O�̃��X�g
			const char* m_lowerBoneName[c_lowerBoneNum] = {
				
				"mixamorig5:Hips",
				"mixamorig5:LeftUpLeg",
				"mixamorig5:LeftLeg",
				"mixamorig5:LeftFoot",
				"mixamorig5:LeftToeBase",
				"mixamorig5:LeftToe_End",
				"mixamorig5:RightUpLeg",
				"mixamorig5:RightLeg",
				"mixamorig5:RightFoot",
				"mixamorig5:RightToeBase",
				"mixamorig5:RightToe_End"
			};
		};
	}
}

