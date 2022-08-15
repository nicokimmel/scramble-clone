#ifndef SCRAMBLE_OBJECT_H
#define SCRAMBLE_OBJECT_H

#include "../utils/base.h"
#include "../utils/const.h"

#include "../physics/vector2.h"

class Object {
    private:
        Vector2 _size;
		Vector2 _position;
		Vector2 _velocity;
		uint _speed;
		int _rotation;
    public:   
        Vector2 getSize();
		void setSize(Vector2);
		Vector2 getPosition();
		void setPosition(Vector2);
		Vector2 getVelocity();
		void setVelocity(Vector2);
		uint getSpeed();
		void setSpeed(uint);
		int getRotation();
		void setRotation(int);
		virtual void onCollision(std::shared_ptr<Object>) = 0;
};

#endif //SCRAMBLE_OBJECT_H