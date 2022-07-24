#include "physics.h"


bool Physics::checkCollision_Objects(Object a, Object b) {
    if(a.getMax().getX() < b.getMin().getX() or a.getMin().getX() > b.getMax().getX()) return false;
    if(a.getMax().getY() < b.getMin().getY() or a.getMin().getY() > b.getMax().getY()) return false;

    return true;
}

bool Physics::checkCollision_World(Object a, World b) {


    return true;
}

void Physics::move(Object a) {
    a.setPosition(Vector2(a.getPosition().getX() + a.getVelocity().getX(), a.getPosition().getY() + a.getVelocity().getY()));
    //a.setPosition(a.getPosition().add(a.getVelocity()));
}

void Physics::move(Object a, float vx, float vy) {
    a.setPosition(Vector2(a.getPosition().getX() + a.getVelocity().getX() + vx, a.getPosition().getY() + a.getVelocity().getY() + vy));
}

void Physics::fall(Object a, float gravity, int timestep) {
    a.getPosition().getY() + (a.getVelocity().getY() + gravity * timestep) * timestep;
}

void Physics::rotate(Object a, float angle, int timestep) {
   // a.setRotation(std::min(timestep > 20 ? 120 * ((timestep - 20.0f) / (timestep - 1.0f)) : 0.0f, angle));
}