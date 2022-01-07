#pragma once
#include "Actor.h"
class PowerUp :
	public Actor
{
	void onCollision(Actor* other) override;
};

