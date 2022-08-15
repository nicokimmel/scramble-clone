#ifndef SCRAMBLE_PHYSICS_H
#define SCRAMBLE_PHYSICS_H

#include <bits/stdc++.h>
#include <algorithm>
#include "object.h"
#include "world.h"

class Physics {
	private:
        
	public:
		bool checkCollision_Objects(Object *a, Object *b);
        bool checkCollision_World(Object *a, World *b);
        void checkCollision(std::shared_ptr<World>);
        void move(Object *a);
        void move(Object *a, int vx, int vy);
        void fall(Object *a, float gravity, int timestep);
        void rotate(Object *a, float angle, int timestep);
};


#endif //SCRAMBLE_PHYSICS_H