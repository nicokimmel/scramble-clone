#ifndef SCRAMBLE_OBJECT_H
#define SCRAMBLE_OBJECT_H

#include "../utils/base.h"
#include "../utils/const.h"

#include "../physics/vector2.h"

class Object {
    private:
        
    public:   
        virtual Vector2 getSize() = 0;
		virtual void setSize(Vector2) = 0;
		virtual Vector2 getPosition() = 0;
		virtual void setPosition(Vector2) = 0;
		virtual Vector2 getVelocity() = 0;
		virtual void setVelocity(Vector2) = 0;
		virtual uint getSpeed() = 0;
		virtual void setSpeed(uint) = 0;
		virtual int getRotation() = 0;
		virtual void setRotation(int) = 0;
		virtual void onCollision(std::shared_ptr<Object>) = 0;
};

#endif //SCRAMBLE_OBJECT_H