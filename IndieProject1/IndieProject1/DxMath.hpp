#pragma once
#include "DxLib.h"
#include <cmath>
#include "mathutil.hpp"

namespace dxmath
{
	// ベクトル二乗長
	inline float LengthSq(const VECTOR& v) noexcept
	{
		return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	}

	// ベクトル長
	inline float Length(const VECTOR& v) noexcept
	{
		return std::sqrt(LengthSq(v));
	}

	// 内積
	inline float Dot(const VECTOR& a, const VECTOR& b)noexcept
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	// 外積
	inline VECTOR Cross(const VECTOR& a, const VECTOR& b) noexcept
	{
		return VGet(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}

	// 加算
	inline VECTOR Add(const VECTOR& a, const VECTOR& b) noexcept
	{
		return VGet(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	// 減算
	inline VECTOR Sub(const VECTOR& a, const VECTOR& b) noexcept
	{
		return VGet(a.x - b.x, a.y - b.y,a.z - b.z);
	}

	// スカラー倍
	inline VECTOR Mult(const VECTOR& v, float s) noexcept
	{
		return VGet(v.x * s, v.y * s, v.z * s);
	}

	// 零長対応の正規化
	inline VECTOR SafeNomalize(const VECTOR& v, const VECTOR& fallback = VGet(0, 1, 0)) noexcept
	{
		const float lsq = Length(v);
		if (lsq <= mathutil::EPSILON * mathutil::EPSILON) return fallback;
		const float invLen = 1.0f / std::sqrt(lsq);
		return Mult(v, invLen);
	}

	// 距離(基本こっち)
	inline float DistanceSq(const VECTOR& a, const VECTOR& b) noexcept
	{
		return LengthSq(Sub(a, b));
	}

	// 距離
	inline float Distance(const VECTOR& a, const VECTOR& b) noexcept
	{
		return std::sqrt(DistanceSq(a, b));
	}

	// 方向ベクトル計算
	inline VECTOR Direction(const VECTOR& from, const VECTOR& to, const VECTOR& fallback = VGet(0, 0, 1)) noexcept
	{
		return SafeNomalize(Sub(to, from), fallback);
	}
}