#include "laser.h"

Laser::Laser() {
	_type = EntityType::LASER;
	setSize(Vector2(7, 10));
	setVelocity(Vector2(15, 0));
}

void Laser::update() {
	
}

void Laser::onCollision(std::shared_ptr<Object> collisionPartner) {
	if(collisionPartner == nullptr) {
		_crashed = true;
		return;
	}

	auto entity = std::static_pointer_cast<Entity>(collisionPartner);
	auto entityType = entity->getType();

	if(entityType != EntityType::PLAYER && entityType != EntityType::MISSILE && entityType != EntityType::EXPLOSION) {
		_crashed = true;
	}
}