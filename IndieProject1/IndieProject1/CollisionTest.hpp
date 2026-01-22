#pragma once
#include "ICollider.hpp"
#include "ColliderMath.hpp"
#include "CapsuleCollider.hpp"
#include "SphereCollider.hpp"

namespace collision
{
	bool Test(const ICollider& a, const ICollider& b, HitResult* out = nullptr) noexcept;
}