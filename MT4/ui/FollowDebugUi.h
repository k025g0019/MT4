#pragma once

class FollowCircle;

/// <summary>
/// 追従補間のパラメータを操作するImGuiウィンドウ
/// </summary>
class FollowDebugUi {
public:
	/// <summary>
	/// 追従速度(speed)をスライダーで変更する
	/// </summary>
	/// <param name="followCircle">操作対象の追従する円</param>
	void Draw(FollowCircle& followCircle);
};
