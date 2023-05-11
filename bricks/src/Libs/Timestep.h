#pragma once

class Timestep {
    public:
        Timestep(double time);
        double GetTime();
    private:
    double time = 0.f;
    };