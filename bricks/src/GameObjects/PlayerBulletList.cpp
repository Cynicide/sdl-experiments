#include <PlayerBulletList.h>
#include <stack>

PlayerBulletList::PlayerBulletList(SpriteManager* spriteManager, AudioManager* audioManager) {
    this->spriteManager = spriteManager;
    this->audioManager = audioManager;
}

PlayerBulletList::~PlayerBulletList() {
    clear();
}

void PlayerBulletList::shoot(SDL_FRect paddleRect) {
    // Don't add any bullets unless two slots are free.
    int freeSlots = 0;
    for (int p = 0; p < MAXBULLETS; ++p) {
        if (bulletList[p] == nullptr) {
            freeSlots = freeSlots + 1;
        }
    }

    if (freeSlots >= MAXBULLETS) {

        // Create a stack to hold the bullets
        std::stack<float> bulletStack;
        
        // Push the location to spawn each bullet above the paddle
        bulletStack.push(paddleRect.x + (paddleRect.w * 0.33));
        bulletStack.push(paddleRect.x + (paddleRect.w * 0.66));

        // Look for empty elements in the bullet array
        for (int p = 0; p < MAXBULLETS; ++p) {
            if (bulletList[p] == nullptr) {
                //Retrieve and pop the bullet xlocation
                float xLoc = bulletStack.top();
                bulletStack.pop();
                //ToDo: Magic number. Why 16?
                bulletList[p] = new PlayerBullet(spriteManager, xLoc, paddleRect.y + 16);
            }
            // If the stack is empty play the audio break out of the loop
            if (bulletStack.empty()) {
                if (Mix_Playing(4)) {
                    Mix_HaltChannel(4);
                    Mix_PlayChannel(4, audioManager->laser, 0);
                } else {
                    Mix_PlayChannel(4, audioManager->laser, 0);
                }            
                break;
            }
        }  
    }
}

void PlayerBulletList::remove(int index) {
    delete(bulletList[index]);
    bulletList[index] = nullptr;
}

void PlayerBulletList::clear() {
    for (int b = 0; b < MAXBULLETS; ++b) {
        if (bulletList[b] != nullptr) {
            remove(b);
        }
    }    
}

PlayerBullet* PlayerBulletList::get(int index) {
    return bulletList[index];
}

void PlayerBulletList::update(double dt) {
    for (int b = 0; b < MAXBULLETS; ++b) {
        if (bulletList[b] != nullptr) {
            //If they have a status of Dead delete them.
            if (bulletList[b]->bulletStatus == Definitions::BulletStatus::BulletDead) {
                remove(b);
            } else {
                bulletList[b]->update(dt);
            }
        }
    }
}

void PlayerBulletList::render() {
    for (int b = 0; b < MAXBULLETS; ++b) {
        if (bulletList[b] != nullptr) {
            bulletList[b]->render();
        }
    }
}