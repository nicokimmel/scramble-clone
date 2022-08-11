#include "explosion.h"

Explosion::Explosion(ExplosionType explosionType) {
	_type = EntityType::EXPLOSION;
	_explosionType = explosionType;
	_explosionList = {
		{ExplosionType::EDEFAULT, Vector2(66, 68)},
		{ExplosionType::EPLAYER, Vector2(119, 67)},
	};
	
	setSize(_explosionList[explosionType]);
}

void Explosion::update() {
	
}

void Explosion::onCollision(std::shared_ptr<Object> collisionPartner) {
	
}

int Explosion::getIdentifier() {
	return _explosionType;
}

ExplosionType Explosion::getExplosionType() {
	return _explosionType;
}