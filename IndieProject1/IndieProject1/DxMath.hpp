#pragma once
#include "DxLib.h"
#include <cmath>
#include "MathUtil.hpp"

namespace DxMath
{
	inline float LengthSq(const VECTOR& v) noexcept
	{
		return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	}

	inline float Length(const VECTOR& v) noexcept
	{
		return std::sqrt(LengthSq(v));
	}

	inline float Dot(const VECTOR& a, const VECTOR& b)noexcept
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline VECTOR Cross(const VECTOR& a, const VECTOR& b) noexcept
	{
		return VGet(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}

	inline VECTOR Add(const VECTOR& a, const VECTOR& b) noexcept
	{
		return VGet(a.x + b.x, a.y + b.y, a.z + b.z);
	}
}