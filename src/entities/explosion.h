#ifndef SCRAMBLE_EXPLOSION_H
#define SCRAMBLE_EXPLOSION_H

#include "../utils/base.h"

#include "./entity.h"

class Explosion : public Entity {
	private:
		
	public:
		Explosion();
		void update();
		void onCollision(std::shared_ptr<Object>);
};

#endif //SCRAMBLE_EXPLOSION_H