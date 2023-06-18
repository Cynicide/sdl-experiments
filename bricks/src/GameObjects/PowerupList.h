# pragma once
#include <Powerup.h>
#include <SpriteManager.h>

class PowerupList {
    public:

        PowerupList(SpriteManager* spriteManager);
        ~PowerupList();
        void add(float x, float y, int parentWidth);
        void remove(int index);
        void clear();
        Powerup* get(int index);
        void update(double dt);
        void render();

        const static int MAXPOWERUPS = 5;

    private:
        Powerup* powerupList[MAXPOWERUPS] = {};
        SpriteManager* spriteManager;
};