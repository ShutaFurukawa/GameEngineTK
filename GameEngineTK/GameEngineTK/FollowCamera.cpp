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
	m_keyboard = nullptr;
	chengeFlag = false;
}

//更新関数
void FollowCamera::update()
{
	//　キーボード処理　////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//キーボードの状態取得
	Keyboard::State keyboardState = m_keyboard->GetState();
	m_keyboardTracker.Update(keyboardState);

	//Ｃを押すごとにTPS/FPS切り替え
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keys::C))
	{
		//フラグ切り替え
		chengeFlag = !chengeFlag;
	}

	//フラグによってfps/tpsの切り替え
	if (chengeFlag)
	{

		//　FPS視点カメラ　/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//eyePosから先に計算するという考え
		//視点、参照点
		Vector3 eyePos, refPos;
		//ファッ？！

		//自機の目の位置を視点とするための計算
		Vector3 upPos;
		upPos = m_target_pos + Vector3(0, 0.2f, 0);
		//参照点と視点の差分のベクトル
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);

		//自機の後ろに回り込むための行列作成
		Matrix rotmat_ = Matrix::CreateRotationY(m_target_amgle);
		//差分ベクトルを回転させる
		cameraV = Vector3::TransformNormal(cameraV, rotmat_);
		eyePos = upPos + cameraV * 0.1f;

		//参照点座標を計算
		refPos = upPos + cameraV;

		this->SetEyePos(eyePos);
		this->SetRefPos(refPos);

	}
	else
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

		//現在地点から目標地点まで線形補間する
		//補間した座標＝現在の座標＋(目標の座標‐現在の座標)＊補間の割合
		//(今回の場合)
		//現在の座標＝カメラの視点座標
		//目標の座標＝追従するための視点座標
		//視点を現在位置から補間する
		eyePos = m_eyePos + (eyePos - m_eyePos) * 0.1;
		//参照点を現在位置からする
		refPos = m_refPos + (refPos - m_refPos) * 0.5;

		this->SetEyePos(eyePos);
		this->SetRefPos(refPos);
	}


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

void FollowCamera::SetKeyBoard(Keyboard* keyboard)
{
	m_keyboard = keyboard;
}
