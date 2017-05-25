//
// Game.h
//

#pragma once

#include "DebugCamera.h"

#include "StepTimer.h"
#include <VertexTypes.h>
#include <PrimitiveBatch.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <vector>

#include <Model.h>
#include <Keyboard.h>

#include "FollowCamerah.h"
#include "Obj3D.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	//ここから追加
	//std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//行列
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	//キーボード情報
	std::unique_ptr<DirectX::Keyboard> keyboard;

	//エフェクトファクトリの作成
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	//モデルの作成
	std::unique_ptr<DirectX::Model> m_modelGround;
	std::unique_ptr<DirectX::Model> m_modelSky;
	//std::unique_ptr<DirectX::Model> m_modelSky2;
	//std::unique_ptr<DirectX::Model> m_modelteaput;

	//球ワールド行列
	DirectX::SimpleMath::Matrix m_worldBall[21];
	//ティーワールド行列
	DirectX::SimpleMath::Matrix m_wordTae[20];

	//std::unique_ptr<DirectX::SpriteFont> m_font;

	DirectX::SimpleMath::Vector2 m_fontPos;
	//std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//回転量
	float m_rotmat = 0.0f;
	float m_rotmaty = 0.0f;

	//移動量
	float m_trance[20];
	float m_trancex[20];
	float m_trancez[20];

	//スケール
	float val;

	//原点位置
	DirectX::SimpleMath::Vector3 m_origin;

	//原点への移動変数
	float m_toOriginX[20];
	float m_toOroginZ[20];

	//カメラ
	std::unique_ptr<FollowCamera> m_FollowCamera;

	//自機のワールド行列
	DirectX::SimpleMath::Matrix m_tankWolrd;
	//自機のワールド行列2
	DirectX::SimpleMath::Matrix m_tankWolrd2;
	//自機の座標
	DirectX::SimpleMath::Vector3 tank_pos;
	//回転量
	float m_rotVal = 0.0f;

	Obje3D m_ObjePlayer1;
	Obje3D m_ObjePlayer2;

	//カメラ切り替えよう

};