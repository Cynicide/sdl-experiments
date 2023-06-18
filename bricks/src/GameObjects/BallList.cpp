#include <BallList.h>

BallList::BallList(SpriteManager* spriteManager, AudioManager* audioManager) {
    this->spriteManager = spriteManager;
    this->audioManager = audioManager;
}

BallList::~BallList() {
    clear();
}

void BallList::add() {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] == nullptr) {
            ballList[b] = new Ball(spriteManager, audioManager);
            break;
        }
    }
}

void BallList::fillAtLocation(float x, float y, float currentVel) {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] == nullptr) {
            ballList[b] = new Ball(spriteManager, x, y, currentVel, audioManager);
        }
    }
}

void BallList::remove(int index) {
    delete(ballList[index]);
    ballList[index] = nullptr;
}

void BallList::clear() {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] != nullptr) {
            remove(b);
        }
    }
}

Ball* BallList::get(int index) {
    return ballList[index];
}

void BallList::update(double dt, SDL_FRect paddleRect) {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] != nullptr) {
            if (ballList[b]->stuckToPaddle == true) {
                ballList[b]->updateStuck(dt, paddleRect);
            } else {
                ballList[b]->update(dt);
            }
        }
    }
}

void BallList::updateServing(double dt, SDL_FRect paddleRect) {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] != nullptr) {
            ballList[b]->update(dt, paddleRect);
        }
    }
}

void BallList::render() {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] != nullptr) {
            ballList[b]->render();
        }
    }
}

void BallList::unstickAll() {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] != nullptr) {
                ballList[b]->releaseFromPaddle();
                ballList[b]->resetStuckOffset();
        }
    }
}

void BallList::setSpeed(int speed) {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] != nullptr) {
            ballList[b]->setSpeed(speed);
        }
    }
}