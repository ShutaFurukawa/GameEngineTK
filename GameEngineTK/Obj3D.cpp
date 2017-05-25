#include "Obj3d.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̎���
// �f�o�C�X
Microsoft::WRL::ComPtr<ID3D11Device>            Obje3D::m_d3dDevice;
// �f�o�C�X�R���e�L�X�g
Microsoft::WRL::ComPtr<ID3D11DeviceContext>     Obje3D::m_d3dContext;
// �J����
Camera* Obje3D::m_Camera;
// �ėp�`��X�e�[�g
std::unique_ptr<DirectX::CommonStates> Obje3D::m_state;
// �G�t�F�N�g�t�@�N�g��
std::unique_ptr<DirectX::EffectFactory> Obje3D::m_factory;

void Obje3D::InitializeState(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	// �ėp�`��X�e�[�g����
	m_state = std::make_unique<CommonStates>(m_d3dDevice.Get());

	// �G�t�F�N�g�t�@�N�g������
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	// �e�N�X�`���̓ǂݍ��݃p�X�w��
	m_factory->SetDirectory(L"Resources");
}

Obje3D::Obje3D()
{
	//�X�P�[���͂P�{���f�t�H
	m_scale = Vector3(1, 1, 1);
	m_parent = nullptr;
}

void Obje3D::LoadModel(const wchar_t * fileName)
{
	//static�֐��͒ʏ�̃����o�ϐ���static�ϐ����g����
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

void Obje3D::Update()
{
	//�s��̌v�Z
	//�X�P�[���s��
	Matrix scalemat = Matrix::CreateScale(m_scale);
	//��]�s��
	Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
	Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
	Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
	Matrix rotmat = rotmatZ * rotmatX * rotmatY;
	//���s�s��
	Matrix transemat = Matrix::CreateTranslation(m_translation);
	//���[���h�s�������
	m_world = scalemat * rotmat * transemat;
	//�e�����Ȃ����f���̌v�Z�̂��ߕ���
	if (m_parent)
	{
		//���̗p�ɐe�̍s�������
		m_world *= m_parent->m_world;
	}

}

void Obje3D::Draw()
{
	//�J������null�������狭���I��
	//�������U�Ȃ狭���I��
	assert(m_Camera);

	//null�̏ꍇ�͕\�����Ȃ�
	if (m_model)
	{
		//3D���f���̕`��
		m_model->Draw(m_d3dContext.Get(), *m_state, m_world, m_Camera->GetViewMatrix(), m_Camera->GetProjMatrix());
	}
}
