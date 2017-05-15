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
}

//�X�V�֐�
void FollowCamera::update()
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

	this->SetEyePos(eyePos);
	this->SetRefPos(refPos);

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

