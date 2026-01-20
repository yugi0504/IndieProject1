#pragma once
#include "DxLib.h"

class Character
{
	virtual ~Character() = default;

	virtual void Update(float deltaTime) = 0;
};