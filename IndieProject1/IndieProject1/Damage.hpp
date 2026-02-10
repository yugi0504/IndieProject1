#pragma once
#include "DxLib.h"

struct DamageInfo
{
	int		damage		= 0;
	float	hitstun		= 0.0f;				// ”í’ed’¼(•b)
	float	invincible	= 0.0f;				// –³“G(•b)
	VECTOR	impulse		= VGet(0, 0, 0);	// ƒmƒbƒNƒoƒbƒN
};