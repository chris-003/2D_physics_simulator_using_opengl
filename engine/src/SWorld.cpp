#include "SWorld.h"

namespace engine {
SWorld::SWorld() {
}

SWorld::~SWorld() {
}

void SWorld::step(float timeStep, int32 velocityIterations,
                  int32 positionIterations) {
    world->Step(timeStep, velocityIterations, positionIterations);
}

b2World *SWorld::operator->() {
    return world;
}
} // namespace engine
