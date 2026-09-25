#include "Interpolation.h"

float Lerp(float p, float q, float t) {
	// 「現在地から目標へ、差の t 割だけ近づける」という見方で実装する
	return p + t * (q - p);
}

Vector2 Lerp(const Vector2& p, const Vector2& q, float t) { return Add(p, Multiply(t, Subtract(q, p))); }
