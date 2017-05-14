//*--------------------------------------------------------------*//
//= @file   名前
//=
//= @brief  概要 カメラを制御するクラス
//=
//= @date   日付
//=
//= @author 制作者	ShutaFurukawa
//*--------------------------------------------------------------*//

//多重インクルード防止
#pragma once

#include <SimpleMath.h>

class Camera
{
	//限定公開メンバ
protected:
	//ビュー行列
	//どこから見るのか（視点）
	DirectX::SimpleMath::Vector3 m_eyePos;
	//どこを見るのか(注視点)
	DirectX::SimpleMath::Vector3 m_refPos;
	//どちらが画面上方向か（上方向ベクトル）
	DirectX::SimpleMath::Vector3 m_upVec;

	static float m_angle;


	//射影行列
	//垂直方向視野角
	float m_fovY;
	//アスペクト比(横・縦の比率)
	float m_aspect;
	//手前の表示限界
	float m_nearClip = 0.1f;
	//奥の表示限界
	float m_farClip = 1000.0f;

	//ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	//射影行列
	DirectX::SimpleMath::Matrix m_proj;

	//公開メンバ
public:
	//コンストラクタ
	Camera(int width, int hight);
	Camera();
	//仮想デストラクタ
	virtual ~Camera();

	//更新関数
	void update();

	//ビュー行列を取得
	DirectX::SimpleMath::Matrix GetViewMatrix();

	//射影行列を取得
	DirectX::SimpleMath::Matrix GetProjMatrix();

	//視点をセットする関数
	void SetEyePos(DirectX::SimpleMath::Vector3 eyepos);
	//注視点をセットする関数
	void SetRefPos(DirectX::SimpleMath::Vector3 refpos);
	//上方向ベクトルをセットする関数
	void SetUpVec(DirectX::SimpleMath::Vector3 uppos);
	//垂直方向視野角をセットする関数
	void SetFovY(float fovy);
	//アスペクト比をセットする関数
	void SetAspect(float aspect);
	//手前の表示限界をセットする関数
	void SetNearClip(float neraclip);
	//奥の表示限界をセットする関数
	void SetFarClip(float farclip);
};