//*--------------------------------------------------------------*//
//= @file   ���O
//=
//= @brief  �T�v ���@��Ǐ]����J�����𐧌䂷��N���X
//=
//= @date   ���t
//=
//= @author �����	ShutaFurukawa
//*--------------------------------------------------------------*//

#pragma once

#include "Camera.h"
#include <Keyboard.h>

class FollowCamera : public Camera
{
private:
	//�Ǐ]�Ώۂ̍��W
	DirectX::SimpleMath::Vector3 m_target_pos;
	//�Ǐ]���W�̉�]�p
	float m_target_amgle;
	//�L�[�{�[�h
	DirectX::Keyboard* m_keyboard;
	//�L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;
	//�J�����؂�ւ��̃t���O
	bool chengeFlag;
	
public:
	//�Ǐ]�ΏۂƃJ�����̋���
	static const float CAMERA_DISTANCE;
	//�R���X�g���N�^
	FollowCamera(int width, int hight);

	//���t���[���X�V
	void update() override;
	//�Ǐ]�Ώۂ̍��W���Z�b�g����֐�
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);
	//�Ǐ]�Ώۂ̉�]�p���Z�b�g����֐�
	void SetTargetAngle(float targetangle);
	//�L�[�{�[�h���Z�b�g
	void SetKeyBoard(DirectX::Keyboard* keyboard);

};