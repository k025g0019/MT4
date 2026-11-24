#include <Novice.h>

#include <algorithm>
#include <cmath>
#include <cstring>

#include "math/Vector2.h"

#ifdef USE_IMGUI
#include <imgui.h>
#endif

namespace {

constexpr char kWindowTitle[] = "Jump Ramp";
constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;
constexpr float kPixelsPerMeter = 240.0f;
constexpr Vector2 kScreenOrigin = {300.0f, 620.0f};
constexpr float kRampStart = 0.0f;
constexpr float kRampEnd = 2.0f;
constexpr float kMoveSpeed = 0.6f; // m/s
constexpr float kFrameTime = 1.0f / 60.0f;
constexpr unsigned int kBackgroundColor = 0x5688B8FF;
constexpr unsigned int kRampColor = 0xFFFFFFFF;
constexpr unsigned int kBikeColor = 0xFFAA45FF;

// 台の高さ。ワールド座標では y が上向きで、単位は m。
float f(float x) {
	return 0.125f * x * x * x + 0.25f * x * x;
}

// f(x) = x^3 / 8 + x^2 / 4 を手で微分した接線の傾き。
float fPrime(float x) {
	return 0.375f * x * x + 0.5f * x;
}

Vector2 NormalizeDirection(const Vector2& direction) {
	const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	return {direction.x / length, direction.y / length};
}

// 描画時だけスクリーン座標へ変換する。画面の y 軸は下向き。
Vector2 WorldToScreen(const Vector2& world) {
	return {kScreenOrigin.x + world.x * kPixelsPerMeter,
		kScreenOrigin.y - world.y * kPixelsPerMeter};
}

void DrawWorldLine(const Vector2& from, const Vector2& to, unsigned int color) {
	const Vector2 screenFrom = WorldToScreen(from);
	const Vector2 screenTo = WorldToScreen(to);
	Novice::DrawLine(static_cast<int>(screenFrom.x), static_cast<int>(screenFrom.y),
		static_cast<int>(screenTo.x), static_cast<int>(screenTo.y), color);
}

// 台の接線に沿う一本の線で車体の向きを表す。
void DrawBike(const Vector2& position, const Vector2& forward) {
	constexpr float kHalfLength = 0.12f;
	const Vector2 rear = {position.x - forward.x * kHalfLength,
		position.y - forward.y * kHalfLength};
	const Vector2 front = {position.x + forward.x * kHalfLength,
		position.y + forward.y * kHalfLength};
	DrawWorldLine(rear, front, kBikeColor);

	const Vector2 rearScreen = WorldToScreen(rear);
	const Vector2 frontScreen = WorldToScreen(front);
	constexpr int kPointRadius = 6;
	Novice::DrawEllipse(static_cast<int>(rearScreen.x), static_cast<int>(rearScreen.y),
		kPointRadius, kPointRadius, 0.0f, kBikeColor, kFillModeSolid);
	Novice::DrawEllipse(static_cast<int>(frontScreen.x), static_cast<int>(frontScreen.y),
		kPointRadius, kPointRadius, 0.0f, kBikeColor, kFillModeSolid);
}

} // namespace

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	char keys[256] = {};
	char preKeys[256] = {};
	float x = kRampStart;

	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();
		std::memcpy(preKeys, keys, sizeof(keys));
		Novice::GetHitKeyStateAll(keys);

		// D で登り、A で下る。反対方向の同時押しは相殺する。
		const float moveDirection = static_cast<float>((keys[DIK_D] != 0) - (keys[DIK_A] != 0));
		x = std::clamp(x + moveDirection * kMoveSpeed * kFrameTime, kRampStart, kRampEnd);

		const float slope = fPrime(x);
		const Vector2 position = {x, f(x)};
		const Vector2 forward = NormalizeDirection({1.0f, slope});

		Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0.0f,
			kBackgroundColor, kFillModeSolid);

		// 台の曲線と、その高さ・区間を示す補助線。
		DrawWorldLine({-0.8f, 0.0f}, {3.6f, 0.0f}, kRampColor);
		DrawWorldLine({kRampEnd, 0.0f}, {kRampEnd, f(kRampEnd)}, kRampColor);
		constexpr int kRampSegments = 80;
		for (int i = 0; i < kRampSegments; ++i) {
			const float fromX = kRampEnd * static_cast<float>(i) / kRampSegments;
			const float toX = kRampEnd * static_cast<float>(i + 1) / kRampSegments;
			DrawWorldLine({fromX, f(fromX)}, {toX, f(toX)}, kRampColor);
		}

		DrawBike(position, forward);

#ifdef USE_IMGUI
		ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f), ImGuiCond_FirstUseEver);
		ImGui::Begin("Jump Ramp");
		ImGui::Text("A / D : move");
		ImGui::Separator();
		ImGui::Text("x: %.3f m", x);
		ImGui::Text("f'(x): %.3f", slope);
		ImGui::Text("Forward: (%.3f, %.3f)", forward.x, forward.y);
		ImGui::End();
#endif

		Novice::EndFrame();
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	Novice::Finalize();
	return 0;
}
