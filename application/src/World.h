#pragma once
#include "SWorld.h"

class World : public engine::SWorld {
private:
    World();

public:
    ~World();
    static World &getInstance();
};
