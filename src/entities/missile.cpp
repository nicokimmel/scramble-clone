#include "missile.h"

Missile::Missile() {
	_type = EntityType::MISSILE;
	_size = Vector2(26, 17);
	_ticks = 1;
}

void Missile::update() {
	_ticks += 1;
	_rotation = std::min(_ticks > 20 ? 120 * ((_ticks - 20.0f) / (_ticks - 1.0f)) : 0.0f, 90.0f);
	
	float xVel = std::max(-1 * std::pow(0.1f * _ticks - 2.0f, 2.0f) + 5, 0.0f);
	float yVel = std::min(_ticks > 30 ? std::pow(0.1f * _ticks - 2.0f, 2.0f) : 0, 5.0f) * -1;
	_velocity = Vector2(xVel, yVel);
	
}

void Missile::onCollision(std::shared_ptr<Entity> collisionPartner) {
	_crashed = true;
}