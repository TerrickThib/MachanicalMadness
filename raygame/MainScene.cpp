#include "MainScene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Collider.h"
#include "AABBCollider.h"
#include "Transform2D.h"
#include "Player.h"
#include "Enemy.h"

void MainScene::start()
{
	//Declares player, sets scale and adds Collider
	Player* player = new Player(50, 50, "Player");
	addActor(player);

	//Adds Enemy and Targets the Player
	Enemy* test = new Enemy(500, 50, "Enemy", "Sword");
	addActor(test);
	test->setTarget(player);

	//Adds goal
	Actor* goal = new Actor(50, 500, "Goal");
	addActor(goal);
	goal->setCollider(new AABBCollider(goal));
	goal->addComponent(new SpriteComponent("Images/player.png"));
}
