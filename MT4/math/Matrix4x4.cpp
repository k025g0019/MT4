#include "Matrix4x4.h"

Matrix4x4 MakeIdentity4x4() {
	return Matrix4x4{
	    {
             {1.0f, 0.0f, 0.0f, 0.0f},
             {0.0f, 1.0f, 0.0f, 0.0f},
             {0.0f, 0.0f, 1.0f, 0.0f},
             {0.0f, 0.0f, 0.0f, 1.0f},
	     }
    };
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result{
		vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0],
		vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1],
		vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2],
	};
	const float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];
	if (w != 0.0f) {
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}
	return result;
}
