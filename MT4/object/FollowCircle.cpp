#include "FollowCircle.h"

#include "../math/Interpolation.h"

FollowCircle::FollowCircle(const Vector2& position, int radius, unsigned int color, const Circle* target, float speed)
    : Circle(position, radius, color)
    , target_(target)
    , speed_(speed) {}

void FollowCircle::Update(float deltaTime) {
	if (target_ == nullptr) {
		return;
	}
	// 前フレームの補間位置を起点に、動き続けるターゲットへ毎フレーム近づける
	// デルタタイムを掛けることで、フレームレートに応じた移動量の補正ができる
	float t = speed_ * deltaTime;
	position_ = Lerp(position_, target_->GetPosition(), t);
}
