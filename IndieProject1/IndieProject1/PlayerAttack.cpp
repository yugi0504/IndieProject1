#include "PlayerAttack.hpp"

void PlayerAttack::Initialize(const AttackDesc& light, const AttackDesc& heavy)
{
    m_light = light;
    m_heavy = heavy;

    m_hitCollider = make_shared<CapsuleCollider>(0.1f, 0.1f);
}

void PlayerAttack::Update(float deltaTime, Character& owner)
{
    if (m_type == AttackType::None)
    {

    }
}