#pragma once
#include "Component.h"
#include "Collider.h"
class CollisionComponent :
	public Component
{
public:
	AABBCollider getCollider() { return m_AABBCollider; }
private:
	Collider* m_collider;
};

