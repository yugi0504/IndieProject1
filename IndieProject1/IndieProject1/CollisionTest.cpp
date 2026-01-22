#include "CollisionTest.hpp"

namespace collision
{
	// îΩì]
	static HitResult InvertHit(const HitResult& src) noexcept
	{
		HitResult h = src;

		// A <-> B ÇîΩì] 
		h.normal = dxmath::Mult(src.normal, -1.0f);
		std::swap(h.pushOutA, h.pushOutB);
		std::swap(h.pointA, h.pointB);

		return h;
	}

	bool Test(const ICollider& a, const ICollider& b, HitResult* out) noexcept
	{
		const ColliderType ta = a.GetType();
		const ColliderType tb = b.GetType();

		// sphere vs sphere
		if (ta == ColliderType::Sphere && tb == ColliderType::Sphere)
		{
			const auto& sa = static_cast<const SphereCollider&>(a);
			const auto& sb = static_cast<const SphereCollider&>(b);

			HitResult hr;
			const bool hit = SphereSphere(sa.ToCollisionSphere(), sb.ToCollisionSphere(), out ? &hr : nullptr);

			if (out) *out = hit ? hr : HitResult{};
			return hit;
		}

		// Capsule vs Capsule
		if (ta == ColliderType::Capsule && tb == ColliderType::Capsule)
		{
			const auto& ca = static_cast<const CapsuleCollider&>(a);
			const auto& cb = static_cast<const CapsuleCollider&>(b);

			HitResult hr;
			const bool hit = CapsuleCapsule(ca.ToCollisionCapsule(), cb.ToCollisionCapsule(), out ? &hr : nullptr);

			if (out) *out = hit ? hr : HitResult{};
			return hit;
		}

		// Capsule vs Sphere
		if (ta == ColliderType::Capsule && tb == ColliderType::Sphere)
		{
			const auto& ca = static_cast<const CapsuleCollider&>(a);
			const auto& sb = static_cast<const SphereCollider&>(b);

			HitResult hr;
			const bool hit = CapsuleSphere(ca.ToCollisionCapsule(), sb.ToCollisionSphere(), out ? &hr : nullptr);

			if (out) *out = hit ? hr : HitResult{};
			return hit;
		}

		// Sphere vs CapsuleÅ@(èáèòãtÇ»ÇÃÇ≈îΩì])
		if (ta == ColliderType::Sphere && tb == ColliderType::Capsule)
		{
			const auto& sa = static_cast<const SphereCollider&>(a);
			const auto& cb = static_cast<const CapsuleCollider&>(b);

			HitResult hr;
			const bool hit = CapsuleSphere(cb.ToCollisionCapsule(), sa.ToCollisionSphere(), out ? &hr : nullptr);

			// îΩì]
			if (out)
			{
				*out = hit ? InvertHit(hr) : HitResult{};
			}

			return hit;
		}

		// ñ¢é¿ëïïîï™
		// AABB Ç∆Ç©Å@OBBÇ∆Ç©Å@ÉÅÉbÉVÉÖÇ∆Ç©Å@ÇÃÇøÇ…é¿ëï

		if (out) *out = HitResult{};
		return false;
	}
}