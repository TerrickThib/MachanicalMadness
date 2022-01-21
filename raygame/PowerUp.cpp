#include "PowerUp.h"
#include "Player.h"
#include "Engine.h"

void PowerUp::onCollision(Actor* other)
{
	//If you are the player 
	if (other->getName() == "Player")
	{
		Player* player = (Player*)other;
		player->resetPowerUp();//Resets if player has Power up
		player->setHasPowerUp(true);//Sets player to have power up
		Engine::destroy(this);//Deletes this power up from screen
	}
}

void PowerUp::update(float deltaTime)
{
	m_timer += deltaTime;
	if (m_timer >= 5)
	{
		m_spriteComponent->~SpriteComponent();
		m_spriteComponent = nullptr;
		Engine::destroy(this);
	}
}
