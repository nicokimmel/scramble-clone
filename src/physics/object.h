#ifndef SCRAMBLE_OBJECT_H
#define SCRAMBLE_OBJECT_H

#include "../utils/vector2.h"

class Object {
    private:
        Vector2 _v;
        Vector2 _pos;
        Vector2 _max;
        Vector2 _min;
        float _rotation;

    public:   
        virtual void setVelocity(Vector2) = 0;
        virtual void setPosition(Vector2) = 0;
        void setMax(Vector2 max);
        void setMin(Vector2 min);
        void setRotation(float rotation);

        virtual Vector2 getVelocity() = 0;
        virtual Vector2 getPosition() = 0;
        Vector2 getMax();
        Vector2 getMin();
        float getRotation();

};

#endif //SCRAMBLE_OBJECT_H