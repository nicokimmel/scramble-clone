#ifndef SCRAMBLE_LASER_H
#define SCRAMBLE_LASER_H

#include "../utils/base.h"

#include "./entity.h"

/**
 * @brief Modellklasse der vom Spieler gefeuerten Laser
 */
class Laser : public Entity {
	private:
		uint _ticks;
	public:
		Laser();
		void update();
		void onCollision(EntityType);
};

#endif //SCRAMBLE_LASER_H