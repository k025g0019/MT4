#include "Spherical.h"

#include <algorithm>
#include <cmath>

Vector3 ToCartesian(const Spherical& s) {
	// 仰角θで高さyと水平面の半径ρに分け、方位角φでρをxとzに分ける
	float rho = s.radius * std::cos(s.theta);
	return {
	    rho * std::cos(s.phi),
	    s.radius * std::sin(s.theta),
	    rho * std::sin(s.phi),
	};
}

Spherical ToSpherical(const Vector3& p) {
	float r = Length(p);
	// 原点では角度が決まらないので、ここでは0として返す
	if (r < 1e-6f) {
		return {0.0f, 0.0f, 0.0f};
	}
	// 丸め誤差で asin の入力が±1を超えるのを防ぐ
	float sinTheta = std::clamp(p.y / r, -1.0f, 1.0f);
	// y軸上では方位角が決まらないので、ここではφを0とする
	float phi = 0.0f;
	if (p.x != 0.0f || p.z != 0.0f) {
		phi = std::atan2(p.z, p.x);
	}
	return {r, std::asin(sinTheta), phi};
}
