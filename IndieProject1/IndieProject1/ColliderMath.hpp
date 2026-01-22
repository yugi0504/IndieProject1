#pragma once
#include "DxLib.h"
#include "mathutil.hpp"
#include "dxmath.hpp"
#include "Geometry.hpp"

namespace collision
{
	// 衝突情報
	struct HitResult
	{
		bool hit = false;

		// 接触法線(A -> B方向基本)
		VECTOR normal = VGet(0, 1, 0);

		// 貫通深度
		float penetration = 0.0f;

		// Aを押し戻すベクトル
		VECTOR pushOutA = VGet(0, 0, 0);

		// Bを押し戻すベクトル
		VECTOR pushOutB = VGet(0, 0, 0);

		// 接触点
		VECTOR pointA = VGet(0, 0, 0);
		VECTOR pointB = VGet(0, 0, 0);
	};

	// カプセル表現
	struct Capsule
	{
		VECTOR center = VGet(0, 0, 0);
		VECTOR upDir = VGet(0, 1, 0);
		float halfSegment = 0.0f;	// 球中心間線分の半分
		float radius = 0.0f;
	};

	// 球表現
	struct Sphere
	{
		VECTOR center = VGet(0, 0, 0);
		float radius = 0.0f;
	};

	// capsule vs sphere
	bool CapsuleSphere(const Capsule& cap, const Sphere& sph, HitResult* out = nullptr) noexcept;

	// capsule vs capsule
	bool CapsuleCapsule(const Capsule& a, const Capsule& b, HitResult* out = nullptr) noexcept;

	// sphere vs sphere
	bool SphereSphere(const Sphere& a, const Sphere& b, HitResult* out = nullptr) noexcept;
}