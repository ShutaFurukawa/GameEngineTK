/// <summary>
/// 3Dオブジェクトのクラス
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
	//静的メンバを初期化する関数
	static void InitializeState(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera* camera);

private:
	//静的メンバ
	//3Dモデル
	std::unique_ptr<DirectX::Model> m_model;
	//スケーリング
	DirectX::SimpleMath::Vector3	m_scale;
	//回転角
	DirectX::SimpleMath::Vector3	m_rotation;
	//平行移動
	DirectX::SimpleMath::Vector3	m_translation;
	//ワールド行列
	DirectX::SimpleMath::Matrix		m_world;

	//親の3Dオブジェクトクラスのポインタ
	Obje3D* m_parent;

	//デバイス
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	//デバイスコンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
	//カメラ
	static Camera* m_Camera;

	//エフェクトファクトリの作成
	static std::unique_ptr<DirectX::EffectFactory> m_factory;
	//汎用描画ステート
	static std::unique_ptr<DirectX::CommonStates> m_state;

public:
	//コンストラクタ
	Obje3D();

	//モデルをロード
	void LoadModel(const wchar_t* fileName);

	//更新
	void Update();

	//描画
	void Draw();

	//setter
	//スケーリング
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	//回転角
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation; }
	//平行移動
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation) { m_translation = translation; }
	//親の3Dオブジェクトのポインタ
	void SetParent(Obje3D* parent) { m_parent = parent; }

	//getter
	//スケーリング
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	//回転角
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	//平行移動
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }
	//ワールド行列
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }
	//親の3Dオブジェクトのポインタ
	Obje3D* GetParent() { return m_parent; }
};