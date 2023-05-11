#include <Timestep.h>

Timestep::Timestep(double time) {
    this->time = time;
}

double Timestep::GetTime() {
    return time;
}