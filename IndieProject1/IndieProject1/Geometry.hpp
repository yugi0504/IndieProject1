#pragma once
#include "DxLib.h"
#include "mathutil.hpp"
#include "dxmath.hpp"

namespace geometry
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
		return dxmath::DistanceSq(a, b);
	}

	inline ClosestPointResult ClosestPointOnSegment(const VECTOR& p, const VECTOR& a, const VECTOR& b) noexcept
	{
		const VECTOR ab = dxmath::Sub(b,a);
		const float abLenSq = dxmath::LengthSq(ab);

		ClosestPointResult r{};

		if (abLenSq <= mathutil::EPSILON * mathutil::EPSILON)
		{
			r.t = 0.0f;
			r.point = a;
			return r;
		}

		const VECTOR ap = dxmath::Sub(p, a);
		const float tRaw = dxmath::Dot(ap, ab) / abLenSq;
		const float t = mathutil::Clamp(tRaw, 0.0f, 1.0f);

		r.t = t;
		r.point = dxmath::Add(a, dxmath::Mult(ab, t));
		return r;
	}

	inline SegmentSegmentResult ClosestPointsBrtweenSegments(const VECTOR& a0, const VECTOR& a1, const VECTOR& b0, const VECTOR& b1) noexcept
	{
		SegmentSegmentResult out{};

		const VECTOR d1 = dxmath::Sub(a1, a0);
		const VECTOR d2 = dxmath::Sub(b1, b0);
		const VECTOR r = dxmath::Sub(a0, b0);

		const float a = dxmath::Dot(d1, d1);
		const float e = dxmath::Dot(d2, d2);
		const float f = dxmath::Dot(d2, r);

		if (a <= mathutil::EPSILON * mathutil::EPSILON &&
			e <= mathutil::EPSILON * mathutil::EPSILON)
		{
			out.tA = 0.0f;
			out.tB = 0.0f;
			out.closestA = a0;
			out.closestB = b0;
			out.distSq = DistSq(out.closestA, out.closestB);
			return out;
		}

		if (a <= mathutil::EPSILON * mathutil::EPSILON)
		{
			out.tA = 0.0f;
			const auto cp = ClosestPointOnSegment(a0, b0, b1);
			out.tB = cp.t;
			out.closestA = a0;
			out.closestB = cp.point;
			out.distSq = DistSq(out.closestA, out.closestB);
			return out;
		}

		if (e < mathutil::EPSILON * mathutil::EPSILON)
		{
			const auto cp = ClosestPointOnSegment(b0, a0, a1);
			out.tA = cp.t;
			out.tB = 0.0f;
			out.closestA = cp.point;
			out.closestB = b0;
			out.distSq = DistSq(out.closestA, out.closestB);
			return out;
		}

		const float b = dxmath::Dot(d1, d2);
		const float c = dxmath::Dot(d1, r);
		const float demon = a * e - b * b;

		float s = 0.0f;
		float t = 0.0f;

		if (std::fabs(demon) <= mathutil::EPSILON)
		{
			s = 0.0f;
			t = mathutil::Clamp(f / e, 0.0f, 1.0f);
		}
		else
		{
			s = mathutil::Clamp((b * f - c * e) / demon, 0.0f, 1.0f);

			const float tNom = b * c + f;
			t = mathutil::Clamp(tNom / e, 0.0f, 1.0f);
		}

		{
			const float sNom = b * t - c;
			s = mathutil::Clamp(sNom / a, 0.0f, 1.0f);
		}

		out.tA = s;
		out.tB = t;
		out.closestA = dxmath::Add(a0, dxmath::Mult(d1, s));
		out.closestB = dxmath::Add(b0, dxmath::Mult(d2, t));
		out.distSq = DistSq(out.closestA, out.closestB);
		return out;
	}

	inline CapsuleEndpoints CalcCapsuleEndpoints(const VECTOR& center, const VECTOR& upDir, float halfHeight) noexcept
	{
		const VECTOR axis = dxmath::SafeNomalize(upDir, VGet(0, 1, 0));
		const VECTOR offset = dxmath::Mult(axis, halfHeight);

		CapsuleEndpoints ep{};

		ep.p0 = dxmath::Sub(center, offset);
		ep.p1 = dxmath::Add(center, offset);
		return ep;
	}
}