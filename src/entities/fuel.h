#ifndef SCRAMBLE_FUEL_H
#define SCRAMBLE_FUEL_H

#include "../utils/base.h"

#include "./entity.h"
#include "../textures/texture.h"

class Fuel : public Entity {
	private:
		
	public:
		Fuel();
		void update();
		void onCollision(std::shared_ptr<Object>);
};

#endif //SCRAMBLE_FUEL_H