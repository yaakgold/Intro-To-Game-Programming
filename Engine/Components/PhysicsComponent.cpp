#include "pch.h"
#include "PhysicsComponent.h"

bool hummus::PhysicsComponent::Create(void* data)
{
	m_velocity = Vector2::forward * 100;

    return true;
}

void hummus::PhysicsComponent::Destroy()
{
}

void hummus::PhysicsComponent::Update()
{
	m_velocity += m_force * m_owner->m_engine->GetTimer().DeltaTime();
	m_velocity *= m_drag;
	m_owner->m_transform.position += m_velocity * m_owner->m_engine->GetTimer().DeltaTime();
}
