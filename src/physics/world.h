#ifndef SCRAMBLE_WORLD_H
#define SCRAMBLE_WORLD_H

#include "object.h"
#include <vector>

class World {
    private:
        int* _worldArray;
    public:   
        virtual int getAlpha(int x, int y) = 0;
        virtual std::vector<std::shared_ptr<Object>> getObjectList() = 0;
};

#endif //SCRAMBLE_WORLD_H