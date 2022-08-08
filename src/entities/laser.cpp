#include "laser.h"

Laser::Laser() {
	_type = EntityType::LASER;
	setSize(Vector2(7, 10));
	setVelocity(Vector2(15, 0));
}

void Laser::update() {
	
}

void Laser::onCollision(std::shared_ptr<Object> collisionPartner) {
	_crashed = true;
}