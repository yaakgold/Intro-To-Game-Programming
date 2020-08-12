#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace hummus
{
    bool hummus::SpriteComponent::Create(void* data)
    {
        m_texture = m_owner->m_engine->GetSystem<hummus::ResourceManager>()->Get<hummus::Texture>("cars.png", m_owner->m_engine->GetSystem<hummus::Renderer>());

        return true;
    }

    void hummus::SpriteComponent::Destroy()
    {
    }

    void hummus::SpriteComponent::Update()
    {
    }

    void hummus::SpriteComponent::Draw()
    {
        m_texture->Draw({ 0, 16, 64, 144 }, m_owner->m_transform.position, { 1, 1 }, m_owner->m_transform.angle);
    }
}