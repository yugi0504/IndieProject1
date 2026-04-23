#include "Enemy.hpp"

void Enemy::Initialize(int modelHandle)
{
	m_modelHandle = modelHandle;

	m_bodyCollider = make_shared<CapsuleCollider>(1.0f, 0.5f);

	AddCollider(m_bodyCollider);

	m_status.hp = 300;
	m_status.maxHp = 300;

}

std::shared_ptr<CapsuleCollider> Enemy::GetHurtCollider() const noexcept
{
	return m_bodyCollider;
}

void Enemy::OnUpdate(float deltaTime)
{
	

	if (input::KeyTrigger(KEY_INPUT_F2))
	{
		m_drawColliderDebug = !m_drawColliderDebug;
	}

}

void Enemy::OnDraw()
{
	if (m_modelHandle >= 0)
	{
		MV1SetPosition(m_modelHandle, m_transform.position);
		MV1SetRotationXYZ(m_modelHandle, m_transform.rotate);
		MV1DrawModel(m_modelHandle);
	}

	if (m_drawColliderDebug && m_bodyCollider)
	{
		m_bodyCollider->Draw();
	}
}

void Enemy::OnDamaged(const DamageInfo& dmg)
{

}

void Enemy::OnDead()
{

}



