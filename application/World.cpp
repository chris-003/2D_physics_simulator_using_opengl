#include "World.h"

World::World() {
    world = new b2World(b2Vec2(0, -10));
    float G = 10, L = 1000, radius = 0.001;
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.f);
    b2Body *groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(2.0 * L, 10.0f);
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundBox;
    groundFixtureDef.density = 0.0f;
    groundFixtureDef.friction = 0.0f;
    groundFixtureDef.restitution = 1.0f;
    groundFixtureDef.restitutionThreshold = 0.0f;
    groundBody->CreateFixture(&groundFixtureDef);

    b2BodyDef wallDef;
    wallDef.position.Set(-2.0f * radius, 0.6f * L);
    b2Body *wallBody = world->CreateBody(&wallDef);
    b2PolygonShape wallBox;
    wallBox.SetAsBox(radius, 0.6f * L);
    b2FixtureDef wallFixtureDef;
    wallFixtureDef.shape = &wallBox;
    wallFixtureDef.density = 0.0f;
    wallFixtureDef.friction = 0.0f;
    wallFixtureDef.restitution = 1.0f;
    wallFixtureDef.restitutionThreshold = 0.0f;
    wallBody->CreateFixture(&wallFixtureDef);

    b2BodyDef b1Def;
    b1Def.type = b2_dynamicBody;
    b1Def.position.Set(0.0f, 2.0f * L / 3.0f + radius);
    b2Body *b1 = world->CreateBody(&b1Def);
    b2CircleShape b1Shape;
    b1Shape.m_radius = radius;
    // b2PolygonShape b1Shape;
    // b1Shape.SetAsBox(radius, radius);
    b2FixtureDef b1FixtureDef;
    b1FixtureDef.shape = &b1Shape;
    b1FixtureDef.density = 1.0f;
    b1FixtureDef.friction = 0.0f;
    b1FixtureDef.restitution = 1.0f;
    b1FixtureDef.restitutionThreshold = 0.0f;
    b1->CreateFixture(&b1FixtureDef);

    b2BodyDef b2Def;
    b2Def.type = b2_dynamicBody;
    b2Def.position.Set(L * sqrt(5.0f) / 3.0f, radius);
    b2Body *b2 = world->CreateBody(&b2Def);
    b2CircleShape b2Shape;
    b2Shape.m_radius = radius;
    // b2PolygonShape b2Shape;
    // b2Shape.SetAsBox(radius, radius);
    b2FixtureDef b2FixtureDef;
    b2FixtureDef.shape = &b2Shape;
    b2FixtureDef.density = 1.0f;
    b2FixtureDef.friction = 0.0f;
    b2FixtureDef.restitution = 1.0f;
    b2FixtureDef.restitutionThreshold = 0.0f;
    b2->CreateFixture(&b2FixtureDef);
    b2->ApplyLinearImpulseToCenter(b2Vec2(b2->GetMass() * 2.0f * sqrt(G * L) * sqrt(2.0f / 3.0f) / 3.0f, 0.0f), true);

    b2DistanceJointDef jointDef;
    jointDef.Initialize(b1, b2, b1->GetWorldCenter(), b2->GetWorldCenter());
    jointDef.collideConnected = true;
    b2DistanceJoint *joint = (b2DistanceJoint *)world->CreateJoint(&jointDef);
}

World::~World() {
}

World &World::getInstance() {
    static World instance;
    return instance;
}
