#ifndef SCRAMBLE_WORLD_H
#define SCRAMBLE_WORLD_H

class World {
    private:
        int* _worldArray;

    public:   
        virtual int getAlpha(int x, int y) = 0;

};

#endif //SCRAMBLE_WORLD_H