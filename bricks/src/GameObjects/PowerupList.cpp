#include <PowerupList.h>
#include "spdlog/spdlog.h"

PowerupList::PowerupList(SpriteManager* spriteManager) {
    this->spriteManager = spriteManager;
}

PowerupList::~PowerupList() {
    clear();
}

void PowerupList::add(float x, float y, int parentWidth) {
    auto logger = spdlog::get("fileLogger");
    for (int p = 0; p < MAXPOWERUPS; ++p) {
        if (powerupList[p] == nullptr) {
            logger->info("Adding powerup at: " + p);
            powerupList[p] = new Powerup(spriteManager, x, y, parentWidth);
            break;
        }
    }
}

void PowerupList::remove(int index) {
    delete powerupList[index];
    powerupList[index] = nullptr;
}

void PowerupList::clear() {
    for (int p = 0; p < MAXPOWERUPS; ++p) {
        if (powerupList[p] != nullptr) {
            remove(p);
        }
    }
}

Powerup* PowerupList::get(int index) {
    return powerupList[index];
}

void PowerupList::update(double dt) {
    for (int p = 0; p < MAXPOWERUPS; ++p) {
        if (powerupList[p] != nullptr) {
            powerupList[p]->update(dt);
            // If they have fallen off the bottom of the screen delete them.
            if (powerupList[p]->powerupRect.y > SCREEN_HEIGHT) {
                delete(powerupList[p]);
                powerupList[p] = nullptr; 
            }
        }
    }
}

void PowerupList::render() {
    for (int p = 0; p < MAXPOWERUPS; ++p) {
        if (powerupList[p] != nullptr) {
            powerupList[p]->render();
        }
    }
}