#ifndef SCRAMBLE_BUILDING_H
#define SCRAMBLE_BUILDING_H

#include "../utils/base.h"

#include "./entity.h"

class Building : public Entity {
	private:
		uint _ticks;
	public:
		Building();
		void update();
		void onCollision(std::shared_ptr<Object>);
};

#endif //SCRAMBLE_BUILDING_H