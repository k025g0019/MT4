#pragma once

#include "Vector3.h"

/// <summary>
/// 球面座標系
/// </summary>
struct Spherical {
	float radius; // 動径 r : 中心からの距離
	float theta;  // 仰角 θ : 水平面からの角度 [rad]
	float phi;    // 方位角 φ : 水平面での回転 [rad]
};

/// <summary>
/// 球面座標から直交座標への変換
/// </summary>
Vector3 ToCartesian(const Spherical& s);

/// <summary>
/// 直交座標から球面座標への変換(逆変換)
/// </summary>
Spherical ToSpherical(const Vector3& p);
