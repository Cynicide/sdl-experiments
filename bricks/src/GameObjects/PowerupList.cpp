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
            powerupList[p] = std::make_unique<Powerup>(spriteManager, x, y, parentWidth);
            break;
        }
    }
}

void PowerupList::remove(int index) {
    powerupList[index].reset();
}

void PowerupList::clear() {
    for (int p = 0; p < MAXPOWERUPS; ++p) {
        if (powerupList[p] != nullptr) {
            remove(p);
        }
    }
}

std::shared_ptr<Powerup> PowerupList::get(int index) {
    return powerupList[index];
}

void PowerupList::update(double dt) {
    for (int p = 0; p < MAXPOWERUPS; ++p) {
        if (powerupList[p] != nullptr) {
            powerupList[p]->update(dt);
            // If they have fallen off the bottom of the screen delete them.
            if (powerupList[p]->powerupRect.y > SCREEN_HEIGHT) {
                powerupList[p].reset(); 
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