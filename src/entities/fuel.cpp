#include "fuel.h"

Fuel::Fuel() {
	_type = EntityType::FUEL;
	setSize(Vector2(60, 69));
}

void Fuel::update() {
	
}

void Fuel::onCollision(std::shared_ptr<Object> collisionPartner) {
	_crashed = true;
}