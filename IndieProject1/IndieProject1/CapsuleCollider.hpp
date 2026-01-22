#pragma once
#include "ICollider.hpp"
#include "ColliderMath.hpp"
#include <algorithm>

class CapsuleCollider final : public ICollider
{
private:
	float m_localHalfSegment = 0.0f;
	float m_localRadius = 0.0f;

	VECTOR m_worldCenter = VGet(0, 0, 0);
	VECTOR m_worldUpDir = VGet(0, 1, 0);
	float m_worldHalfSegment = 0.0f;
	float m_worldRadius = 0.0f;

	unsigned int m_debugColor = GetColor(255, 255, 0);

public :
	CapsuleCollider() = default;
	explicit CapsuleCollider(float halfSegment,float radius) noexcept
		:m_localHalfSegment(halfSegment),m_localRadius(radius){}

	void SetLocalHarfSegment(float halfSegment) noexcept { m_localHalfSegment = halfSegment; }
	void SetLocalRadius(float radius) noexcept { m_localRadius = radius; }

	float GetLocalHalfSegment() const noexcept { return m_localHalfSegment; }
	float GetLocalRadius() const noexcept { return m_localRadius; }

	void SetWorld(const Transform& world) override;

	ColliderType GetType() const noexcept override { return ColliderType::Capsule; }
	void Draw() const override;

	collision::Capsule ToCollisionCapsule() const noexcept;


};