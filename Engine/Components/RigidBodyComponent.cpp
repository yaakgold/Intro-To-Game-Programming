#include "pch.h"
#include "RigidBodyComponent.h"

namespace hummus
{
    bool RigidBodyComponent::Create(void* data)
    {
        m_owner = static_cast<GameObject*>(data);
        m_drag = 0.95f;
        return true;
    }

    void RigidBodyComponent::Destroy()
    {
        m_owner->m_engine->GetSystem<PhysicsSystem>()->DestroyBody(m_body);
    }

    void RigidBodyComponent::Read(const rapidjson::Value& value)
    {
        json::Get(value, "isDynamic", m_rb.isDynamic);
        json::Get(value, "isTrigger", m_rb.isTrigger);
        json::Get(value, "lockAngle", m_rb.lockAngle);
        json::Get(value, "size", m_rb.size);
        json::Get(value, "density", m_rb.density);
        json::Get(value, "friction", m_rb.friction);
        json::Get(value, "restitution", m_rb.restitution);
    }

    void RigidBodyComponent::Update()
    {
        if (m_body == nullptr)
        {
            m_body = m_owner->m_engine->GetSystem<PhysicsSystem>()->CreateBody(m_owner->m_transform.position, m_owner->m_transform.angle, m_rb, m_owner);
        }

        m_owner->m_transform.position = PhysicsSystem::WorldToScreen(m_body->GetPosition());
        m_owner->m_transform.angle = hummus::RadsToDegs(m_body->GetAngle());

        m_velocity = m_body->GetLinearVelocity();
        m_velocity.x = Clamp(m_velocity.x, -5.0f, 5.0f);
        m_body->SetLinearVelocity(m_velocity);
    }

    void RigidBodyComponent::ApplyForce(const Vector2& force)
    {
        m_body->ApplyForceToCenter(force, true);
    }
}