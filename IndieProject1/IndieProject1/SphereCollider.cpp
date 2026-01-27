#include "SphereCollider.hpp"

void SphereCollider::SetWorld(const Transform& world)
{
	m_worldCenter = world.position;
	
	const float s = max(world.scale.x, max(world.scale.y, world.scale.z));

	m_worldradius = m_localRadius * s;
}

collision::Sphere SphereCollider::ToCollisionSphere() const noexcept
{
	collision::Sphere s{};
	s.center = m_worldCenter;
	s.radius = m_worldradius;
	return s;
}

void SphereCollider::Draw() const
{
	DrawSphere3D(m_worldCenter, m_worldradius, 12, m_debugColor, m_debugColor, FALSE);

}