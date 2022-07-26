#include "fuel.h"

Fuel::Fuel() {
	_type = EntityType::FUEL;
	_size = Vector2(60, 69);
}

void Fuel::update() {
	
}

void Fuel::onCollision(std::shared_ptr<Entity> collisionPartner) {
	
}