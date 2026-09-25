#include "FollowScene.h"

#include <Novice.h>

const float FollowScene::kDeltaTime = 1.0f / 60.0f;

namespace {
// 円Aは半径12の赤、円Bは半径20の緑
const int kCursorRadius = 12;
const int kFollowRadius = 20;
const Vector2 kFollowStartPosition = {640.0f, 360.0f};
const float kDefaultSpeed = 6.0f;
} // namespace

FollowScene::FollowScene()
    : cursorCircle_(kFollowStartPosition, kCursorRadius, RED)
    , followCircle_(kFollowStartPosition, kFollowRadius, GREEN, &cursorCircle_, kDefaultSpeed)
    , circles_{&cursorCircle_, &followCircle_} {}

void FollowScene::Update() {
	// ターゲット(円A)を先に更新してから、追従する円Bを更新する
	for (Circle* circle : circles_) {
		circle->Update(kDeltaTime);
	}
}

void FollowScene::Draw() const {
	// 円Aと円Bの中心を結ぶ線で、追従の遅れを可視化する
	const Vector2& cursorPosition = cursorCircle_.GetPosition();
	const Vector2& followPosition = followCircle_.GetPosition();
	Novice::DrawLine(static_cast<int>(cursorPosition.x), static_cast<int>(cursorPosition.y), static_cast<int>(followPosition.x), static_cast<int>(followPosition.y), WHITE);

	for (const Circle* circle : circles_) {
		circle->Draw();
	}
}
