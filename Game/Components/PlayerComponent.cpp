#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"

namespace hummus
{
    bool PlayerComponent::Create(void* data)
    {
		m_owner = static_cast<GameObject*>(data);
        return true;
    }

    void PlayerComponent::Destroy()
    {

    }

    void PlayerComponent::Update()
    {
		//Movement
		if (m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == hummus::InputSystem::eButtonState::HELD || m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == hummus::InputSystem::eButtonState::HELD)
		{
			m_owner->m_transform.angle += -200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == hummus::InputSystem::eButtonState::HELD || m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == hummus::InputSystem::eButtonState::HELD)
		{
			m_owner->m_transform.angle += 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}

		//Physics
		Vector2 force{ 0,0 };

		if (m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_UP) == hummus::InputSystem::eButtonState::HELD || m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == hummus::InputSystem::eButtonState::HELD)
		{
			force = Vector2::forward * 1000.0f;
		}
		if (m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_DOWN) == hummus::InputSystem::eButtonState::HELD || m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_S) == hummus::InputSystem::eButtonState::HELD)
		{
			force = Vector2::forward * -1000.0f;
		}
		force = Vector2::Rotate(force, m_owner->m_transform.angle * hummus::DEG_TO_RAD);

		PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(force);
		}
    }
}
