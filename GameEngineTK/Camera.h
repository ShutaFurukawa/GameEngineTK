//*--------------------------------------------------------------*//
//= @file   ���O
//=
//= @brief  �T�v �J�����𐧌䂷��N���X
//=
//= @date   ���t
//=
//= @author �����	ShutaFurukawa
//*--------------------------------------------------------------*//

//���d�C���N���[�h�h�~
#pragma once

#include <SimpleMath.h>

class Camera
{
	//������J�����o
protected:
	//�r���[�s��
	//�ǂ����猩��̂��i���_�j
	DirectX::SimpleMath::Vector3 m_eyePos;
	//�ǂ�������̂�(�����_)
	DirectX::SimpleMath::Vector3 m_refPos;
	//�ǂ��炪��ʏ�������i������x�N�g���j
	DirectX::SimpleMath::Vector3 m_upVec;

	static float m_angle;


	//�ˉe�s��
	//������������p
	float m_fovY;
	//�A�X�y�N�g��(���E�c�̔䗦)
	float m_aspect;
	//��O�̕\�����E
	float m_nearClip = 0.1f;
	//���̕\�����E
	float m_farClip = 1000.0f;

	//�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	//�ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;

	//���J�����o
public:
	//�R���X�g���N�^
	Camera(int width, int hight);
	Camera();
	//���z�f�X�g���N�^
	virtual ~Camera();

	//�X�V�֐�
	void update();

	//�r���[�s����擾
	DirectX::SimpleMath::Matrix GetViewMatrix();

	//�ˉe�s����擾
	DirectX::SimpleMath::Matrix GetProjMatrix();

	//���_���Z�b�g����֐�
	void SetEyePos(DirectX::SimpleMath::Vector3 eyepos);
	//�����_���Z�b�g����֐�
	void SetRefPos(DirectX::SimpleMath::Vector3 refpos);
	//������x�N�g�����Z�b�g����֐�
	void SetUpVec(DirectX::SimpleMath::Vector3 uppos);
	//������������p���Z�b�g����֐�
	void SetFovY(float fovy);
	//�A�X�y�N�g����Z�b�g����֐�
	void SetAspect(float aspect);
	//��O�̕\�����E���Z�b�g����֐�
	void SetNearClip(float neraclip);
	//���̕\�����E���Z�b�g����֐�
	void SetFarClip(float farclip);
};