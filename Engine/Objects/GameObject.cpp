#include "pch.h"
#include "GameObject.h"
#include <Components/Component.h>
#include <Components\RenderComponent.h>

namespace hummus
{
    bool GameObject::Create(void* data)
    {
        m_engine = static_cast<Engine*>(data);
        return false;
    }

    void GameObject::Destroy()
    {

    }

    void GameObject::Read(const rapidjson::Value& value)
    {
        hummus::json::Get(value, "position", m_transform.position);
        hummus::json::Get(value, "scale", m_transform.scale);
        hummus::json::Get(value, "angle", m_transform.angle);
    }

    void GameObject::AddComponent(Component* component)
    {
        component->m_owner = this;
        m_components.push_back(component);
    }

    void GameObject::RemoveComponent(Component* component)
    {
        auto iter = std::find(m_components.begin(), m_components.end(), component);
        if (iter != m_components.end())
        {
            (*iter)->Destroy();
            delete (*iter);
        }
    }

    void GameObject::RemoveAllComponents()
    {
        for (auto component : m_components)
        {
            component->Destroy();
            delete component;
        }
        m_components.clear();
    }

    void GameObject::Update()
    {
        for (auto component : m_components)
        {
            component->Update();
        }
    }

    void GameObject::Draw()
    {
        RenderComponent* comp = GetComponent<RenderComponent>();
        if (comp)
        {
            comp->Draw();
        }
    }
}
