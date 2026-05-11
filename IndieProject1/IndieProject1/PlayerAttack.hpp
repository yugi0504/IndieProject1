#pragma once
#include "memory"
#include "DxLib.h"
#include "Character.hpp"
#include "CapsuleCollider.hpp"
#include "Transform.hpp"
#include "Damage.hpp"

#include "Input.hpp"
#include "DxMath.hpp"
#include "MathUtil.hpp"


class Character;

class PlayerAttack
{
public:
    enum class AttackType { None, Light, Heavy };
    enum class Phase { None, Windup, Active, Recovery };

    struct AttackDesc
    {
        float windup = 0.10f;
        float active = 0.12f;
        float recovery = 0.25f;

        DamageInfo dmg{};

        VECTOR localOffset = VGet(0.0f, 0.9f, 0.9f);
        float halfSegment = 0.35f;
        float radius = 0.25f;
    };

private:
    AttackDesc m_light{};
    AttackDesc m_heavy{};

    AttackType m_type = AttackType::None;
    Phase m_phase = Phase::None;
    float m_timer = 0.0f;

    AttackDesc m_current{};
    DamageInfo m_currentDmg{};

    shared_ptr<CapsuleCollider> m_hitCollider;
    Transform m_hitWorld;

    bool m_hasHit = false;

public :
    void Initialize(const AttackDesc& light, const AttackDesc& heavy);
    void Update(float deltaTime, const Transform& ownerTranceform);

    bool HasHit() const noexcept { return m_hasHit; }
    void MarkHit() noexcept { m_hasHit = true; }

    bool IsAttacking() const noexcept { return m_type != AttackType::None; }
    bool IsActive() const noexcept { return m_phase == Phase::Active; }
    
    AttackType GetType() const noexcept { return m_type; }
    Phase GetPhase() const noexcept { return m_phase; }

    shared_ptr<CapsuleCollider> GetHitCollider() const noexcept { return m_hitCollider; }

    const DamageInfo& GetDamage() const noexcept { return m_currentDmg; }

private:
    void TryStart(AttackType type, const AttackDesc& desc);
    void AdvacePhase(float deltaTime);
    void UpdateHitColliderWorld(const Transform& ownerTr);

    VECTOR LocalToWorldOffset(const Transform& tr, const VECTOR& local) const;
};