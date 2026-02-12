#pragma once
#include "DxLib.h"
#include "Transform.hpp"
#include "DxMath.hpp"
#include "MathUtil.hpp"

struct PlayerMoveInput
{
	float moveX = 0.0f;
	float moveZ = 0.0f;
	bool dodge = false;
	bool sprint = false;
};

class PlayerMove
{
private:
	float m_walkSpeed = 5.5f;
	float m_sprintSpeed = 8.0f;

	float m_dodgeSpeed = 13.0f;
	float m_dodgeTime = 0.25f;
	float m_dodgeTimer = 0.0f;
	bool m_isDodging = false;

	VECTOR m_dodgeDir = VGet(0, 0, 1);

public:
	void Initialize(float walkSpeed, float sprintSpeed, float dodgeSpeed, float dodgeTime) noexcept;

	void Update(
		float deltaTime,
		const PlayerMoveInput& in,
		const VECTOR& cameraForward,
		const VECTOR& cameraRight,
		Transform& ioTransform,
		VECTOR& ioVelocity,
		bool isHitstun
	);

	bool IsDodging() const noexcept { return m_isDodging; }

private:
	void StartDodge(const VECTOR& worldDir) noexcept;
};
