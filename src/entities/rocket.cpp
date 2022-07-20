#include "rocket.h"

Rocket::Rocket() {
	_type = EntityType::ROCKET;
	_size = Vector2(28, 64);
	_velocity = Vector2(0, 2);
}

void Rocket::update() {
	if(getPosition().getY() + getSize().getY() > 600) {
		Vector2 vel = getVelocity();
		vel.setY(-2);
		setVelocity(vel);
	} else if(getPosition().getY() < 0) {
		Vector2 vel = getVelocity();
		vel.setY(2);
		setVelocity(vel);
	}
}

void Rocket::onCollision(std::shared_ptr<Entity> collisionPartner) {
	
}