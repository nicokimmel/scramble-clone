#include "rocket.h"

Rocket::Rocket() {
	_type = EntityType::ROCKET;
	setSize(Vector2(28, 72));
}

void Rocket::update() {
	
}

void Rocket::onCollision(std::shared_ptr<Object> collisionPartner) {
	_crashed = true;
}