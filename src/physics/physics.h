#ifndef SCRAMBLE_PHYSICS_H
#define SCRAMBLE_PHYSICS_H

#include <bits/stdc++.h>
#include <algorithm>
#include "object.h"
#include "world.h"

//#include "../events/eventmanager.h"
//#include "../levels/levelmanager.h"

class Physics {
	private:
        
	public:
        //std::shared_ptr<EventManager> _eventManager;
		bool checkCollision_Objects(Object *a, Object *b);
        bool checkCollision_World(Object *a, World *b);
        void checkCollision(std::vector<std::shared_ptr<Object>>, std::vector<std::shared_ptr<Object>>, std::shared_ptr<World>);
        void checkCollision2(std::vector<std::shared_ptr<Object>>, std::shared_ptr<World>);
        void move(Object *a);
        void move(Object *a, int vx, int vy);
        void fall(Object *a, float gravity, int timestep);
        void rotate(Object *a, float angle, int timestep);
};


#endif //SCRAMBLE_PHYSICS_H