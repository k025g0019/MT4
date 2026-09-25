#pragma once

#include "../object/CursorCircle.h"
#include "../object/FollowCircle.h"

/// <summary>
/// 円の追従補間を確認するシーン
/// </summary>
class FollowScene {
public:
	// 60fpsを前提とした固定のデルタタイム
	static const float kDeltaTime;

	FollowScene();

	/// <summary>
	/// 円をまとめて更新する
	/// </summary>
	void Update();

	/// <summary>
	/// 2つの円と、追従の遅れを可視化する線を描画する
	/// </summary>
	void Draw() const;

	FollowCircle& GetFollowCircle() { return followCircle_; }

private:
	CursorCircle cursorCircle_;
	FollowCircle followCircle_;

	// 基底クラスのポインタでまとめて更新する
	Circle* circles_[2];
};
