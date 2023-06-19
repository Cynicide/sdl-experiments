# pragma once
#include <Powerup.h>
#include <SpriteManager.h>
#include <memory>

class PowerupList {
    public:

        PowerupList(SpriteManager* spriteManager);
        ~PowerupList();
        void add(float x, float y, int parentWidth);
        void remove(int index);
        void clear();
        std::shared_ptr<Powerup> get(int index);
        void update(double dt);
        void render();

        const static int MAXPOWERUPS = 5;

    private:
        std::shared_ptr<Powerup> powerupList[MAXPOWERUPS];
        SpriteManager* spriteManager;
};