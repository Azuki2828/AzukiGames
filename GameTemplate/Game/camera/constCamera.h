#pragma once

namespace nsMyGame {

	namespace nsCamera {

		const CVector3 c_defaultCameraVec = { 0.0f,150.0f,200.0f };
		constexpr float c_addCameraTarget = 80.0f;			//�J�����̒����_�����߂�l
		constexpr float c_cameraFar = 80000.0f;				//�J�����̉�����
		constexpr float c_cameraCollisionRadius = 5.0f;	//�R���W�����̔��a
	}
}