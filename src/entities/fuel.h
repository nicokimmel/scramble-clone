#ifndef SCRAMBLE_FUEL_H
#define SCRAMBLE_FUEL_H

#include "../utils/base.h"

#include "./entity.h"

/**
 * @brief Modellklasse der Tanks am Boden
 */
class Fuel : public Entity {
	private:
		
	public:
		Fuel();
		void update();
		void onCollision(std::shared_ptr<Object>);
};

#endif //SCRAMBLE_FUEL_H