#include "Spawner.h"
#include "Engine.h"
#include "Enemy.h"
#include "Transform2D.h"
#include "Player.h"

void Spawner::update(float deltaTime)
{
	m_timesincelastSpawn += deltaTime;

	if (m_numberofenemies < 20  && m_timesincelastSpawn > m_spawnCooldown)
	{
		//Declares the enemy that wil be spawned
			m_enemyspawn = new Enemy(50, 100, "Enemy", "Rusher", Spawner::m_currentplayer);
			m_enemyspawn->getTransform()->setScale({ 50,50 });

			//Adds that enemy to the game
			Engine::getCurrentScene()->addActor(m_enemyspawn);
			m_numberofenemies++;//Adds to the number of enemys
			m_timesincelastSpawn = 0;//resets the time since last spawn	

			//Declares the enemy that wil be spawned
			m_enemyspawn = new Enemy(750, 100, "Enemy", "Sword", Spawner::m_currentplayer);
			m_enemyspawn->getTransform()->setScale({ 50,50 });

			//Adds that enemy to the game
			Engine::getCurrentScene()->addActor(m_enemyspawn);
			m_numberofenemies++;//Adds to the number of enemys
			m_timesincelastSpawn = 0;//resets the time since last spawn	

		   
	}
}
