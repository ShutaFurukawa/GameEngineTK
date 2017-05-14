//*--------------------------------------------------------------*//
//= @file   ���O
//=
//= @brief  �T�v �J�����𐧌䂷��N���X
//=
//= @date   ���t
//=
//= @author �����	ShutaFurukawa
//*--------------------------------------------------------------*//

#include "Game.h"
#include "pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�R���X�g���N�^---------------------------------------------------------------
Camera::Camera(int width, int hight)
{
	//�����o�ϐ��̏�����
	//�r���[�s��
	//�ǂ����猩��̂��i���_�j
	m_eyePos = Vector3(0, 0, 5.0f);
	//�ǂ�������̂�(�����_)
	m_refPos = Vector3(0, 0, -0.5f);
	//�ǂ��炪��ʏ�������i������x�N�g���j
	m_upVec = Vector3(cosf(m_angle), sinf(m_angle), 0);

	m_angle = 0.0f;

	//�ˉe�s��
	//������������p
	m_fovY = XMConvertToRadians(60.0f);
	//�A�X�y�N�g��(���E�c�̔䗦)
	m_aspect = (float)width / hight;
	//��O�̕\�����E
	m_nearClip = 0.1f;
	//���̕\�����E
	m_farClip = 1000.0f;

	//�r���[�s��̐���
	m_view = Matrix::CreateLookAt(m_eyePos, m_refPos, m_upVec);

	//�ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

//�R���X�g���N�^---------------------------------------------------------------
Camera::Camera()
{

}

//�f�X�g���N�^------------------------------------------------------------------
Camera::~Camera()
{

}

//�X�V�֐�----------------------------------------------------------------------
void Camera::update()
{
	//�r���[�s��̐���
	m_view = Matrix::CreateLookAt(m_eyePos, m_refPos, m_upVec);

	//�ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);

}

//�r���[�s��擾�֐�------------------------------------------------------------
Matrix Camera::GetViewMatrix()
{
	return m_view;
}

//�ˉe�s��擾�֐�--------------------------------------------------------------
Matrix Camera::GetProjMatrix()
{
	return m_proj;
}

//���_�̃Z�b�g�֐�--------------------------------------------------------------
void Camera::SetEyePos(Vector3 eyepos)
{
	m_eyePos = eyepos;
}

//�����_�̃Z�b�g�֐�------------------------------------------------------------
void Camera::SetRefPos(Vector3 refpos)
{
	m_refPos = refpos;
}

//������x�N�g���̃Z�b�g�֐�----------------------------------------------------
void Camera::SetUpVec(Vector3 uppos)
{
	m_upVec = uppos;
}

//������������p�̃Z�b�g�֐�----------------------------------------------------
void Camera::SetFovY(float fovy)
{
	m_fovY = fovy;
}

//�A�X�y�N�g��̃Z�b�g�֐�------------------------------------------------------
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

//��O�\�����E�̃Z�b�g�֐�------------------------------------------------------
void Camera::SetNearClip(float nearclip)
{
	m_nearClip = nearclip;
}

//���\�����E�̃Z�b�g�֐�--------------------------------------------------------
void Camera::SetFarClip(float farclip)
{
	m_farClip = farclip;
}