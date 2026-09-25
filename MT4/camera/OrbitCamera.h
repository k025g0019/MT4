#pragma once

#include "../math/Matrix4x4.h"
#include "../math/Spherical.h"
#include "../math/Vector3.h"

/// <summary>
/// 注視点を球面座標で回り込むカメラ
/// </summary>
class OrbitCamera {
public:
	// 球面座標の可動範囲(真上・真下・中心では前Fや右Rが作れないため制限する)
	static const float kMinRadius;
	static const float kThetaLimit;

	OrbitCamera();

	/// <summary>
	/// 球面座標を可動範囲に収め、カメラ位置とワールド行列を作り直す
	/// </summary>
	void Update();

	// 注視点
	void SetTarget(const Vector3& target);
	const Vector3& GetTarget() const { return target_; }

	// 球面座標(操作用のパラメータ)
	void SetSpherical(const Spherical& spherical);
	const Spherical& GetSpherical() const { return spherical_; }
	Spherical& GetSphericalRef() { return spherical_; }

	// 注視点から見たカメラのオフセット(球面座標を直交座標にしたもの)
	const Vector3& GetOffset() const { return offset_; }
	// ワールドでのカメラ位置
	const Vector3& GetEye() const { return eye_; }
	// カメラのワールド行列
	const Matrix4x4& GetWorldMatrix() const { return worldMatrix_; }

private:
	// 球面座標からカメラ位置を求める
	void UpdateEye();
	// 注視点を向く3本の軸とカメラ位置からワールド行列を作る
	void UpdateWorldMatrix();

	Vector3 target_;
	Spherical spherical_;

	Vector3 offset_;
	Vector3 eye_;
	Matrix4x4 worldMatrix_;
};
