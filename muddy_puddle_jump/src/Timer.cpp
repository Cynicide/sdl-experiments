#include <Timer.h>
#include <SDL2/SDL.h>
#include <iostream>

Timer* Timer::sTimer = nullptr;

void Timer::Tick() {
    //mDeltaTime = (SDL_GetTicks() - mLastTime) * (TARGET_FPS / 1000.0f);

    mDeltaTime = (SDL_GetPerformanceCounter() - mLastTime) / (float)SDL_GetPerformanceFrequency();

    if (mDeltaTime > TARGET_DELTATIME) {
        mDeltaTime = 1.5f;
    }
    //mLastTime = SDL_GetTicks();
    mLastTime = SDL_GetPerformanceCounter();
}

Timer::Timer() {

}