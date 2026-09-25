#include "Vector2.h"

Vector2 Add(const Vector2& v1, const Vector2& v2) { return {v1.x + v2.x, v1.y + v2.y}; }

Vector2 Subtract(const Vector2& v1, const Vector2& v2) { return {v1.x - v2.x, v1.y - v2.y}; }

Vector2 Multiply(float scalar, const Vector2& v) { return {scalar * v.x, scalar * v.y}; }
