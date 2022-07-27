#ifndef SCRAMBLE_PLAYER_H
#define SCRAMBLE_PLAYER_H

#include "../utils/base.h"

#include "./entity.h"
#include "../events/eventdata.h"
#include "../textures/texture.h"

class Player : public Entity {
	private:
		int _lives;
	public:
		Player();
		void update();
		void onCollision(std::shared_ptr<Entity>);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		int getLives();
		void setLives(int);
};

#endif //SCRAMBLE_PLAYER_H