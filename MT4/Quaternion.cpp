#include "Quaternion.h"

#include <cmath>
#include <sys/stat.h>
/// <summary>
/// 四元数の関数群
/// 

// 単位四元数
Quaternion IdentityQuaternion() {
	return Quaternion{0.0f, 0.0f, 0.0f, 1.0f};
}

// 共役四元数
Quaternion Conjugate(Quaternion& quaternion) {
	return Quaternion{-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w};
}

// 四元数のノルム
float Norm(const Quaternion& quaternion) {
	return std::sqrt(
		quaternion.x * quaternion.x +
		quaternion.y * quaternion.y +
		quaternion.z * quaternion.z +
		quaternion.w * quaternion.w
	);
}

// 逆四元数
Quaternion Inverse(Quaternion& quaternion) {
	float norm = Norm(quaternion);

	if (norm == 0.0f) {
		// ノルムがゼロの場合、逆四元数は定義されない
		return IdentityQuaternion();
	}

	float normSquared = norm * norm;

	Quaternion conjugate = Conjugate(quaternion);

	return Quaternion{
		conjugate.x / normSquared,
		conjugate.y / normSquared,
		conjugate.z / normSquared,
		conjugate.w / normSquared
	};
}

// 正規化四元数
Quaternion Normalize(Quaternion& quaternion) {
	float norm = Norm(quaternion);
	if (norm == 0.0f) {
		// ノルムがゼロの場合、正規化できないため、単位四元数を返す
		return IdentityQuaternion();
	}
	return Quaternion{quaternion.x / norm, quaternion.y / norm, quaternion.z / norm, quaternion.w / norm};
}

// 四元数の積
Quaternion Multiply(Quaternion& lhs, Quaternion& rhs) {
	return Quaternion{
		lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x,
		lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w,
		lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
	};
}
