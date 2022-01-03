#pragma once
#include "Actor.h"
class MoveComponent;
class SpriteComponent;

class Enemy :
	public Actor
{
public:
	Enemy(float x, float y, const char* name, const char* type) : Actor(x, y, name) { m_type = type; }

	void start() override;
	void update(float deltaTime) override;
	void onCollision(Actor* other) override;

private:
	MoveComponent* m_moveComponent;
	SpriteComponent* m_spriteComponent;
	const char* m_type;
};

