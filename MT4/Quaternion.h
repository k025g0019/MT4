#pragma once
/// <summary>
/// Quaternion(四元数)
/// </summary>

struct Quaternion {
	float x; // 実部
	float y; // 虚部i
	float z; // 虚部j
	float w; // 虚部k
};

Quaternion IdentityQuaternion(); // 単位四元数

Quaternion Conjugate(Quaternion& quaternion); // 共役四元数

Quaternion Inverse(Quaternion& quaternion); // 逆四元数

Quaternion Normalize(Quaternion& quaternion); // 正規化四元数

Quaternion Multiply(Quaternion& lhs, Quaternion& rhs); // 四元数の積
float Norm(const Quaternion& quaternion); // 四元数のノルム
