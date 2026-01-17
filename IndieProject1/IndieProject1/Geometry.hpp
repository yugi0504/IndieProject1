#pragma once
#include "DxLib.h"
#include "MathUtil.hpp"
#include "DxMath.hpp"

namespace Geometry
{
	// 線分最近点の結果
	struct ClosestPointResult
	{
		VECTOR point;
		float t;
	};

	// 線分-線分 最近点（最短距離）結果
	struct SegmentSegmentResult
	{
		VECTOR closestA;
		VECTOR closestB;
		float tA;
		float tB;
		float distSq;
	};

	// カプセル端点（p0,p1）
	struct CapsuleEndpoints
	{
		VECTOR p0;
		VECTOR p1;
	};

	inline float DistSq(const VECTOR& a, const VECTOR& b) noexcept
	{
		return DxMath::DistanceSq(a, b);
	}

	inline ClosestPointResult ClosestPointOnSegment(const VECTOR& p, const VECTOR& a, const VECTOR& b) noexcept
	{
		const VECTOR ab = DxMath::Sub(b,a);
		const float abLenSq = DxMath::LengthSq(ab);

		ClosestPointResult r{};

		if (abLenSq <= MathUtil::EPSILON * MathUtil::EPSILON)
		{
			r.t = 0.0f;
			r.point = a;
			return r;
		}

		const VECTOR ap = DxMath::Sub(p, a);
		const float tRaw = DxMath::Dot(ap, ab) / abLenSq;
		const float t = MathUtil::Clamp(tRaw, 0.0f, 1.0f);

		r.t = t;
		r.point = DxMath::Add(a, DxMath::Mult(ab, t));
		return r;
	}

	inline SegmentSegmentResult ClosestPointsBrtweenSegments(const VECTOR& a0, const VECTOR& a1, const VECTOR& b0, const VECTOR& b1) noexcept
	{
		SegmentSegmentResult out{};

		const VECTOR d1 = DxMath::Sub(a1, a0);
		const VECTOR d2 = DxMath::Sub(b1, b0);
		const VECTOR r = DxMath::Sub(a0, b0);

		const float a = DxMath::Dot(d1, d1);
		const float e = DxMath::Dot(d2, d2);
		const float f = DxMath::Dot(d2, r);

		if (a <= MathUtil::EPSILON * MathUtil::EPSILON &&
			e <= MathUtil::EPSILON * MathUtil::EPSILON)
		{
			out.tA = 0.0f;
			out.tB = 0.0f;
			out.closestA = a0;
			out.closestB = b0;
			out.distSq = DistSq(out.closestA, out.closestB);
			return out;
		}

		if (a <= MathUtil::EPSILON * MathUtil::EPSILON)
		{
			out.tA = 0.0f;
			const auto cp = ClosestPointOnSegment(a0, b0, b1);
			out.tB = cp.t;
			out.closestA = a0;
			out.closestB = cp.point;
			out.distSq = DistSq(out.closestA, out.closestB);
			return out;
		}

		if (e < MathUtil::EPSILON * MathUtil::EPSILON)
		{
			const auto cp = ClosestPointOnSegment(b0, a0, a1);
			out.tA = cp.t;
			out.tB = 0.0f;
			out.closestA = cp.point;
			out.closestB = b0;
			out.distSq = DistSq(out.closestA, out.closestB);
			return out;
		}

		const float b = DxMath::Dot(d1, d2);
		const float c = DxMath::Dot(d1, r);
		const float demon = a * e - b * b;

		float s = 0.0f;
		float t = 0.0f;

		if (std::fabs(demon) <= MathUtil::EPSILON)
		{
			s = 0.0f;
			t = MathUtil::Clamp(f / e, 0.0f, 1.0f);
		}
		else
		{
			s = MathUtil::Clamp((b * f - c * e) / demon, 0.0f, 1.0f);

			const float tNom = b * c + f;
			t = MathUtil::Clamp(tNom / e, 0.0f, 1.0f);
		}

		{
			const float sNom = b * t - c;
			s = MathUtil::Clamp(sNom / a, 0.0f, 1.0f);
		}

		out.tA = s;
		out.tB = t;
		out.closestA = DxMath::Add(a0, DxMath::Mult(d1, s));
		out.closestB = DxMath::Add(b0, DxMath::Mult(d2, t));
		out.distSq = DistSq(out.closestA, out.closestB);
		return out;
	}

	inline CapsuleEndpoints CalcCapsuleEndpoints(const VECTOR& center, const VECTOR& upDir, float halfHeight) noexcept
	{
		const VECTOR axis = DxMath::SafeNomalize(upDir, VGet(0, 1, 0));
		const VECTOR offset = DxMath::Mult(axis, halfHeight);

		CapsuleEndpoints ep{};

		ep.p0 = DxMath::Sub(center, offset);
		ep.p1 = DxMath::Add(center, offset);
		return ep;
	}
}