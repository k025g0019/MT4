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
