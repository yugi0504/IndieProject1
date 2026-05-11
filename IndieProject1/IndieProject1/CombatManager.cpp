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
			DamageInfo dmg = atk.GetDamage();

			// 接触法線方向にノックバック
			dmg.impulse = dxmath::Mult(hr.normal, 4.0f);

			enemy.ApplyDamage(dmg);
			atk.MarkHit();
		}
	}
}