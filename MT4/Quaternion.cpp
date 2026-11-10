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

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle) {
	// 回転軸を正規化
	Vector3 n = Normalize(axis);

	// 回転角度の半分
	float halfAngle = angle / 2.0f;

	Quaternion result;
	result.x = n.x * std::sin(halfAngle);
	result.y = n.y * std::sin(halfAngle);
	result.z = n.z * std::sin(halfAngle);
	result.w = std::cos(halfAngle);

	return result;
}

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion) {
	// ベクトルを四元数として表現
	Quaternion vectorQuat{vector.x, vector.y, vector.z, 0.0f};
	// 回転を適用。既存APIは変更可能な参照を受けるため、四元数を複製して渡す。
	Quaternion rotation = quaternion;
	Quaternion firstProduct = Multiply(rotation, vectorQuat);
	Quaternion inverse = Inverse(rotation);
	Quaternion rotatedQuat = Multiply(firstProduct, inverse);
	// 結果のベクトルを返す
	return Vector3{rotatedQuat.x, rotatedQuat.y, rotatedQuat.z};
}

Quaternion DirectionToDirection(const Vector3& from, const Vector3& to) {
	const float dot = Dot(from, to);
	const Vector3 cross = Cross(from, to);
	const float crossLengthSquared = Dot(cross, cross);

	// 真逆の方向では外積がゼロになるので、from に直交する回転軸を選ぶ。
	constexpr float kOppositeAxisEpsilonSquared = 1.0e-12f;
	if (dot < 0.0f && crossLengthSquared < kOppositeAxisEpsilonSquared) {
		// 最も成分の小さい軸を選ぶと、外積を安定して正規化できる。
		Vector3 referenceAxis{1.0f, 0.0f, 0.0f};
		if (std::abs(from.y) <= std::abs(from.x) && std::abs(from.y) <= std::abs(from.z)) {
			referenceAxis = Vector3{0.0f, 1.0f, 0.0f};
		} else if (std::abs(from.z) <= std::abs(from.x)) {
			referenceAxis = Vector3{0.0f, 0.0f, 1.0f};
		}
		const Vector3 axis = Normalize(Cross(from, referenceAxis));
		return Quaternion{axis.x, axis.y, axis.z, 0.0f};
	}

	// q = (from × to, 1 + from・to) を正規化すると最短回転になる。
	Quaternion rotation{cross.x, cross.y, cross.z, 1.0f + dot};
	return Normalize(rotation);
}

Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion) {
	Matrix4x4 rotationMatrix;
	float xx = quaternion.x * quaternion.x;
	float yy = quaternion.y * quaternion.y;
	float zz = quaternion.z * quaternion.z;
	float xy = quaternion.x * quaternion.y;
	float xz = quaternion.x * quaternion.z;
	float yz = quaternion.y * quaternion.z;
	float wx = quaternion.w * quaternion.x;
	float wy = quaternion.w * quaternion.y;
	float wz = quaternion.w * quaternion.z;
	rotationMatrix.m[0][0] = 1.0f - 2.0f * (yy + zz);
	// Transform の行ベクトル方式に合わせて転置した配置にする。
	rotationMatrix.m[0][1] = 2.0f * (xy + wz);
	rotationMatrix.m[0][2] = 2.0f * (xz - wy);
	rotationMatrix.m[0][3] = 0.0f;
	rotationMatrix.m[1][0] = 2.0f * (xy - wz);
	rotationMatrix.m[1][1] = 1.0f - 2.0f * (xx + zz);
	rotationMatrix.m[1][2] = 2.0f * (yz + wx);
	rotationMatrix.m[1][3] = 0.0f;
	rotationMatrix.m[2][0] = 2.0f * (xz + wy);
	rotationMatrix.m[2][1] = 2.0f * (yz - wx);
	rotationMatrix.m[2][2] = 1.0f - 2.0f * (xx + yy);
	rotationMatrix.m[2][3] = 0.0f;
	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;
	return rotationMatrix;
}
