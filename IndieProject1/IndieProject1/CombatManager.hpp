#pragma once

#include "Player.hpp"
#include "Enemy.hpp"

class Player;
class Enemy;

namespace combat
{
	void ResolvePlayerVsEnemy(Player& player, Enemy& enemy);
}