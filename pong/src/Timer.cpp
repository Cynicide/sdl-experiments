#include <Timer.h>
#include <SDL2/SDL.h>
#include <iostream>

Timer* Timer::sTimer = nullptr;

void Timer::Tick() {
    mDeltaTime = (SDL_GetTicks() - mLastTime) * (TARGET_FPS / 1000.0f);

    if (mDeltaTime > TARGET_DELTATIME) {
        mDeltaTime = 1.5f;
    }
    mLastTime = SDL_GetTicks();

}

Timer::Timer() {

}