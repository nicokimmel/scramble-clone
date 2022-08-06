#include "laser.h"

Laser::Laser() {
	_type = EntityType::LASER;
	_size = Vector2(7, 10);
	_velocity = Vector2(15, 0);
}

void Laser::update() {
	
}

void Laser::onCollision(std::shared_ptr<Entity> collisionPartner) {
	_crashed = true;
}