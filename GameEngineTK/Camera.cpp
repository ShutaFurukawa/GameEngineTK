//*--------------------------------------------------------------*//
//= @file   名前
//=
//= @brief  概要 カメラを制御するクラス
//=
//= @date   日付
//=
//= @author 制作者	ShutaFurukawa
//*--------------------------------------------------------------*//

#include "Game.h"
#include "pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//コンストラクタ---------------------------------------------------------------
Camera::Camera(int width, int hight)
{
	//メンバ変数の初期化
	//ビュー行列
	//どこから見るのか（視点）
	m_eyePos = Vector3(0, 0, 5.0f);
	//どこを見るのか(注視点)
	m_refPos = Vector3(0, 0, -0.5f);
	//どちらが画面上方向か（上方向ベクトル）
	m_upVec = Vector3(cosf(m_angle), sinf(m_angle), 0);

	m_angle = 0.0f;

	//射影行列
	//垂直方向視野角
	m_fovY = XMConvertToRadians(60.0f);
	//アスペクト比(横・縦の比率)
	m_aspect = (float)width / hight;
	//手前の表示限界
	m_nearClip = 0.1f;
	//奥の表示限界
	m_farClip = 1000.0f;

	//ビュー行列の生成
	m_view = Matrix::CreateLookAt(m_eyePos, m_refPos, m_upVec);

	//射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

//コンストラクタ---------------------------------------------------------------
Camera::Camera()
{

}

//デストラクタ------------------------------------------------------------------
Camera::~Camera()
{

}

//更新関数----------------------------------------------------------------------
void Camera::update()
{
	//ビュー行列の生成
	m_view = Matrix::CreateLookAt(m_eyePos, m_refPos, m_upVec);

	//射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);

}

//ビュー行列取得関数------------------------------------------------------------
Matrix Camera::GetViewMatrix()
{
	return m_view;
}

//射影行列取得関数--------------------------------------------------------------
Matrix Camera::GetProjMatrix()
{
	return m_proj;
}

//視点のセット関数--------------------------------------------------------------
void Camera::SetEyePos(Vector3 eyepos)
{
	m_eyePos = eyepos;
}

//注視点のセット関数------------------------------------------------------------
void Camera::SetRefPos(Vector3 refpos)
{
	m_refPos = refpos;
}

//上方向ベクトルのセット関数----------------------------------------------------
void Camera::SetUpVec(Vector3 uppos)
{
	m_upVec = uppos;
}

//垂直方向視野角のセット関数----------------------------------------------------
void Camera::SetFovY(float fovy)
{
	m_fovY = fovy;
}

//アスペクト比のセット関数------------------------------------------------------
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

//手前表示限界のセット関数------------------------------------------------------
void Camera::SetNearClip(float nearclip)
{
	m_nearClip = nearclip;
}

//奥表示限界のセット関数--------------------------------------------------------
void Camera::SetFarClip(float farclip)
{
	m_farClip = farclip;
}