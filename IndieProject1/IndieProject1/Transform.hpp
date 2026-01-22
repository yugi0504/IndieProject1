#pragma once
#include "DxLib.h"

struct Transform
{
	VECTOR position	= VGet(0, 0, 0);
	VECTOR rotate	= VGet(0, 0, 0);
	VECTOR scale	= VGet(1, 1, 1);
};