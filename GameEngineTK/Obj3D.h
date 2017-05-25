/// <summary>
/// 3D�I�u�W�F�N�g�̃N���X
/// </summary>
#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>

#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>

#include <Model.h>

#include "Camera.h"

class Obje3D
{
public:
	//�ÓI�����o������������֐�
	static void InitializeState(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera* camera);

private:
	//�ÓI�����o
	//3D���f��
	std::unique_ptr<DirectX::Model> m_model;
	//�X�P�[�����O
	DirectX::SimpleMath::Vector3	m_scale;
	//��]�p
	DirectX::SimpleMath::Vector3	m_rotation;
	//���s�ړ�
	DirectX::SimpleMath::Vector3	m_translation;
	//���[���h�s��
	DirectX::SimpleMath::Matrix		m_world;

	//�e��3D�I�u�W�F�N�g�N���X�̃|�C���^
	Obje3D* m_parent;

	//�f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	//�f�o�C�X�R���e�L�X�g
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
	//�J����
	static Camera* m_Camera;

	//�G�t�F�N�g�t�@�N�g���̍쐬
	static std::unique_ptr<DirectX::EffectFactory> m_factory;
	//�ėp�`��X�e�[�g
	static std::unique_ptr<DirectX::CommonStates> m_state;

public:
	//�R���X�g���N�^
	Obje3D();

	//���f�������[�h
	void LoadModel(const wchar_t* fileName);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//setter
	//�X�P�[�����O
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	//��]�p
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation; }
	//���s�ړ�
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation) { m_translation = translation; }
	//�e��3D�I�u�W�F�N�g�̃|�C���^
	void SetParent(Obje3D* parent) { m_parent = parent; }

	//getter
	//�X�P�[�����O
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	//��]�p
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	//���s�ړ�
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }
	//���[���h�s��
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }
	//�e��3D�I�u�W�F�N�g�̃|�C���^
	Obje3D* GetParent() { return m_parent; }
};