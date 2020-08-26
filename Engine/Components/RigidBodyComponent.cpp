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
        json::Get(value, "restitution", m_rb.restitution);
    }

    void RigidBodyComponent::Update()
    {
        if (m_body == nullptr)
        {
            m_body = m_owner->m_engine->GetSystem<PhysicsSystem>()->CreateBody(m_owner->m_transform.position, m_rb, m_owner);
            m_body->SetTransform(m_owner->m_transform.position, DegsToRads(m_owner->m_transform.angle));
        }

        m_owner->m_transform.position = m_body->GetPosition();
        m_owner->m_transform.angle = hummus::RadsToDegs(m_body->GetAngle());
    }

    void RigidBodyComponent::ApplyForce(const Vector2& force)
    {
        m_body->ApplyLinearImpulseToCenter(force, true);
    }
}