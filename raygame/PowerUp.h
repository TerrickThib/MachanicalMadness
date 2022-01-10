#pragma once
#include "SpriteComponent.h"
#include "Actor.h"

class PowerUp :
	public Actor
{
public:
	PowerUp(float x, float y, const char* name = "PowerUp") : Actor(x,y,name) { m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/Powerup.png"))); }
	void onCollision(Actor* other) override;

private:
	SpriteComponent* m_spriteComponent;
};

