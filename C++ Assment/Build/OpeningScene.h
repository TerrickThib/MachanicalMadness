#pragma once
#include "Scene.h"
class OpeningScene :
	public Scene
{
public:
	void start();
	void update(float deltaTime) override;
};


