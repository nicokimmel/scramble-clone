#ifndef SCRAMBLE_MISSILE_H
#define SCRAMBLE_MISSILE_H

#include "../utils/base.h"

#include <algorithm>
#include <cmath>

#include "./entity.h"

/**
 * @brief Modellklasse der vom Spieler gefeuerten Raketen
 */
class Missile : public Entity {
	private:
		uint _ticks;
	public:
		Missile();
		void update();
		void onCollision(std::shared_ptr<Object>);
};

#endif //SCRAMBLE_MISSILE_H