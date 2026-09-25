#pragma once

#include "../math/Vector2.h"

/// <summary>
/// 画面に描画する円の基底クラス
/// </summary>
class Circle {
public:
	Circle(const Vector2& position, int radius, unsigned int color);
	virtual ~Circle() = default;

	/// <summary>
	/// 1フレーム分の更新。動かない円は何もしない
	/// </summary>
	/// <param name="deltaTime">前フレームからの経過時間[秒]</param>
	virtual void Update(float deltaTime);

	/// <summary>
	/// 円を描画する
	/// </summary>
	virtual void Draw() const;

	const Vector2& GetPosition() const { return position_; }
	void SetPosition(const Vector2& position) { position_ = position; }
	int GetRadius() const { return radius_; }

protected:
	Vector2 position_;
	int radius_;
	unsigned int color_;
};
