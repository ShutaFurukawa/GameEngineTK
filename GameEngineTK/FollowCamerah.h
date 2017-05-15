//*--------------------------------------------------------------*//
//= @file   名前
//=
//= @brief  概要 自機を追従するカメラを制御するクラス
//=
//= @date   日付
//=
//= @author 制作者	ShutaFurukawa
//*--------------------------------------------------------------*//

#pragma once

#include "Camera.h"

class FollowCamera : public Camera
{
private:
	//追従対象の座標
	DirectX::SimpleMath::Vector3 m_target_pos;
	//追従座標の回転角
	float m_target_amgle;
	
public:
	//追従対象とカメラの距離
	static const float CAMERA_DISTANCE;
	//コンストラクタ
	FollowCamera(int width, int hight);

	//毎フレーム更新
	void update() override;
	//追従対象の座標をセットする関数
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);
	//追従対象の回転角をセットする関数
	void SetTargetAngle(float targetangle);

};
