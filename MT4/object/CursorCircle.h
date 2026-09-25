#pragma once

#include "Circle.h"

/// <summary>
/// マウスカーソルの位置に表示する円(追従のターゲット)
/// </summary>
class CursorCircle : public Circle {
public:
	CursorCircle(const Vector2& position, int radius, unsigned int color);

	/// <summary>
	/// 毎フレーム、マウス座標を取得して位置を更新する
	/// </summary>
	void Update(float deltaTime) override;
};
