#ifndef SCRAMBLE_PLAYER_H
#define SCRAMBLE_PLAYER_H

#include "../utils/base.h"

#include <algorithm>

#include "./entity.h"

/**
 * @brief Modellklasse des Spielers
 */
class Player : public Entity {
	private:
		int _lives;
		uint _fuel;
	public:
		Player();
		void update();
		void onCollision(EntityType entityType);
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