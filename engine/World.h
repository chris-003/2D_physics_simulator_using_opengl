#pragma once
#include <box2d/box2d.h>

namespace engine {
	class World {
	public:
		World();
		~World();
		void step(float timeStep = 1.0f / 60.0f, int32 velocityIterations = 6, int32 positionIterations = 2);
		b2World *operator->();

	protected:
		b2World *world;
	};
}
