#include "Obj3d.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的メンバ変数の実体
// デバイス
Microsoft::WRL::ComPtr<ID3D11Device>            Obje3D::m_d3dDevice;
// デバイスコンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext>     Obje3D::m_d3dContext;
// カメラ
Camera* Obje3D::m_Camera;
// 汎用描画ステート
std::unique_ptr<DirectX::CommonStates> Obje3D::m_state;
// エフェクトファクトリ
std::unique_ptr<DirectX::EffectFactory> Obje3D::m_factory;

void Obje3D::InitializeState(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	// 汎用描画ステート生成
	m_state = std::make_unique<CommonStates>(m_d3dDevice.Get());

	// エフェクトファクトリ生成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	// テクスチャの読み込みパス指定
	m_factory->SetDirectory(L"Resources");
}

Obje3D::Obje3D()
{
	//スケールは１倍がデフォ
	m_scale = Vector3(1, 1, 1);
	m_parent = nullptr;
}

void Obje3D::LoadModel(const wchar_t * fileName)
{
	//static関数は通常のメンバ変数とstatic変数が使える
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

void Obje3D::Update()
{
	//行列の計算
	//スケール行列
	Matrix scalemat = Matrix::CreateScale(m_scale);
	//回転行列
	Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
	Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
	Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
	Matrix rotmat = rotmatZ * rotmatX * rotmatY;
	//平行行列
	Matrix transemat = Matrix::CreateTranslation(m_translation);
	//ワールド行列を合成
	m_world = scalemat * rotmat * transemat;
	//親がいないモデルの計算のため分割
	if (m_parent)
	{
		//合体用に親の行列も合成
		m_world *= m_parent->m_world;
	}

}

void Obje3D::Draw()
{
	//カメラがnullだったら強制終了
	//条件が偽なら強制終了
	assert(m_Camera);

	//nullの場合は表示しない
	if (m_model)
	{
		//3Dモデルの描画
		m_model->Draw(m_d3dContext.Get(), *m_state, m_world, m_Camera->GetViewMatrix(), m_Camera->GetProjMatrix());
	}
}
