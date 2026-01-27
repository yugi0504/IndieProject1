#pragma once
#include "ICollider.hpp"
#include "ColliderMath.hpp"

class SphereCollider final : public ICollider
{
private:
	// ローカル形状
	float m_localRadius = 0.0f;

	// ワールド反映
	VECTOR m_worldCenter = VGet(0, 0, 0);
	float m_worldradius = 0.0f;

	unsigned int m_debugColor = GetColor(255, 0, 0);

public :
				SphereCollider()						 = default;
	explicit	SphereCollider(float radius)	noexcept : m_localRadius(radius){}

	void		SetLocalRadius(float r)			noexcept { m_localRadius = r; }
	float		GetLocalRadius()				noexcept { return m_localRadius; }

	// ワールド同期
	void		SetWorld	  (const Transform& world)	 override;

	ColliderType GetType()				  const noexcept override { return ColliderType::Sphere; }

	void		Draw()					  const			 override;

	// 衝突計算用の軽量型変換 
	collision::Sphere ToCollisionSphere() const noexcept;

};