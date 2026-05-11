#include "Player.hpp"

void Player::Initialize(int modelHandle, Camera* camera)
{
	m_modelHandle = modelHandle;
	m_camera = camera;

	// Move　詳細追加
	m_move.Initialize(5.5f, 8.0f, 13.0f, 0.25f);

	// Attack 詳細追加
	PlayerAttack::AttackDesc light{};
	light.windup = 0.10f;
	light.active = 0.12f;
	light.recovery = 0.25f;
	light.dmg.damage = 10;
	light.dmg.hitstun = 0.15f;
	light.dmg.invincible = 0.0f;
	light.dmg.impulse = VGet(0, 0, 1);

	PlayerAttack::AttackDesc heavy{};
	heavy.windup = 0.20f;
	heavy.active = 0.14f;
	heavy.recovery = 0.40f;
	heavy.dmg.damage = 30;
	heavy.dmg.hitstun = 0.45f;
	heavy.dmg.invincible = 0.0f;
	heavy.dmg.impulse = VGet(0, 0, 3);

	m_attack.Initialize(light, heavy);

	// コライダー　詳細追加
	m_bodyCollider = std::make_shared<CapsuleCollider>(0.8f, 0.4f);
	AddCollider(m_bodyCollider);

	// カメラ追従
	if (m_camera)
	{
		m_camera->SetTarget(&m_transform);
	}
}

void Player::OnUpdate(float deltaTime)
{
	// Move Input
	PlayerMoveInput moveIn{};
	ReadMoveInput(moveIn);

	// Camera
	VECTOR camF = VGet(0, 0, 1);
	VECTOR camR = VGet(1, 0, 0);
	if (m_camera)
	{
		camF = m_camera->GetMoveForward();
		camR = m_camera->GetMoveRight();
	}
	m_move.Update(deltaTime, moveIn, camF, camR, m_transform, m_velocity, m_status.hitstun);

	// Attack
	if (!m_status.hitstun)
	{
		m_attack.Update(deltaTime, m_transform);
	}

	// Debug
	if (input::KeyTrigger(KEY_INPUT_F1))
	{
		// 切り替え
		m_drawColliderDebug = !m_drawColliderDebug;
	}
}

void Player::OnDraw()
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

	if (m_drawColliderDebug && m_attack.IsActive() && m_attack.GetHitCollider())
	{
		m_attack.GetHitCollider()->Draw();
	}
}

void Player::OnDamaged(const DamageInfo& dmg)
{
	// SE.エフェクト.カメラ揺れなど追加
}

void Player::ReadMoveInput(PlayerMoveInput& out) const noexcept
{
	out.moveX =
		(input::KeyDown(KEY_INPUT_D) ?  1.0f : 0.0f) +
		(input::KeyDown(KEY_INPUT_A) ? -1.0f : 0.0f);

	out.moveZ =
		(input::KeyDown(KEY_INPUT_W) ?  1.0f : 0.0f) +
		(input::KeyDown(KEY_INPUT_S) ? -1.0f : 0.0f);

	out.sprint = input::KeyDown(KEY_INPUT_LSHIFT);

	out.dodge = input::KeyTrigger(KEY_INPUT_SPACE);
}