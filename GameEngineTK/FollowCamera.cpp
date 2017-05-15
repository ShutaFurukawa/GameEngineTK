//*--------------------------------------------------------------*//
//= @file   名前
//=
//= @brief  概要 自機を追従するカメラを制御するクラス
//=
//= @date   日付
//=
//= @author 制作者	ShutaFurukawa
//*--------------------------------------------------------------*//
#include "Game.h"
#include "pch.h"
#include "FollowCamerah.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//静的メンバ変数の初期化
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

//コンストラクタ
FollowCamera::FollowCamera(int width, int hight)
			:Camera(width, hight)
{
	m_target_pos = Vector3::Zero;
	m_target_amgle = 0.0f;
}

//更新関数
void FollowCamera::update()
{
	// 自機を追従するカメラ //////////////////////////////////////////////////////////////////////////////////////////////////////

	//視点、参照点
	Vector3 eyePos, refPos;

	//自機の上空２ｍを参照点とする
	refPos = m_target_pos + Vector3(0, 2, 0);
	//参照点と視点の差分のベクトル
	Vector3 cameraV(0, 0, CAMERA_DISTANCE);

	//自機の後ろに回り込むための行列作成
	Matrix rotmat_ = Matrix::CreateRotationY(m_target_amgle);
	//差分ベクトルを回転させる
	cameraV = Vector3::TransformNormal(cameraV, rotmat_);

	//視点座標を計算
	eyePos = refPos + cameraV;

	this->SetEyePos(eyePos);
	this->SetRefPos(refPos);

	//基底クラスの更新
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

