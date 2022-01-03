#pragma once
#include "Actor.h"

class Bullet : public Actor
{
public:
	Bullet(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, MathLibrary::Vector2 velocity);
	void update(float deltaTime) override;
	void onCollision(Actor* other) override;
};

