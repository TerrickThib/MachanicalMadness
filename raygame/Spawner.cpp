#include "Spawner.h"
#include "Engine.h"
#include "Enemy.h"
#include "Transform2D.h"
#include "Player.h"

void Spawner::update(float deltaTime)
{
	m_timesincelastSpawn += deltaTime;

	if (m_numberofenemies < 10 && m_timesincelastSpawn > m_spawnCooldown)
	{
		//Declares the enemy that wil be spawned
			m_enemyspawn = new Enemy(10, 10, "Taco", "Rusher", Spawner::m_currentplayer);
			m_enemyspawn->getTransform()->setScale({ 50,50 });

			//Adds that enemy to the game
			Engine::getCurrentScene()->addActor(m_enemyspawn);
			m_numberofenemies++;//Adds to the number of enemys
			m_timesincelastSpawn = 0;//resets the time since last spawn	

			int randomNumber;
			for (int index = 0; index < 10; index++)
			{
				randomNumber = (rand() % 35) + 1;
			}			
		   
	}
}
