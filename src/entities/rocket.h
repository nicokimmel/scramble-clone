#ifndef SCRAMBLE_ROCKET_H
#define SCRAMBLE_ROCKET_H

#include "../utils/base.h"

#include "./entity.h"

/**
 * @brief Modellklasse für aufsteigende Raketen
 */
class Rocket : public Entity {
	private:
		
	public:
		Rocket();
		void update();
		void onCollision(std::shared_ptr<Object>);
		void launch();
};

#endif //SCRAMBLE_ROCKET_H