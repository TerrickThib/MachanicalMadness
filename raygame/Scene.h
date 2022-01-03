#pragma once
#include "Actor.h"

class Scene
{
public:
    Scene();

    bool getStarted() { return m_started; }

    MathLibrary::Matrix3* getWorld();

    void addActor(Actor* actor);
    bool removeActor(int index);

    bool removeActor(Actor* actor);

    virtual void start();

    virtual void checkCollision();

    virtual void update(float deltaTime);

    virtual void draw();

    virtual void debug();

    virtual void end();

    static void destroy(Actor* actor);

private:
    Actor** m_actors;
    MathLibrary::Matrix3* m_world;
    bool m_started;
    int m_actorCount;
};

