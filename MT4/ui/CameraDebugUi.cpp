#include "CameraDebugUi.h"

#include "../camera/OrbitCamera.h"

#ifdef USE_IMGUI
#include <imgui.h>
#endif // USE_IMGUI

void CameraDebugUi::Draw(OrbitCamera& camera) {
#ifdef USE_IMGUI
	ImGui::Begin("Spherical Coordinates");

	ImGui::Text("Target: (%.1f, %.1f, %.1f) / +Y up / Camera +Z forward", camera.GetTarget().x, camera.GetTarget().y, camera.GetTarget().z);

	// 球面座標(角度はrad表記)を編集可能にする
	Spherical& spherical = camera.GetSphericalRef();
	bool edited = false;
	edited |= ImGui::InputFloat("Radius", &spherical.radius, 0.1f, 1.0f, "%.3f");
	edited |= ImGui::InputFloat("Theta: elevation (rad)", &spherical.theta, 0.01f, 0.1f, "%.3f");
	edited |= ImGui::InputFloat("Phi (rad)", &spherical.phi, 0.01f, 0.1f, "%.3f");
	if (edited) {
		// 入力値を可動範囲に収め、カメラを作り直す
		camera.Update();
	}

	ImGui::Separator();

	// 変換した直交座標を表示する
	ImGui::Text("Spherical: r = %.3f, theta = %.3f rad, phi = %.3f rad", spherical.radius, spherical.theta, spherical.phi);
	const Vector3& eye = camera.GetEye();
	ImGui::Text("Cartesian: x = %.3f, y = %.3f, z = %.3f", eye.x, eye.y, eye.z);

	// 作成したカメラ行列(4x4)を表示する
	ImGui::Text("Camera matrix");
	const Matrix4x4& worldMatrix = camera.GetWorldMatrix();
	for (int row = 0; row < 4; ++row) {
		ImGui::Text("%10.3f%10.3f%10.3f%10.3f", worldMatrix.m[row][0], worldMatrix.m[row][1], worldMatrix.m[row][2], worldMatrix.m[row][3]);
	}

	ImGui::End();
#else
	// ImGuiを使わない構成では何もしない
	(void)camera;
#endif // USE_IMGUI
}
