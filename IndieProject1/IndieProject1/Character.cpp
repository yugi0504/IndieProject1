#include "Character.hpp"

void Character::Update(float deltaTime)
{
	// タイマー更新
	UpdateTimers(deltaTime);

	// 死亡チェック
	if (m_status.IsDead())
	{
		if (!m_deadNotified)
		{
			m_deadNotified = true;
			OnDead();
		}
		SyncCollidersToWorld();
		return;
	}

	// 硬直中の意思決定の停止
	if (!m_status.hitstun)
	{
		OnUpdate(deltaTime);
	}

	// 移動反映
	Integrate(deltaTime);

	// コライダーのワールド同期
	SyncCollidersToWorld();

	// Update中死亡時の死亡通知
	if (m_status.IsDead() && !m_deadNotified)
	{
		m_deadNotified = true;
		OnDead();
	}
}

void Character::Draw()
{

}

bool Character::ApplyDamage(const DamageInfo& dmg)
{
	if (m_status.IsDead()) return false;
	if (m_status.invincible) return false;

	m_status.hp -= dmg.damage;
	if (m_status.hp < 0) m_status.hp = 0;

	if (dmg.hitstun > 0.0f)
	{
		m_status.hitstun = true;
		m_status.hitstunTime = dmg.hitstun;
		m_status.hitstunTimer = 0.0f;
	}

	if (dmg.invincible > 0.0f)
	{
		m_status.invincible = true;
		m_status.invincibleTime = dmg.invincible;
		m_status.invincibleTimer = 0.0f;
	}

	m_velocity = dxmath::Add(m_velocity, dmg.impulse);

	OnDamaged(dmg);
	return true;
}

void Character::AddCollider(const shared_ptr<ICollider>& col) noexcept
{
	if (!col) return;
	m_colliders.push_back(col);
	SyncCollidersToWorld();
}

void Character::UpdateTimers(float deltaTime) noexcept
{
	if (m_status.invincible)
	{
		m_status.hitstunTimer += deltaTime;
		if (m_status.invincibleTimer >= m_status.invincibleTime)
		{
			m_status.invincible = false;
			m_status.invincibleTimer = 0.0f;
			m_status.invincibleTime = 0.0f;
		}
	}

	if (m_status.hitstun)
	{
		m_status.hitstunTimer += deltaTime;
		if (m_status.hitstunTimer >= m_status.hitstunTime)
		{
			m_status.hitstun = false;
			m_status.hitstunTimer = 0.0f;
			m_status.hitstunTime = 0.0f;
		}
	}
}

void Character::SyncCollidersToWorld() noexcept
{
	for (auto& col : m_colliders)
	{
		if (!col) continue;

		col->SetWorld(m_transform);
	}
}

void Character::Integrate(float deltaTime) 
{
	m_transform.position = dxmath::Add(m_transform.position, dxmath::Mult(m_velocity, deltaTime));

	m_velocity = dxmath::Mult(m_velocity, 0.9f);
}

