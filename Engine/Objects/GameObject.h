#pragma once

#include <Objects/Object.h>
#include <Engine.h>
#include <vector>

namespace hummus
{
	class Component;

	class GameObject : public Object
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;

		template<typename T>
		inline T* GetComponent()
		{
			T* result{ nullptr };

			for (auto component : m_components)
			{
				result = dynamic_cast<T*>(component);
				if (result) break;
			}

			return result;
		}

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveAllComponents();

		void Update();
		void Draw();

		friend class Component;
		friend class PhysicsComponent;

	public:
		Transform m_transform;
		Engine* m_engine;

	protected:
		std::vector<Component*> m_components;
	};
}