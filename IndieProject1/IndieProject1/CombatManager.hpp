#pragma once
#include "Player.hpp"
#include "Enemy.hpp"
#include "ColliderMath.hpp"

class Player;
class Enemy;

namespace combat
{
	void ResolvePlayerVsEnemy(Player& player, Enemy& enemy);
}