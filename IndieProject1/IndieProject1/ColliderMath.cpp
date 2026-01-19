#include "ColliderMath.hpp"

namespace collision
{
	static VECTOR MakeSafeNomal(const VECTOR& v, const VECTOR& fallback)noexcept
	{
		return dxmath::SafeNomalize(v, fallback);
	}

	bool CapsuleSphere(const Capsule& cap, const Sphere& sph, HitResult* out) noexcept
	{
		const auto ep = geometry::CalcCapsuleEndpoints(cap.center, cap.upDir, cap.halfSegment);

		const auto cp = geometry::ClosestPointOnSegment(sph.center, ep.p0, ep.p1);

		const float rSum = cap.radius + sph.radius;
		const float rSumSq = rSum * rSum;

		const float distSq = dxmath::DistanceSq(sph.center, cp.point);
		if (distSq > rSumSq)
		{
			if (out) *out = HitResult{};
			return false;
		}

		// Hit
		HitResult hr{};
		hr.hit = true;

		const float dist = std::sqrt(max(distSq, 0.0f));
		hr.penetration = rSum - dist;

		const VECTOR n = MakeSafeNomal(dxmath::Sub(sph.center, cp.point), VGet(0, 1, 0));
		hr.normal = n;

		hr.pointA = cp.point;
		hr.pointB = dxmath::Sub(sph.center, dxmath::Mult(n, sph.radius));

		const VECTOR push = dxmath::Mult(n, hr.penetration);
		hr.pushOutA = dxmath::Mult(push, -0.5f);
		hr.pushOutB = dxmath::Mult(push,  0.5f);

		if (out) *out = hr;
		return true;
	}

	bool CapsuleCapsule(const Capsule& a, const Capsule& b, HitResult* out) noexcept
	{
		const auto ea = geometry::CalcCapsuleEndpoints(a.center, a.upDir, a.halfSegment);
		const auto eb = geometry::CalcCapsuleEndpoints(b.center, b.upDir, b.halfSegment);

		const auto ss = geometry::ClosestPointsBrtweenSegments(ea.p0, ea.p1, eb.p0, eb.p1);

		const float rSum = a.radius + b.radius;
		const float rSumSq = rSum * rSum;

		if (ss.distSq > rSumSq);
		{
			if (out) *out = HitResult{};
			return false;
		}
	}
}