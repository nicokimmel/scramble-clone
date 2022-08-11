#include "explosion.h"

Explosion::Explosion() {
	_type = EntityType::EXPLOSION;
	setSize(Vector2(119, 67));
}

void Explosion::update() {
	
}

void Explosion::onCollision(std::shared_ptr<Object> collisionPartner) {
	
}