#include "pch.h"
#include "PlayerComponent.h"
#include "Components/RigidBodyComponent.h"
#include <Components/SpriteComponent.h>

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
		auto floorContacts = m_owner->GetContactsByTag("Floor");
		auto itemContacts = m_owner->GetContactsByTag("Box");
		bool onGround = (!floorContacts.empty() || !itemContacts.empty());

		Vector2 force{ 0,0 };

		if (m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == hummus::InputSystem::eButtonState::HELD || m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == hummus::InputSystem::eButtonState::HELD)
		{
			force.x = -20;
			//m_owner->m_transform.angle += -200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == hummus::InputSystem::eButtonState::HELD || m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == hummus::InputSystem::eButtonState::HELD)
		{
			force.x = 20;
			//m_owner->m_transform.angle += 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}

		if (onGround && (m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == hummus::InputSystem::eButtonState::HELD || m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == hummus::InputSystem::eButtonState::HELD))
		{
			force.y = -500;

			/*AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();

			if (audioComponent)
			{
				audioComponent->Play();
			}*/
		}

		RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
		if (component)
		{
			component->ApplyForce(force);

			Vector2 velocity = component->GetVelocity();

			SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();

			if (velocity.x <= -0.5f) spriteComponent->Flip();
			else if (velocity.x >= 0.5f) spriteComponent->Flip(false);
		}

		auto coinContacts = m_owner->GetContactsByTag("Coin");
		for (auto contact : coinContacts)
		{
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
		}
    }
}
