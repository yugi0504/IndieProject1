#pragma once

#include <cmath>
#include <algorithm>
#include <limits>

namespace mathutil
{
	// 定数
	inline constexpr float EPSILON = 1e-6f;

	// 角度
	inline constexpr float PI = 3.14159265358979323846f;


	// 角度変換
	
	// 弧度法 → 度数法
	inline constexpr float DegTorad(float deg) noexcept
	{
		return deg * (PI / 180.0f);
	}

	//弧度法 → 度数法
	inline constexpr float RadToDeg(float rad) noexcept
	{
		return rad * (180.0f / PI);
	}


	// Clamp(テンプレート化)
	template <class T>
	inline constexpr T Clamp(T value, T min, T max) noexcept
	{
		return (value < min) ? min : (value > max) ? max : value;
	}

	// 線形補間
	inline float Lerp(float a, float b, float t) noexcept
	{
		return a + (b - a) * t;
	}


	// 浮動小数比較
	
	// 近似比較(ほぼ等しい)
	inline bool NearlyEqual(float a, float b, float eps = EPSILON) noexcept
	{
		return std::fabs(a - b) <= eps;
	}

	// ０判定
	inline bool IsZero(float a, float eps = EPSILON) noexcept
	{
		return std::fabs(a) <= eps;
	}


	// 角度ラップ　
	
	// 角度を[-PI,PI]の範囲に正規化
	inline float WrapAnglePi(float rad) noexcept
	{
		// fmodの負値対策
		float x = std::fmod(rad + PI, 2.0f * PI);
		if (x < 0.0f) x += 2.0f * PI;
		return x - PI;
	}
}