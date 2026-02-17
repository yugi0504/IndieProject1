#include "PlayerAttack.hpp"

void PlayerAttack::Initialize(const AttackDesc& light, const AttackDesc& heavy)
{
    m_light = light;
    m_heavy = heavy;

    m_hitCollider = make_shared<CapsuleCollider>(0.1f, 0.1f);
}

void PlayerAttack::Update(float deltaTime, Character& owner)
{
    // 攻撃
    if (m_type == AttackType::None)
    {
        // キーコンフィグ
        if (input::KeyTrigger(KEY_INPUT_E))
        {
            TryStart(AttackType::Light, m_light);
        }
        else if (input::KeyTrigger(KEY_INPUT_Q))
        {
            TryStart(AttackType::Heavy, m_heavy);
        }
    }

    if (m_type == AttackType::None) return;

    AdvacePhase(deltaTime);

    // Active中のみ当たり判定を更新
    if (m_phase == Phase::Active)
    {
        UpdateHitColliderWorld(owner.GetTransform());
        m_hitCollider->SetWorld(m_hitWorld);
    }
}

void PlayerAttack::TryStart(AttackType type, const AttackDesc& desc)
{
    m_type = type;
    m_phase = Phase::Windup;
    m_current = desc;
    m_currentDmg = desc.dmg;

    m_hitCollider = make_shared<CapsuleCollider>(desc.halfSegment, desc.radius);
}

void PlayerAttack::AdvacePhase(float deltaTime)
{
    m_timer = deltaTime;

    switch (m_phase)
    {
    case Phase::Windup:
        if (m_timer >= m_current.windup)
        {
            m_phase = Phase::Active;
            m_timer = 0.0f;
        }
        break;

    case Phase::Active:
        if (m_timer >= m_current.active)
        {
            m_phase = Phase::Recovery;
            m_timer = 0.0f;
        }
        break;
    case Phase::Recovery:
        if (m_timer >= m_current.recovery)
        {
            m_phase = Phase::None;
            m_type = AttackType::None;
            m_timer = 0.0f;
        }
        break;

    default:
        break;
    }
}

void PlayerAttack::UpdateHitColliderWorld(const Transform& ownerTr)
{
    m_hitWorld = ownerTr;

    const VECTOR wOff = LocalToWorldOffset(ownerTr, m_current.localOffset);
    m_hitWorld.position = dxmath::Add(ownerTr.position, wOff);
}

VECTOR PlayerAttack::LocalToWorldOffset(const Transform& tr, const VECTOR& local) const
{
    const VECTOR right = dxmath::RightFromEulerXYZ(tr.rotate);
    const VECTOR up = dxmath::UpFromEulerXYZ(tr.rotate);
    const VECTOR forward = dxmath::ForwardFromEulerXYZ(tr.rotate);

    VECTOR w = VGet(0, 0, 0);
    w = dxmath::Add(w, dxmath::Mult(right, local.x));
    w = dxmath::Add(w, dxmath::Mult(up, local.y));
    w = dxmath::Add(w, dxmath::Mult(forward, local.z));

    return w;
}

