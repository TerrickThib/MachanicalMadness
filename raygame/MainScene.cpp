#include "MainScene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Transform2D.h"
#include "Player.h"

void MainScene::start()
{
	//Declares player and sets scale
	Player* player = new Player(50, 50, "Player");	
	player->getTransform()->setScale({ 50,50 });
	addActor(player);

}
