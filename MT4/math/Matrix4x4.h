#pragma once

#include "Vector3.h"

/// <summary>
/// 4x4行列(行優先)
/// </summary>
struct Matrix4x4 {
	float m[4][4];
};

// 単位行列
Matrix4x4 MakeIdentity4x4();

// 行ベクトルとして座標を4x4行列で変換する。
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
