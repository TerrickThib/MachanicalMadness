#include "Spawner.h"
#include "Engine.h"
#include "Enemy.h"
#include "Transform2D.h"


Spawner::Spawner(float x, float y, const char* name)
{
}

Spawner::~Spawner()
{
}

void Spawner::update(float deltaTime)
{
	m_timesincelastSpawn += deltaTime;

	if (m_numberofenemies < 10 && m_timesincelastSpawn > m_spawnCooldown)
	{
		m_enemyspawn = new Enemy(10, 10, "Taco", "RUsher");
		m_enemyspawn->getTransform()->setScale({ 50,50 });

		Engine::getCurrentScene()->addActor(m_enemyspawn);
			m_numberofenemies++;
			m_timesincelastSpawn = 0;			
	}
}
