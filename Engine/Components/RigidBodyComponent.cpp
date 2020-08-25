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

    }

    void RigidBodyComponent::Read(const rapidjson::Value& value)
    {
        json::Get(value, "isDynamic", m_rb.isDynamic);
        json::Get(value, "lockAngle", m_rb.lockAngle);
        json::Get(value, "size", m_rb.size);
        json::Get(value, "density", m_rb.density);
        json::Get(value, "friction", m_rb.friction);
    }

    void RigidBodyComponent::Update()
    {
        if (m_body == nullptr)
        {
            m_body = m_owner->m_engine->GetSystem<PhysicsSystem>()->CreateBody(m_owner->m_transform.position, m_rb, m_owner);
        }

        m_owner->m_transform.position = m_body->GetPosition();
        m_owner->m_transform.angle = m_body->GetAngle();
    }

    void RigidBodyComponent::ApplyForce(const Vector2& force)
    {
        m_body->ApplyLinearImpulseToCenter(force, true);
    }
}