#include "Enemy.hpp"

void Enemy::Initialize(int modelHandle)
{
	m_modelHandle = modelHandle;

	m_bodyCollider = std::make_shared<CapsuleCollider>(1.0f, 0.5f);

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
	// 被弾アクション更新
	if (m_damageFlashTimer > 0.0f)
	{
		m_damageFlashTimer -= deltaTime;
		if (m_damageFlashTimer < 0.0f)
		{
			m_damageFlashTimer = 0.0f;
		}
	}

	if (input::KeyTrigger(KEY_INPUT_F2))
	{
		m_drawColliderDebug = !m_drawColliderDebug;
	}

}

void Enemy::OnDraw()
{
	// 被弾時点滅
	const bool isFlashing = (m_damageFlashTimer > 0.0f);
	const bool skipDraw = isFlashing && (GetNowCount() / 50 % 2 == 0);

	if (m_modelHandle >= 0 && !skipDraw)
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
	// 被弾演出
	m_damageFlashTimer = m_damageFlashTime;

	// 追加予定
	// - 被弾SE
	// - ヒットエフェクト
	// - 被弾モーション

}

void Enemy::OnDead()
{
	m_modelHandle = -1;

	// 追加予定
	// - 死亡演出
	// - 死亡エフェクト
	// - 撃破処理


}



