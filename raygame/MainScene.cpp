#include "MainScene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Collider.h"
#include "AABBCollider.h"
#include "Transform2D.h"
#include "Player.h"
#include "Enemy.h"
#include "Spawner.h"
#include "UIText.h"

void MainScene::start()
{
	//Declares player, sets scale and adds Collider
	Player* player = new Player(350, 750, "Player");
	addActor(player);

	//Adds goal
	Actor* goal = new Actor(350, 23, "Goal");
	goal->getTransform()->setScale({ 30, 30 });
	addActor(goal);
	goal->setCollider(new AABBCollider(goal));
	goal->addComponent(new SpriteComponent("Images/VictoryPad.png"));

	Spawner* spawner1 = new Spawner(50, 50, "spawner", player);
	addActor(spawner1); 

}
