#include "CombatManager.hpp"

namespace combat
{
	void ResolvePlayerVsEnemy(Player& player, Enemy& enemy)
	{
		auto& atk = player.GetAttack();

		if (!atk.IsActive()) return;
		if (atk.HasHit()) return;

		auto hit = atk.GetHitCollider();
		auto hurt = enemy.GetHurtCollider();

		if (!hit || !hurt) return;

		collision::HitResult hr{};
		if (collision::CapsuleCapsule(hit->ToCollisionCapsule(),hurt->ToCollisionCapsule(),&hr))
		{
			enemy.ApplyDamage(atk.GetDamage());
			atk.MarkHit();
			
		}
	}
}