#ifndef SCRAMBLE_BUILDING_H
#define SCRAMBLE_BUILDING_H

#include "../utils/base.h"

#include "./entity.h"

/**
 * @brief Modellklasse der nicht interaktiven Gebäude
 */
class Building : public Entity {
	private:
		
	public:
		Building();
		void update();
		void onCollision(std::shared_ptr<Object>);
};

#endif //SCRAMBLE_BUILDING_H