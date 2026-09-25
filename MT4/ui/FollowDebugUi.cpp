#include "FollowDebugUi.h"

#include "../object/FollowCircle.h"

#include <cmath>

#ifdef USE_IMGUI
#include <imgui.h>
#endif // USE_IMGUI

void FollowDebugUi::Draw(FollowCircle& followCircle) {
#ifdef USE_IMGUI
	ImGui::Begin("Interpolation Controller");

	// speedを変えて、追従の遅れ具合や吸い付き方の変化を確認する
	ImGui::SliderFloat("Follow speed", followCircle.GetSpeedPtr(), 0.0f, 20.0f, "%.2f");

	const Vector2& position = followCircle.GetPosition();
	ImGui::Text("Follow pos: (%.1f, %.1f)", position.x, position.y);

	const Circle* target = followCircle.GetTarget();
	if (target != nullptr) {
		const Vector2& targetPosition = target->GetPosition();
		ImGui::Text("Target pos: (%.1f, %.1f)", targetPosition.x, targetPosition.y);
		// 追従の遅れを距離で確認する
		float dx = targetPosition.x - position.x;
		float dy = targetPosition.y - position.y;
		ImGui::Text("Distance to target: %.1f px", std::sqrt(dx * dx + dy * dy));
	}

	ImGui::End();
#else
	(void)followCircle;
#endif // USE_IMGUI
}
