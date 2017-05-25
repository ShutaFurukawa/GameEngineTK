//*--------------------------------------------------------------*//
//= @file   ���O
//=
//= @brief  �T�v ���@��Ǐ]����J�����𐧌䂷��N���X
//=
//= @date   ���t
//=
//= @author �����	ShutaFurukawa
//*--------------------------------------------------------------*//
#include "Game.h"
#include "pch.h"
#include "FollowCamerah.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

//�R���X�g���N�^
FollowCamera::FollowCamera(int width, int hight)
			:Camera(width, hight)
{
	m_target_pos = Vector3::Zero;
	m_target_amgle = 0.0f;
	m_keyboard = nullptr;
	chengeFlag = false;
}

//�X�V�֐�
void FollowCamera::update()
{
	//�@�L�[�{�[�h�����@////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�L�[�{�[�h�̏�Ԏ擾
	Keyboard::State keyboardState = m_keyboard->GetState();
	m_keyboardTracker.Update(keyboardState);

	//�b���������Ƃ�TPS/FPS�؂�ւ�
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keys::C))
	{
		//�t���O�؂�ւ�
		chengeFlag = !chengeFlag;
	}

	//�t���O�ɂ����fps/tps�̐؂�ւ�
	if (chengeFlag)
	{

		//�@FPS���_�J�����@/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//eyePos�����Ɍv�Z����Ƃ����l��
		//���_�A�Q�Ɠ_
		Vector3 eyePos, refPos;
		//�t�@�b�H�I

		//���@�̖ڂ̈ʒu�����_�Ƃ��邽�߂̌v�Z
		Vector3 upPos;
		upPos = m_target_pos + Vector3(0, 0.2f, 0);
		//�Q�Ɠ_�Ǝ��_�̍����̃x�N�g��
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);

		//���@�̌��ɉ�荞�ނ��߂̍s��쐬
		Matrix rotmat_ = Matrix::CreateRotationY(m_target_amgle);
		//�����x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat_);
		eyePos = upPos + cameraV * 0.1f;

		//�Q�Ɠ_���W���v�Z
		refPos = upPos + cameraV;

		this->SetEyePos(eyePos);
		this->SetRefPos(refPos);

	}
	else
	{

		// ���@��Ǐ]����J���� //////////////////////////////////////////////////////////////////////////////////////////////////////

		//���_�A�Q�Ɠ_
		Vector3 eyePos, refPos;

		//���@�̏��Q�����Q�Ɠ_�Ƃ���
		refPos = m_target_pos + Vector3(0, 2, 0);
		//�Q�Ɠ_�Ǝ��_�̍����̃x�N�g��
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);

		//���@�̌��ɉ�荞�ނ��߂̍s��쐬
		Matrix rotmat_ = Matrix::CreateRotationY(m_target_amgle);
		//�����x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat_);

		//���_���W���v�Z
		eyePos = refPos + cameraV;

		//���ݒn�_����ڕW�n�_�܂Ő��`��Ԃ���
		//��Ԃ������W�����݂̍��W�{(�ڕW�̍��W�]���݂̍��W)����Ԃ̊���
		//(����̏ꍇ)
		//���݂̍��W���J�����̎��_���W
		//�ڕW�̍��W���Ǐ]���邽�߂̎��_���W
		//���_�����݈ʒu�����Ԃ���
		eyePos = m_eyePos + (eyePos - m_eyePos) * 0.1;
		//�Q�Ɠ_�����݈ʒu���炷��
		refPos = m_refPos + (refPos - m_refPos) * 0.5;

		this->SetEyePos(eyePos);
		this->SetRefPos(refPos);
	}


	//���N���X�̍X�V
	Camera::update();
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_target_pos = targetpos;
}

void FollowCamera::SetTargetAngle(float targetangle)
{
	m_target_amgle = targetangle;
}

void FollowCamera::SetKeyBoard(Keyboard* keyboard)
{
	m_keyboard = keyboard;
}
