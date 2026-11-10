#pragma once
/// <summary>
/// Quaternion(四元数)
/// </summary>
#include "math/Matrix4x4.h"
#include "math/Vector3.h"


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

//　任意の軸回転を表す
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

//ベクトルをQuaterinionで回転させた結果のベクトルを求める
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

// 正規化済みの from を to に向ける単位四元数を返す
Quaternion DirectionToDirection(const Vector3& from, const Vector3& to);

//Quaternionから回転行列を作る
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);
