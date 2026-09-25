#pragma once

#include "Vector2.h"

/// <summary>
/// 線形補間 : p' = p + t * (q - p)
/// </summary>
/// <param name="p">現在地</param>
/// <param name="q">目標</param>
/// <param name="t">補間割合</param>
float Lerp(float p, float q, float t);
Vector2 Lerp(const Vector2& p, const Vector2& q, float t);
