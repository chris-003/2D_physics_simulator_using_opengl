#include "World.h"

namespace engine {
World::World() {
}

World::~World() {
}

void World::step(float timeStep, int32 velocityIterations,
                 int32 positionIterations) {
    world->Step(timeStep, velocityIterations, positionIterations);
}

b2World *World::operator->() {
    return world;
}
} // namespace engine
