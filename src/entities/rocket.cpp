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

void Rocket::launch() {
	setVelocity(Vector2(getVelocity().getX(), 3));
}