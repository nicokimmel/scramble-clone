#include "physics.h"


bool Physics::checkCollision_Objects(Object *a, Object *b) {
    if(a->getMax().getX() < b->getMin().getX() or a->getMin().getX() > b->getMax().getX()) return false;
    if(a->getMax().getY() < b->getMin().getY() or a->getMin().getY() > b->getMax().getY()) return false;

    return true;
}

bool Physics::checkCollision_World(Object *a, World *b) {
    if(b->getLevelAlpha(a->getMin().getX(), a->getMin().getY()) == 255) return true;
    if(b->getLevelAlpha(a->getMin().getX(), a->getMax().getY()) == 255) return true;
    if(b->getLevelAlpha(a->getMax().getX(), a->getMin().getY()) == 255) return true;
    if(b->getLevelAlpha(a->getMax().getX(), a->getMax().getY()) == 255) return true;
    
    return false;
}

void Physics::move(Object *a) {
    a->setPosition(Vector2(a->getPosition().getX() + a->getVelocity().getX(), a->getPosition().getY() + a->getVelocity().getY()));
}

/*
void Physics::accelerate(Object *a, float vx, float vy) {
    a->setVelocity(Vector2(a->getVelocity().getX() + vx, a->getVelocity().getY() + vy));
    a->setPosition(Vector2(a->getPosition().getX() + a->getVelocity().getX(), a->getPosition().getY() + a->getVelocity().getY()));
}

void Physics::fall(Object *a, float gravity, int timestep) {
    a->getPosition().getY() + (a->getVelocity().getY() + gravity * timestep) * timestep;
}

void Physics::rotate(Object *a, float angle, int timestep) {
    a->setRotation(timestep > 20 ? angle * ((timestep - 20.0f) / (timestep - 1.0f)) : 0.0f);
}
*/