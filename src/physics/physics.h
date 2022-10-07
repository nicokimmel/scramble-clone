#ifndef SCRAMBLE_PHYSICS_H
#define SCRAMBLE_PHYSICS_H

#include <bits/stdc++.h>
#include <algorithm>
#include "object.h"
#include "world.h"

class Physics {
	private:
        bool checkCollision_Objects(std::shared_ptr<Object> a, std::shared_ptr<Object>b);
        bool checkCollision_World(std::shared_ptr<Object> a, std::shared_ptr<World> b);
	public:
        void checkCollision(std::shared_ptr<World>);
        void move(std::shared_ptr<Object> a);
        void move(std::shared_ptr<Object> a, int vx, int vy);
};


#endif //SCRAMBLE_PHYSICS_H