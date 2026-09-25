#pragma once

class OrbitCamera;

/// <summary>
/// 球面座標の操作と、変換結果の表示を行うImGuiウィンドウ
/// </summary>
class CameraDebugUi {
public:
	/// <summary>
	/// カメラの球面座標を編集し、直交座標とカメラ行列を表示する
	/// </summary>
	/// <param name="camera">操作対象のカメラ</param>
	void Draw(OrbitCamera& camera);
};
