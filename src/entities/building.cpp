#include "building.h"

Building::Building() {
	_type = EntityType::BUILDING;
	setSize(Vector2(60, 69));
}

void Building::update() {
	
}

void Building::onCollision(std::shared_ptr<Object> collisionPartner) {
	_crashed = true;
}