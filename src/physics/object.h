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
        void setVelocity(Vector2);
        void setPosition(Vector2);
        void setMax(Vector2 max);
        void setMin(Vector2 min);
        void setRotation(float rotation);

        Vector2 getVelocity();
        Vector2 getPosition();
        Vector2 getMax();
        Vector2 getMin();
        float getRotation();

};

#endif //SCRAMBLE_OBJECT_H