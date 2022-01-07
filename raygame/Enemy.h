#pragma once
#include "Actor.h"
class MoveComponent;
class SpriteComponent;

class Enemy :
	public Actor
{
public:
	Enemy(float x, float y, const char* name, const char* type, Actor* target) : Actor(x, y, name) { m_type = type; m_target = target; }
	~Enemy();

	void start() override;
	void update(float deltaTime) override;
	void onCollision(Actor* other) override;
	void draw() override;

	void setTarget(Actor* target) { m_target = target; }
private:
	MoveComponent* m_moveComponent;
	SpriteComponent* m_spriteComponent;
	const char* m_type;
	Actor* m_target;
};

