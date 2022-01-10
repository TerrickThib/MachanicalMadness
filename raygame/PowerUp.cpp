#include "PowerUp.h"
#include "Player.h"
#include "Engine.h"

void PowerUp::onCollision(Actor* other)
{
	if (other->getName() == "Player")
	{
		Player* player = (Player*)other;
		player->resetPowerUp();
		player->setHasPowerUp(true);
		Engine::destroy(this);
	}
}
