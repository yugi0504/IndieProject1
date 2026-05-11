#pragma once
#include <memory>

#include "Character.hpp"
#include "CapsuleCollider.hpp"
#include "Damage.hpp"

#include "Input.hpp"

class Enemy final : public Character
{
	// ---------------------------
	// ƒƒ“ƒo[•Ï”
	// ---------------------------

private:
	int m_modelHandle = -1;
	std::shared_ptr<CapsuleCollider> m_bodyCollider;
	bool m_drawColliderDebug = false;

	// ”í’e‰‰o
	float m_damageFlashTimer = 0.0f;
	float m_damageFlashTime = 0.15f;

	// ---------------------------
	// ŠÖ”
	// ---------------------------

public:
	Enemy() = default;
	~Enemy() override = default;

	void Initialize(int modelHandle);

	std::shared_ptr<CapsuleCollider> GetHurtCollider() const noexcept;

protected:
	void OnUpdate(float deltaTime) override;
	void OnDraw() override;
	void OnDamaged(const DamageInfo& dmg) override;
	void OnDead() override;
};
