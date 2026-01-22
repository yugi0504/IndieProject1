#include "CapsuleCollider.hpp"

void CapsuleCollider::SetWorld(const Transform& world)
{
	m_worldCenter = world.position;
	m_worldUpDir = dxmath::UpFromEulerXYZ(world.rotate);

	const float s = max(max(world.scale.x, world.scale.y), world.scale.z);
}

collision::Capsule CapsuleCollider::ToCollisionCapsule() const noexcept
{
	collision::Capsule c{};
	c.center = m_worldCenter;
	c.upDir = m_worldUpDir;
	c.halfSegment = m_worldHalfSegment;
	c.radius = m_worldRadius;
	return c;
}

void CapsuleCollider::Draw() const
{
	const auto ep = geometry::CalcCapsuleEndpoints(m_worldCenter, m_worldUpDir, m_worldHalfSegment);

	DrawCapsule3D(ep.p0, ep.p1, m_worldRadius, 12, m_debugColor, m_debugColor, FALSE);
}