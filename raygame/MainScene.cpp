#include "MainScene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Collider.h"
#include "AABBCollider.h"
#include "Transform2D.h"
#include "Player.h"

void MainScene::start()
{
	//Declares player, sets scale and adds Collider
	Player* player = new Player(50, 50, "Player");	
	player->getTransform()->setScale({ 50,50 });
	player->setCollider(new AABBCollider(player));
	addActor(player);

	//Adds goal
	Actor* goal = new Actor(50, 500, "Goal");
	addActor(goal);
	goal->setCollider(new AABBCollider(goal));
	goal->addComponent(new SpriteComponent("Images/player.png"));
}
