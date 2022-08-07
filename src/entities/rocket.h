#ifndef SCRAMBLE_ROCKET_H
#define SCRAMBLE_ROCKET_H

#include "../utils/base.h"

#include "./entity.h"
#include "../textures/texture.h"

class Rocket : public Entity {
	private:
		
	public:
		Rocket();
		void update();
		void onCollision(std::shared_ptr<Entity>);
		void launch();
};

#endif //SCRAMBLE_ROCKET_H