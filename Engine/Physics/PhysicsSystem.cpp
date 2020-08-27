#include "pch.h"
#include "PhysicsSystem.h"

namespace hummus
{
    bool PhysicsSystem::Startup()
    {
        b2Vec2 gravity{ 0, 10 };
        m_world = new b2World(gravity);

        contactListener = new ContactListener;
        m_world->SetContactListener(contactListener);

        return true;
    }

    void PhysicsSystem::Update()
    {
        float timeStep = 1.0f / 60.0f;

        m_world->Step(timeStep, 8, 3);
    }
    
    void PhysicsSystem::Shutdown()
    {
        delete m_world;
        m_world = nullptr;
    }
    
    b2Body* PhysicsSystem::CreateBody(const Vector2& position, float angle, const RigidBodyData& rb, GameObject* gameObject)
    {
        b2BodyDef bodyDef;

        Vector2 world = PhysicsSystem::ScreenToWorld(position);

        bodyDef.type = (rb.isDynamic) ? b2_dynamicBody : b2_staticBody;
        bodyDef.position.Set(world.x, world.y);
        bodyDef.angle = DegsToRads(angle);
        bodyDef.fixedRotation = rb.lockAngle;
        b2Body* body = m_world->CreateBody(&bodyDef);


        b2PolygonShape shape;
        Vector2 worldSize = PhysicsSystem::ScreenToWorld(rb.size);
        shape.SetAsBox(worldSize.x, worldSize.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.isSensor = rb.isTrigger;
        fixtureDef.density = rb.density;
        fixtureDef.restitution = rb.restitution;
        fixtureDef.friction = rb.friction;
        fixtureDef.userData = gameObject;

        body->CreateFixture(&fixtureDef);

        return body;
    }
    
    void PhysicsSystem::DestroyBody(b2Body* body)
    {
        m_world->DestroyBody(body);
    }
}