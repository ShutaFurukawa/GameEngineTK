//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include <Mouse.h>

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;


Game::Game() :
    m_window(0),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_window = window;
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateDevice();

    CreateResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	//�������͂���
	//�L�[�{�[�h�̏�����
	keyboard = std::make_unique<Keyboard>();

	//�J�����̐���
	m_FollowCamera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);
	m_FollowCamera->SetKeyBoard(keyboard.get());

	//3D�I�u�W�F�N�g�̐ÓI�����o��������
	Obje3D::InitializeState(m_d3dDevice,m_d3dContext, m_FollowCamera.get());

	//m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(m_d3dContext.Get());
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionNormal>>(m_d3dContext.Get());

	m_effect = std::make_unique<BasicEffect>(m_d3dDevice.Get());

	//�v���W�F�N�V�����s��,�r���[�s��
	m_view = Matrix::CreateLookAt(Vector3(2.f, 2.f, 2.f),Vector3::Zero, Vector3::UnitY);
	//���ߖ@�����������ˉe�s��
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,float(m_outputWidth) / float(m_outputHeight), 0.1f, 500.f);

	//�G�t�F�N�g�ɍs����Z�b�g
	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);

	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	//�f�o�b�O�J�����̐���
	m_debugCamera = std::make_unique<DebugCamera>(m_outputWidth, m_outputHeight);

	//�G�t�F�N�g�t�@�N�g������
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	//�e�N�X�`���̓ǂݍ��݃p�X�w��
	m_factory->SetDirectory(L"Resources");
	//���f���̓ǂݍ��݂Ɛ���
	m_modelGround = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\glound200M.cmo", *m_factory);
	m_modelSky = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\SkyDoom.cmo", *m_factory);
	//m_modelSky2 = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\Sky2.cmo", *m_factory);
	//m_modelteaput = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\taeput.cmo", *m_factory);
	//m_head = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\head.cmo", *m_factory);
}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	//�X�V�����͂���
	m_debugCamera->Update();

	//�L�[�{�[�h�̏�Ԃ��擾
	Keyboard::State key = keyboard->GetState();

	//�r���[�s����擾
	//m_view = m_debugCamera->GetCameraMatrix();

	////�ǂ����猩��̂��i���_�j
	//Vector3 eyePos(0, 0, 5.0f);
	////�ǂ�������̂�(�����_)
	//Vector3 refPos(0, 0, 0);
	////�ǂ��炪��ʏ�������i������x�N�g���j
	//static float angle = 0.0f;
	//angle += 0.01f;
	//Vector3 upVec(cosf(angle), sinf(angle), 0);
	//upVec.Normalize();		//�x�N�g���̐��K��

	////�r���[�s������֐�
	//m_view = Matrix::CreateLookAt(eyePos, refPos, upVec);

	////�f��͈͂����߂��I
	////������������p
	//float fovY = XMConvertToRadians(60.0f);
	////�A�X�y�N�g��(���E�c�̔䗦)
	//float aspect = (float)m_outputWidth / m_outputHeight;
	////��O�̕\�����E
	//float nearClip = 0.1f;
	////���̕\�����E
	//float farClip = 1000.0f;

	////�ˉe�s������֐�
	//m_proj = Matrix::CreatePerspectiveFieldOfView(fovY, aspect, nearClip, farClip);

	
	////��]
	//m_rotmat += 0.025f;
	//m_rotmaty += 1.0f;

	////sinf�ɂ��X�P�[���̕ύX
	//val = sinf(m_rotmat / 2) + 1.0f;

	////�e�B�[�|�b�g�̍s��̐ݒ�
	////���s�ړ�
	//Matrix transmatTae[20];
	////�X�P�[��
	//Matrix scalemat = Matrix::CreateScale(val + 0.25f);
	////��]
	//Matrix rotx = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
	//Matrix roty = Matrix::CreateRotationY(XMConvertToRadians(m_rotmaty));
	//Matrix rotz = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
	////��]�̍���
	//Matrix rot;
	//rot = rotx * roty * rotz;


	////���̃��[���h�s��쐬
	////�X�P�[��
	//Matrix scalemat1 = Matrix::CreateScale(1.0f);
	//Matrix scalemat2 = Matrix::CreateScale(0.5f);
	//Matrix scalemat3 = Matrix::CreateScale(2.5f);

	////��]
	////�s�b�`
	//Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
	////���[��
	//Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
	////���[
	//Matrix rotmaty1[10];
	//Matrix rotmaty2[10];
	//Matrix rotmaty3;
	//Matrix rotmaty0;

	////��]�̍���
	//Matrix rot1[10];
	//Matrix rot2[10];
	//Matrix rot3;
	//Matrix rot0;

	//rotmaty3 = Matrix::CreateRotationY(XMConvertToRadians(m_rotmaty));
	//rot3 = rotmatx * rotmaty3 * rotmatz;
	//rotmaty0 = Matrix::CreateRotationY(XMConvertToRadians(0.0f));
	//rot0 = rotmatx * rotmaty0 * rotmatz;

	////�z��
	//for (int i = 0; i < 10; i++)
	//{
	//	rotmaty1[i] = Matrix::CreateRotationY(XMConvertToRadians(36.0f * i) + m_rotmat);
	//	rot1[i]= rotmatx * rotmaty1[i] * rotmatz;
	//	rotmaty2[i] = Matrix::CreateRotationY(XMConvertToRadians(36.0f * i) - m_rotmat);
	//	rot2[i] = rotmatx * rotmaty2[i] * rotmatz;

	//}

	////���s�ړ�
	//Matrix transmat[21];

	//transmat[20] = Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
	//m_worldBall[20] = scalemat3 * transmat[20] * rot3;

	//for (int i = 0; i < 10; i++)
	//{
	//	//���s�ړ��̍s��
	//	transmat[i] = Matrix::CreateTranslation(15.0f, 0.0f, 0.0f);
	//	transmat[10 + i] = Matrix::CreateTranslation(30.0f, 0.0f, 0.0f);

	//	//���[���h�s��̍���
	//	m_worldBall[i] = scalemat2 * transmat[i] * rot1[i];
	//	m_worldBall[10 + i] = scalemat1 * transmat[10 + i] * rot2[i];
	//}


	////�e�B�[�|�b�g�̃��[���h�s��
	//for (int i = 0; i < 20; i++)
	//{
	//	//���_�ֈړ�
	//	//if()

	//	//�e�v�f���s��֕ϊ�
	//	transmatTae[i] = Matrix::CreateTranslation(m_trancex[i] * m_trance[i], 0.0f, m_trancez[i] * m_trance[i]);
	//	m_wordTae[i] = scalemat * rot * transmatTae[i];
	//}

	//�v�L�[��������Ă�����
	if (key.W)
	{
		//�ړ��ʂ̃x�N�g��
		Vector3 moveV(0, 0, -0.1f);
		//���@�̊p�x���x�N�g������]
		moveV = Vector3::TransformNormal(moveV, m_tankWolrd);
		//���@�̍��W���ړ�
		tank_pos += moveV;
	}
	else if (key.S)
	{
		//�ړ��ʂ̃x�N�g��
		Vector3 moveV(0, 0, 0.1f);
		//���@�̊p�x���x�N�g������]
		Matrix rotmat = Matrix::CreateRotationY(m_rotVal);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//���@�̍��W���ړ�
		tank_pos += moveV;
	}

	//���@����]������
	if (key.A)
	{
		//���@�̉�]�ʂ̐ݒ�
		m_rotVal += 0.05f;
	}
	//���@����]������
	else if (key.D)
	{
		//���@�̉�]�ʂ̐ݒ�
		m_rotVal += -0.05f;
	}

	//����ƃ}�b�g
	//���@�̃��[���h�s����v�Z
	//�e�p�[�c
	Matrix transemat = Matrix::CreateTranslation(tank_pos);
	Matrix rotaitemat = Matrix::CreateRotationY(m_rotVal);
	m_tankWolrd = rotaitemat * transemat;
	//�q�p�[�c
	Matrix transemat2 = Matrix::CreateTranslation(Vector3(0, 0.5f, 0));
	Matrix rotaitemat2 = Matrix::CreateRotationY(0);
	//�����̕ό`���v�Z������e�Ƃ̌v�Z���s��
	m_tankWolrd2 = rotaitemat2 * transemat2 * m_tankWolrd;

	//�s��ݒ�
	m_FollowCamera->SetTargetPos(tank_pos);
	m_FollowCamera->SetTargetAngle(m_rotVal);

	//�r���[�s��A�ˉe�s����쐬
	m_FollowCamera->update();
	m_view = m_FollowCamera->GetViewMatrix();
	m_proj = m_FollowCamera->GetProjMatrix();
}

// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	// TODO: Add your rendering code here.

	//�`��͂���

	////���
	DirectX::CommonStates m_states(m_d3dDevice.Get());

	//���f���̕`��
	//for (int i = 0; i < 20; i++)
	//{
	//	m_modelteaput->Draw(m_d3dContext.Get(), m_states, m_wordTae[i], m_view, m_proj);
	//}

	m_modelGround->Draw(m_d3dContext.Get(), m_states, m_world, m_view, m_proj);

	m_modelSky->Draw(m_d3dContext.Get(), m_states, m_world, m_view, m_proj);

	////���p�[�c�̕`��
	//m_head->Draw(m_d3dContext.Get(), m_states, m_tankWolrd, m_view, m_proj);
	////���p�[�c�Q�̕`��
	//m_head->Draw(m_d3dContext.Get(), m_states, m_tankWolrd2, m_view, m_proj);
	m_ObjePlayer1.Draw();

	//for (int i = 0; i < 10; i++)
	//{
	//	//�����f���̕`��
	//	m_modelSky2->Draw(m_d3dContext.Get(), m_states, m_worldBall[i], m_view, m_proj);
	//	m_modelSky2->Draw(m_d3dContext.Get(), m_states, m_worldBall[10 + i], m_view, m_proj);
	//}
	//m_modelSky2->Draw(m_d3dContext.Get(), m_states, m_worldBall[20], m_view, m_proj);



	//m_d3dContext->OMSetBlendState(m_states.Opaque(), nullptr, 0xFFFFFFFF);
	//m_d3dContext->OMSetDepthStencilState(m_states.DepthNone(), 0);
	////�J�����O��ݒ肷��
	//m_d3dContext->RSSetState(m_states.Wireframe());

	////�s����Z�b�g
	//m_effect->SetWorld(m_world);
	//m_effect->SetView(m_view);
	//m_effect->SetProjection(m_proj);


	//m_effect->Apply(m_d3dContext.Get());
	//m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	////���_�f�[�^
	//uint16_t indices[] =
	//{
	//	0,1,2,
	//	2,1,3,
	//};

	//VertexPositionNormal vertices[] =
	//{
	//	{ Vector3(-1.0f,+1.0f,0.0f),Vector3(0.0f,0.0f,+1.0f) },
	//	{ Vector3(-1.0f,-1.0f,0.0f),Vector3(0.0f,0.0f,+1.0f) },
	//	{ Vector3(+1.0f,+1.0f,0.0f),Vector3(0.0f,0.0f,+1.0f) },
	//	{ Vector3(+1.0f,-1.0f,0.0f),Vector3(0.0f,0.0f,+1.0f) },

	//};



	//m_batch->Begin();

	//���̕`��
	//m_batch->DrawLine(VertexPositionColor(SimpleMath::Vector3(0, 0, 0), SimpleMath::Color(1, 1, 1)), VertexPositionColor(SimpleMath::Vector3(800, 600, 0), SimpleMath::Color(1, 1, 1)));

	////�R�c�̎O�p�`
	//VertexPositionColor v1(Vector3(0.f, 0.5f, 0.5f), Colors::Yellow);
	//VertexPositionColor v2(Vector3(0.5f, -0.5f, 0.5f), Colors::Yellow);
	//VertexPositionColor v3(Vector3(-0.5f, -0.5f, 0.5f), Colors::Yellow);

	////�Q�c�̎O�p�`
	//VertexPositionColor v1(Vector3(0.f, 500.f, 0.f), Colors::Yellow);
	//VertexPositionColor v2(Vector3(500.f, 0.f, 0.f), Colors::Yellow);
	//VertexPositionColor v3(Vector3(0.f, 0.f, 0.f), Colors::Yellow);

	//m_batch->DrawTriangle(v1, v2, v3);

	////�l�p�`
	//m_batch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indices, 6, vertices, 4);

	//m_batch->End();

    Present();

}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it.
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}