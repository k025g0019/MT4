#include <Novice.h>

#include <cmath>
#include <cstring>

#include "math/Vector2.h"

#ifdef USE_IMGUI
#include <imgui.h>
#endif

// スカラーを左に置くベクトルの掛け算。ベジェ曲線の式で使用する。
Vector2 operator*(float s, const Vector2& v) {
	return {s * v.x, s * v.y};
}

// 2次ベジェ曲線上の点を返す。
Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t) {
	const Vector2 first = Add((1.0f - t) * p0, t * p1);
	const Vector2 second = Add((1.0f - t) * p1, t * p2);
	return Add((1.0f - t) * first, t * second);
}

// B(t) = (1-t)^2 p0 + 2(1-t)t p1 + t^2 p2 を微分した接線ベクトル。
Vector2 BezierDerivative(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t) {
	return Add(2.0f * (1.0f - t) * Subtract(p1, p0),
		2.0f * t * Subtract(p2, p1));
}

namespace {

constexpr char kWindowTitle[] = "Bezier";
constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;
constexpr unsigned int kBackgroundColor = 0x5688B8FF;
constexpr unsigned int kCurveColor = 0xFFFFFFFF;
constexpr unsigned int kPointColor = 0xFFAA45FF;
constexpr unsigned int kTangentColor = 0xE65050FF;
constexpr float kTangentLength = 120.0f;

void DrawBezierCurve(const Vector2& p0, const Vector2& p1, const Vector2& p2) {
	constexpr int kSegments = 100;
	for (int i = 0; i < kSegments; ++i) {
		const float fromT = static_cast<float>(i) / kSegments;
		const float toT = static_cast<float>(i + 1) / kSegments;
		const Vector2 from = Bezier(p0, p1, p2, fromT);
		const Vector2 to = Bezier(p0, p1, p2, toT);
		Novice::DrawLine(static_cast<int>(from.x), static_cast<int>(from.y),
			static_cast<int>(to.x), static_cast<int>(to.y), kCurveColor);
	}
}

void DrawPointAndTangent(const Vector2& point, const Vector2& derivative) {
	const float length = std::sqrt(derivative.x * derivative.x + derivative.y * derivative.y);
	if (length > 0.0f) {
		const Vector2 end = Add(point, (kTangentLength / length) * derivative);
		Novice::DrawLine(static_cast<int>(point.x), static_cast<int>(point.y),
			static_cast<int>(end.x), static_cast<int>(end.y), kTangentColor);
	}

	constexpr int kPointRadius = 6;
	Novice::DrawEllipse(static_cast<int>(point.x), static_cast<int>(point.y),
		kPointRadius, kPointRadius, 0.0f, kPointColor, kFillModeSolid);
}

#ifdef USE_IMGUI
void DrawBezierUi(float& t, Vector2& p1, const Vector2& p0, const Vector2& p2) {
	ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f), ImGuiCond_FirstUseEver);
	ImGui::Begin("Bezier");
	ImGui::SliderFloat("t", &t, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat("p1 x", &p1.x, 400.0f, 880.0f, "%.0f");
	ImGui::SliderFloat("p1 y", &p1.y, 20.0f, 570.0f, "%.0f");
	ImGui::Separator();
	const Vector2 point = Bezier(p0, p1, p2, t);
	const Vector2 derivative = BezierDerivative(p0, p1, p2, t);
	ImGui::Text("B(t): (%.2f, %.2f)", point.x, point.y);
	ImGui::Text("B'(t): (%.2f, %.2f)", derivative.x, derivative.y);
	ImGui::End();
}
#endif

} // namespace

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	const Vector2 p0 = {200.0f, 570.0f};
	Vector2 p1 = {800.0f, 70.0f};
	const Vector2 p2 = {1080.0f, 570.0f};
	float t = 0.5f;
	char keys[256] = {};
	char preKeys[256] = {};

	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();
		std::memcpy(preKeys, keys, sizeof(keys));
		Novice::GetHitKeyStateAll(keys);

#ifdef USE_IMGUI
		DrawBezierUi(t, p1, p0, p2);
#endif

		const Vector2 point = Bezier(p0, p1, p2, t);
		const Vector2 derivative = BezierDerivative(p0, p1, p2, t);
		Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0.0f,
			kBackgroundColor, kFillModeSolid);
		DrawBezierCurve(p0, p1, p2);
		DrawPointAndTangent(point, derivative);

		Novice::EndFrame();
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	Novice::Finalize();
	return 0;
}
