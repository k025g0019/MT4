#pragma once

/// <summary>
/// 4x4行列(行優先)
/// </summary>
struct Matrix4x4 {
	float m[4][4];
};

// 単位行列
Matrix4x4 MakeIdentity4x4();
