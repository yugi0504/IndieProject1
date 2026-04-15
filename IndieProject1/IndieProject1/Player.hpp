#pragma once
#include "memory"

#include "Character.hpp"
#include "Transform.hpp"
#include "CapsuleCollider.hpp"

#include "Camera.hpp"
#include "Input.hpp"

#include "PlayerMove.hpp"
#include "PlayerAttack.hpp"

class Player final : public Character
{
	// --------------------
	// ÉÅÉìÉoÅ[ïœêî
	// --------------------

private:
	char* m_handleName;
	int m_modelHandle = -1;

	Camera* m_camera = nullptr;

	PlayerMove m_move;
	PlayerAttack m_attack;

	shared_ptr<CapsuleCollider> m_bodyCollider;

	bool m_drawColliderDebug = false;

	// --------------------
	// ä÷êî
	// --------------------

public:
	Player() = default;
	~Player() override = default;

	void Initialize(int modelHandle, Camera* camera);

protected:
	void OnUpdate(float deltaTime) override;
	void OnDraw() override;
	void OnDamaged(const DamageInfo& dmg) override;

private:
	void ReadMoveInput(PlayerMoveInput& out) const noexcept;

};
