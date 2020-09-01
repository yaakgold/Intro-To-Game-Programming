#include "pch.h"
#include "PlayerComponent.h"
#include <Core/EventManager.h>
#include <Objects/Scene.h>
#include <Objects/GameObject.h>
#include <Objects/ObjectFactory.h>
#include <Components/SpriteComponent.h>
#include "Components/RigidBodyComponent.h"

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

			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();

			if (audioComponent)
			{
				audioComponent->SetSoundName("jump.wav");
				audioComponent->Play();
			}
		}

		RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
		if (component)
		{
			component->ApplyForce(force);

			Vector2 velocity = component->GetVelocity();

			SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();

			if (velocity.x <= -0.05f) spriteComponent->Flip();
			else if (velocity.x >= 0.05f) spriteComponent->Flip(false);
		}
    }
	
	void PlayerComponent::OnCollisionEnter(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

		if (gameObject->m_tag == "Enemy")
		{
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();

			if (m_owner->m_engine->GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_LSHIFT) == hummus::InputSystem::eButtonState::HELD)
			{
				if (audioComponent)
				{
					audioComponent->SetSoundName("EnemyHurt.wav");
					audioComponent->Play();
				}

				gameObject->m_flags[GameObject::eFlags::DESTROY] = true;
			}
			else if (audioComponent)
			{
				audioComponent->SetSoundName("grunt.wav");
				audioComponent->Play();
			}
		}
		else if (gameObject->m_tag == "Coin")
		{
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();

			if (audioComponent)
			{
				audioComponent->SetSoundName("coin.wav");
				audioComponent->Play();
			}

			GameObject* particle = ObjectFactory::Instance().Create<GameObject>("ProtoParticle");
			particle->m_transform.position = gameObject->m_transform.position;
			m_owner->m_scene->AddGameObject(particle);

			gameObject->m_flags[GameObject::eFlags::DESTROY] = true;
		}
		else if (gameObject->m_tag == "Lava")
		{
			m_owner->m_flags[GameObject::eFlags::DESTROY] = true;

			Event event;
			event.type = "PlayerDead";
			EventManager::Instance().Notify(event);
		}
	}
	
	void PlayerComponent::OnCollisionExit(const Event& event)
	{
		
	}
}
