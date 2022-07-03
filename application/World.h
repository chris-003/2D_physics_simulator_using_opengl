#pragma once
#include "engine/engine.h"

class World : public engine::World {
private:
    World();

public:
    ~World();
    static World &getInstance();
};
