#ifndef SCRAMBLE_SKY_H
#define SCRAMBLE_SKY_H

#include "../utils/base.h"

#include "./entity.h"

/**
 * @brief Modellklasse für den Sternenhimmel
 */
class Sky : public Entity {
	private:
		
	public:
		Sky();
		void update();
		void onCollision(EntityType);
};

#endif //SCRAMBLE_SKY_H