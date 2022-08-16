#ifndef SCRAMBLE_EXPLOSION_H
#define SCRAMBLE_EXPLOSION_H

#include "../utils/base.h"

#include "./entity.h"

/**
 * @brief Arten der Explosionen
 * @details Der Spieler hat eine andere Explosion
 * 			als andere Objekte.
 */
enum ExplosionType {
	EDEFAULT = -1,
	EPLAYER = -2
};

/**
 * @brief Modellklasse der durch Kollision entstehenden Explosionen
 */
class Explosion : public Entity {
	private:
		ExplosionType _explosionType;
		std::map<ExplosionType, Vector2> _explosionList;
	public:
		Explosion(ExplosionType);
		void update();
		void onCollision(EntityType);
		int getIdentifier();
		ExplosionType getExplosionType();
};

#endif //SCRAMBLE_EXPLOSION_H