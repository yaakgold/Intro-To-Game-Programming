#include "pch.h"
#include <Graphics\Texture.h>
#include "SpriteAnimationComponent.h"

namespace hummus
{
    bool SpriteAnimationComponent::Create(void* data)
    {
        m_owner = static_cast<GameObject*>(data);
        return true;
    }

    void SpriteAnimationComponent::Destroy()
    {

    }

    void SpriteAnimationComponent::Read(const rapidjson::Value& value)
    {
        SpriteComponent::Read(value);

        json::Get(value, "numX", m_numX);
        json::Get(value, "numY", m_numY);
        json::Get(value, "numFrames", m_numFrames);
        json::Get(value, "fps", m_FPS);

        m_frameRate = 1.0 / m_FPS;
    }

    void SpriteAnimationComponent::Update()
    {
        //Update frame timer
        m_frameTimer += m_owner->m_engine->GetTimer().DeltaTime();
        if (m_frameTimer >= m_frameRate)
        {
            m_frameTimer = 0;
            m_frame++;

            if (m_frame >= m_numFrames)
            {
                m_frame = 0;
            }
        }

        //Update frame rect
        Texture* texture = m_owner->m_engine->GetSystem<hummus::ResourceManager>()->Get<hummus::Texture>(m_textureName, m_owner->m_engine->GetSystem<hummus::Renderer>());
        Vector2 textureSize = texture->GetSize();
        Vector2 cellSize = textureSize / Vector2{ m_numX, m_numY };
            
        m_rect.x = static_cast<int>((m_frame % m_numX) * cellSize.x);
        m_rect.y = static_cast<int>((m_frame / m_numX) * cellSize.y);
        m_rect.w = static_cast<int>(cellSize.x);
        m_rect.h = static_cast<int>(cellSize.y);
    }
}