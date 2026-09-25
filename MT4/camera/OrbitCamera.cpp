#include "OrbitCamera.h"

#include <algorithm>
#include <numbers>

const float OrbitCamera::kMinRadius = 0.1f;
const float OrbitCamera::kThetaLimit = std::numbers::pi_v<float> / 2.0f - 0.01f;

OrbitCamera::OrbitCamera()
    : target_{0.0f, 0.0f, 0.0f}
    , spherical_{6.0f, 0.0f, -std::numbers::pi_v<float> / 2.0f}
    , offset_{0.0f, 0.0f, 0.0f}
    , eye_{0.0f, 0.0f, 0.0f}
    , worldMatrix_(MakeIdentity4x4()) {
	Update();
}

void OrbitCamera::Update() {
	// 中心・真上・真下は特異点なので、操作側でクランプしておく
	spherical_.radius = std::max(spherical_.radius, kMinRadius);
	spherical_.theta = std::clamp(spherical_.theta, -kThetaLimit, kThetaLimit);

	UpdateEye();
	UpdateWorldMatrix();
}

void OrbitCamera::SetTarget(const Vector3& target) {
	target_ = target;
	Update();
}

void OrbitCamera::SetSpherical(const Spherical& spherical) {
	spherical_ = spherical;
	Update();
}

void OrbitCamera::UpdateEye() {
	// 注視点に球面座標から求めたオフセットを加算して、ワールドでのカメラ位置を求める
	offset_ = ToCartesian(spherical_);
	eye_ = Add(target_, offset_);
}

void OrbitCamera::UpdateWorldMatrix() {
	Vector3 worldUp = {0.0f, 1.0f, 0.0f};
	// 注視点 - カメラ位置で前Fを求める
	Vector3 forward = Normalize(Subtract(target_, eye_));
	// 世界の上と前Fの外積で右Rを求める
	Vector3 right = Normalize(Cross(worldUp, forward));
	// 前Fと右Rの外積でカメラ自身の上Uを求め直す
	Vector3 up = Cross(forward, right);

	// 求めた3本の直交軸とカメラ位置を行列に並べる
	worldMatrix_ = Matrix4x4{
	    {
             {right.x, right.y, right.z, 0.0f},
             {up.x, up.y, up.z, 0.0f},
             {forward.x, forward.y, forward.z, 0.0f},
             {eye_.x, eye_.y, eye_.z, 1.0f},
	     }
    };
}
