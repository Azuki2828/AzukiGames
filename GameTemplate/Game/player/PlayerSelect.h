#pragma once
#include "constPlayer.h"

namespace nsMyGame {

	//�v���C���[�̑I����ԃN���X
	class CPlayerSelect
	{
	public:
		/**
		 * @brief �I�u�W�F�N�g��I����Ԃɂ���֐��B
		 * @param selectObj �I�u�W�F�N�g
		*/
		void SetSelectObject(CIGameObject* selectObj, const CVector3& playerPos);

		/**
		 * @brief ���ݑI�𒆂̃I�u�W�F�N�g�ƃv���C���[�Ƃ̋������擾����֐��B
		 * @return ���ݑI�𒆂̃I�u�W�F�N�g�ƃv���C���[�Ƃ̋���
		*/
		const float GetSelectObjectLengthToPlayer(const CVector3& playerPos);

		/**
		 * @brief ���ݑI�𒆂̃I�u�W�F�N�g���X�V����֐��B
		*/
		void UpdateCarentSelectObject(const CVector3& playerPos);
	private:
		CIGameObject* m_selectObject = nullptr;				//�I����Ԃ̃I�u�W�F�N�g
	};
}

