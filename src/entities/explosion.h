#ifndef SCRAMBLE_EXPLOSION_H
#define SCRAMBLE_EXPLOSION_H

#include "../utils/base.h"

#include "./entity.h"

enum ExplosionType {
	EDEFAULT = -1,
	EPLAYER = -2
};

class Explosion : public Entity {
	private:
		ExplosionType _explosionType;
		std::map<ExplosionType, Vector2> _explosionList;
	public:
		Explosion(ExplosionType);
		void update();
		void onCollision(std::shared_ptr<Object>);
		int getIdentifier();
		ExplosionType getExplosionType();
};

#endif //SCRAMBLE_EXPLOSION_H