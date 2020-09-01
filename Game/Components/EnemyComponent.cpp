#include "pch.h"
#include "Objects/Scene.h"
#include "EnemyComponent.h"
#include "Objects/GameObject.h"
#include "Components/RigidBodyComponent.h"

namespace hummus
{
    bool EnemyComponent::Create(void* data)
    {
        m_owner = static_cast<GameObject*>(data);
        return true;
    }

    void EnemyComponent::Destroy()
    {

    }

    void EnemyComponent::Update()
    {
        GameObject* player = m_owner->m_scene->Find("ProtoPlayer");

        if (player)
        {
            Vector2 direction = player->m_transform.position - m_owner->m_transform.position;

            Vector2 force = direction.Normalized() * 10.0f;

            m_owner->GetComponent<RigidBodyComponent>()->ApplyForce(force);
        }
    }
}
