#include "MainScene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Collider.h"
#include "AABBCollider.h"
#include "Transform2D.h"
#include "Player.h"
#include "Enemy.h"
#include "Spawner.h"

void MainScene::start()
{
	//Declares player, sets scale and adds Collider
	Player* player = new Player(50, 50, "Player");
	addActor(player);

	//Adds Enemy and Targets the Player
	Enemy* test = new Enemy(500, 50, "Enemy", "Sword", player);
	Enemy* test2 = new Enemy(50, 500, "Enemy", "Rusher", player);
	addActor(test);
	addActor(test2);
	test->setTarget(player);
	test2->setTarget(player);

	//Adds goal
	Actor* goal = new Actor(50, 500, "Goal");
	goal->getTransform()->setScale({ 30, 30 });
	addActor(goal);
	goal->setCollider(new AABBCollider(goal));
	goal->addComponent(new SpriteComponent("Images/VictoryPad.png"));

	Spawner* test23 = new Spawner(25, 25, "spawner", player);
	addActor(test23);
}
