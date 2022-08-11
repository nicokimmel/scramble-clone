#ifndef SCRAMBLE_PLAYER_H
#define SCRAMBLE_PLAYER_H

#include "../utils/base.h"

#include <algorithm>
#include <cmath>

#include "./entity.h"
#include "../events/eventdata.h"
#include "../textures/texture.h"

class Player : public Entity {
	private:
		int _lives;
		uint _fuel;
	public:
		Player();
		void update();
		void onCollision(std::shared_ptr<Object>);
		void onFuel();
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		int getLives();
		void setLives(int);
		uint getFuel();
		void setFuel(uint);
		void addFuel(uint);
};

#endif //SCRAMBLE_PLAYER_H