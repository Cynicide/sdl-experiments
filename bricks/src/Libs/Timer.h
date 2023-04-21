#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer {
    public:
        void Tick();
        inline float GetDeltaTime() {return mDeltaTime;}
        inline static Timer* get() {return sTimer = (sTimer != nullptr)? sTimer : new Timer();}


    private:
        Timer();
        static Timer* sTimer;
        float mDeltaTime;
        float mLastTime;
};

#endif