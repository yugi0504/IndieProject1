#include "PlayerMove.hpp"

void PlayerMove::Initialize(float walkSpeed, float sprintSpeed, float dodgeSpeed, float dodgeTime)
{
	m_walkSpeed = walkSpeed;
	m_sprintSpeed = sprintSpeed;
	m_dodgeSpeed = dodgeSpeed;
	m_dodgeTime = dodgeTime;
}

void PlayerMove::Update(float deltaTime, const PlayerMoveInput& in, 
	const VECTOR& cameraForward, const VECTOR& cameraRight, Transform& ioTransform, VECTOR& ioVelocity, bool isHitstun)
{
	if (isHitstun) return;

	VECTOR f = dxmath::SafeNomalize(dxmath::Horizontal(cameraForward), VGet(0, 0, 1));
	VECTOR r = dxmath::SafeNomalize(dxmath::Horizontal(cameraRight), VGet(1, 0, 0));

	if (m_isDodging)
	{
		m_dodgeTimer += deltaTime;
		ioVelocity = dxmath::Mult(m_dodgeDir, m_dodgeSpeed);

		if (m_dodgeTimer >= m_dodgeTime)
		{
			m_isDodging = false;
			m_dodgeTimer = 0.0f;
			ioVelocity = dxmath::Mult(ioVelocity, 0.2f); // —]‰C
		}
		return;
	}

	VECTOR worldDir = dxmath::Add(dxmath::Mult(r, in.moveX), dxmath::Mult(f, in.moveZ));

	worldDir = dxmath::SafeNomalize(worldDir, VGet(0, 0, 0));
	const bool hasMove = (dxmath::LengthSq(worldDir) > mathutil::EPSILON);

	// ‰ñ”ğs“®
	if (in.dodge && hasMove)
	{
		StartDodge(worldDir);
		ioVelocity = dxmath::Mult(m_dodgeDir, m_dodgeSpeed);
		return;
	}

	// ’ÊíˆÚ“®
	const float  spd = in.sprint ? m_sprintSpeed : m_walkSpeed;
	ioVelocity = dxmath::Mult(worldDir, spd);

	// Œü‚«ˆÚ“®•ûŒü‚ÖYaw‚ğ‡‚í‚¹‚é
	if (hasMove)
	{
		ioTransform.rotate.y = atan2(worldDir.x, worldDir.z);
	}
}

void PlayerMove::StartDodge(const VECTOR& worldDir) noexcept
{
	m_isDodging = true;
	m_dodgeTimer = 0.0f;
	m_dodgeDir = dxmath::SafeNomalize(worldDir, VGet(0, 0, 1));
}