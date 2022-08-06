#ifndef SCRAMBLE_LASER_H
#define SCRAMBLE_LASER_H

#include "../utils/base.h"

#include <algorithm>
#include <cmath>

#include "./entity.h"
#include "../textures/texture.h"

class Laser : public Entity {
	private:
		uint _ticks;
	public:
		Laser();
		void update();
		void onCollision(std::shared_ptr<Entity>);
};

#endif //SCRAMBLE_LASER_H