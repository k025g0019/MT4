#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 {
	float x;
	float y;
	float z;
};

// 加減算
Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

// 内積・外積
float Dot(const Vector3& v1, const Vector3& v2);
Vector3 Cross(const Vector3& v1, const Vector3& v2);

// 長さ・正規化
float Length(const Vector3& v);
Vector3 Normalize(const Vector3& v);
