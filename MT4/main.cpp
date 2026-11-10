#include <Novice.h>
#include <cstdio>

#include "Quaternion.h"
constexpr char kWindowTitle[] = "学籍番号";
constexpr int kRowHeight = 20;

// 数値を同じ桁数で表示し、四元数と行列の回転結果を比較しやすくする。
void QuaternionScreenPrintf(int x, int y, const Quaternion& value, const char* label) {
	Novice::ScreenPrintf(x, y, "%5.2f %5.2f %5.2f %5.2f    : %s", value.x, value.y, value.z, value.w, label);
}

void VectorScreenPrintf(int x, int y, const Vector3& value, const char* label) {
	Novice::ScreenPrintf(x, y, "%5.2f %5.2f %5.2f    : %s", value.x, value.y, value.z, label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& value, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		Novice::ScreenPrintf(x, y + (row + 1) * kRowHeight, "%6.3f %6.3f %6.3f %6.3f",
			value.m[row][0], value.m[row][1], value.m[row][2], value.m[row][3]);
	}
}

// 課題の確認項目を、通常・同じ向き・真逆の向きで表示する。
void DirectionScreenPrintf(int x, int y, const Vector3& from, const Vector3& to, const char* label) {
	Quaternion rotation = DirectionToDirection(from, to);
	Vector3 rotated = RotateVector(from, rotation);
	Novice::ScreenPrintf(x, y, "%s", label);
	VectorScreenPrintf(x, y + kRowHeight, from, "from");
	VectorScreenPrintf(x, y + kRowHeight * 2, to, "to");
	QuaternionScreenPrintf(x, y + kRowHeight * 3, rotation, "rotation");
	VectorScreenPrintf(x, y + kRowHeight * 4, rotated, "RotateVector(from, rotation)");
	Novice::ScreenPrintf(x, y + kRowHeight * 5, "%.6f    : Norm(rotation)", Norm(rotation));
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Quaternion rotation = MakeRotateAxisAngleQuaternion(Normalize(Vector3{1.0f, 0.4f, -0.2f}), 0.45f);
	Vector3 pointY = {2.1f, -0.9f, 1.3f};
	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotation);
	Vector3 rotateByQuaternion = RotateVector(pointY, rotation);
	Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);
	Quaternion rotation0 = MakeRotateAxisAngleQuaternion(Vector3{0.71f, 0.71f, 0.0f}, 0.3f);
	Quaternion rotation1 = MakeRotateAxisAngleQuaternion(Vector3{0.71f, 0.0f, 0.71f}, 3.141592f);
	Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		QuaternionScreenPrintf(0, kRowHeight * 0, rotation, "rotation");
		MatrixScreenPrintf(0, kRowHeight * 1, rotateMatrix, "rotateMatrix");
		VectorScreenPrintf(0, kRowHeight * 6, rotateByQuaternion, "rotateByQuaternion");
		VectorScreenPrintf(0, kRowHeight * 7, rotateByMatrix, "rotateByMatrix");
		DirectionScreenPrintf(0, kRowHeight * 9, Vector3{1.0f, 0.0f, 0.0f}, Vector3{0.0f, 1.0f, 0.0f}, "normal");
		DirectionScreenPrintf(0, kRowHeight * 16, Vector3{1.0f, 0.0f, 0.0f}, Vector3{1.0f, 0.0f, 0.0f}, "same");
		DirectionScreenPrintf(0, kRowHeight * 23, Vector3{1.0f, 0.0f, 0.0f}, Vector3{-1.0f, 0.0f, 0.0f}, "opposite");
		QuaternionScreenPrintf(650, kRowHeight * 0, rotation0, "rotation0");
		QuaternionScreenPrintf(650, kRowHeight * 1, rotation1, "rotation1");
		QuaternionScreenPrintf(650, kRowHeight * 3, interpolate0, "Slerp(q0, q1, 0.0f)");
		QuaternionScreenPrintf(650, kRowHeight * 4, interpolate1, "Slerp(q0, q1, 0.3f)");
		QuaternionScreenPrintf(650, kRowHeight * 5, interpolate2, "Slerp(q0, q1, 0.5f)");
		QuaternionScreenPrintf(650, kRowHeight * 6, interpolate3, "Slerp(q0, q1, 0.7f)");
		QuaternionScreenPrintf(650, kRowHeight * 7, interpolate4, "Slerp(q0, q1, 1.0f)");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
