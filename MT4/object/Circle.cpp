#include "Circle.h"

#include <Novice.h>

Circle::Circle(const Vector2& position, int radius, unsigned int color)
    : position_(position)
    , radius_(radius)
    , color_(color) {}

void Circle::Update(float deltaTime) {
	// 基底クラスの円は動かない
	(void)deltaTime;
}

void Circle::Draw() const { Novice::DrawEllipse(static_cast<int>(position_.x), static_cast<int>(position_.y), radius_, radius_, 0.0f, color_, kFillModeSolid); }
