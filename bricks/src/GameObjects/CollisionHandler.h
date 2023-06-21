#pragma once

#include <Physics.h>

class CollisionHandler {

public:
    CollisionHandler();
    ~CollisionHandler(){};

private:
    Physics physics;
};