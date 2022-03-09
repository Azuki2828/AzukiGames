#pragma once

namespace nsMyGame {

	namespace nsItem {

		constexpr float c_needToDistanceForGetItem = 100.0f;							//�A�C�e�����������̂ɕK�v�ȋ���
		constexpr const char16_t* c_itemEffectFilePath = u"Assets/effect/item.efk";		//�A�C�e���G�t�F�N�g�̃t�@�C���p�X
		const CVector3 c_itemEffectSize = { 10.0f,10.0f,10.0f };						//�A�C�e���G�t�F�N�g�̊g�嗦
		constexpr float c_itemEffectReplayTime = 1.0f;									//�G�t�F�N�g���Đ�������Ԋu
	}
}