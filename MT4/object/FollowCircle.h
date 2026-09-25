#pragma once

#include "Circle.h"

/// <summary>
/// ターゲットへ線形補間で追従する円
/// </summary>
class FollowCircle : public Circle {
public:
	FollowCircle(const Vector2& position, int radius, unsigned int color, const Circle* target, float speed);

	/// <summary>
	/// 毎フレーム、ターゲットへ pos += (speed * deltaTime) * (target - pos) で近づく
	/// </summary>
	void Update(float deltaTime) override;

	// 追従速度(ImGuiで変更する)
	void SetSpeed(float speed) { speed_ = speed; }
	float GetSpeed() const { return speed_; }
	float* GetSpeedPtr() { return &speed_; }

	const Circle* GetTarget() const { return target_; }

private:
	const Circle* target_;
	float speed_;
};
