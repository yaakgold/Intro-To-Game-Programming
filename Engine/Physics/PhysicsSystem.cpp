#include "pch.h"
#include "PhysicsSystem.h"

namespace hummus
{
    bool PhysicsSystem::Startup()
    {
        b2Vec2 gravity{ 0, 150 };
        m_world = new b2World(gravity);

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

    b2Body* PhysicsSystem::CreateBody(const Vector2& position, const Vector2& size, float density, bool isDynamic)
    {
        b2BodyDef bodyDef;

        bodyDef.type = (isDynamic) ? b2_dynamicBody : b2_staticBody;
        bodyDef.position.Set(position.x, position.y);
        b2Body* body = m_world->CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(size.x, size.y);

        body->CreateFixture(&shape, density);

        return body;
    }
    
    b2Body* PhysicsSystem::CreateBody(const Vector2& position, const RigidBodyData& rb, GameObject* gameObject)
    {
        b2BodyDef bodyDef;

        bodyDef.type = (rb.isDynamic) ? b2_dynamicBody : b2_staticBody;
        bodyDef.position.Set(position.x, position.y);
        bodyDef.fixedRotation = rb.lockAngle;
        b2Body* body = m_world->CreateBody(&bodyDef);


        b2PolygonShape shape;
        shape.SetAsBox(rb.size.x, rb.size.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = rb.density;
        fixtureDef.friction = rb.friction;
        fixtureDef.userData = gameObject;

        body->CreateFixture(&fixtureDef);

        return body;
    }
}