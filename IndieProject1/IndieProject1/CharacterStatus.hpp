#pragma once

struct CharacterStatus
{
	int hp = 100;
	int maxHp = 100;

	bool invincible = false;
	float invincibleTime = 0.0f;
	float invincibleTimer = 0.0f;

	bool hitstun = false;
	float hitstunTime = 0.0f;
	float hitstunTimer = 0.0f;

	bool IsDead() const { return hp <= 0; }

	void ResetTimers()
	{
		invincible = false;
		invincibleTime = invincibleTimer = 0.0f;
		hitstun = false;
		hitstunTime = hitstunTimer = 0.0f;
	}
};