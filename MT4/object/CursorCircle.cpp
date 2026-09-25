#include "CursorCircle.h"

#include <Novice.h>

CursorCircle::CursorCircle(const Vector2& position, int radius, unsigned int color)
    : Circle(position, radius, color) {}

void CursorCircle::Update(float deltaTime) {
	(void)deltaTime;

	int mouseX = 0;
	int mouseY = 0;
	Novice::GetMousePosition(&mouseX, &mouseY);
	position_ = {static_cast<float>(mouseX), static_cast<float>(mouseY)};
}
