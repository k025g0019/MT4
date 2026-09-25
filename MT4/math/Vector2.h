#pragma once

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 {
	float x;
	float y;
};

// 加減算
Vector2 Add(const Vector2& v1, const Vector2& v2);
Vector2 Subtract(const Vector2& v1, const Vector2& v2);

// スカラー倍
Vector2 Multiply(float scalar, const Vector2& v);
