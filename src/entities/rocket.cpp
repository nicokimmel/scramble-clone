#include "rocket.h"

Rocket::Rocket() {
	_type = EntityType::ROCKET;
	_size = Vector2(28, 72);
}

void Rocket::update() {
	
}

void Rocket::onCollision(std::shared_ptr<Entity> collisionPartner) {
	
}