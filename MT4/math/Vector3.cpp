#include "Vector3.h"

#include <cmath>

Vector3 Add(const Vector3& v1, const Vector3& v2) { return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z}; }

Vector3 Subtract(const Vector3& v1, const Vector3& v2) { return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z}; }

float Dot(const Vector3& v1, const Vector3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	return {
	    v1.y * v2.z - v1.z * v2.y,
	    v1.z * v2.x - v1.x * v2.z,
	    v1.x * v2.y - v1.y * v2.x,
	};
}

float Length(const Vector3& v) { return std::sqrt(Dot(v, v)); }

Vector3 Normalize(const Vector3& v) {
	float length = Length(v);
	// 長さ0のベクトルは向きを決められないので、そのまま返す
	if (length < 1e-6f) {
		return v;
	}
	return {v.x / length, v.y / length, v.z / length};
}
