#pragma once

#include <Objects/Object.h>
#include <Engine.h>
#include <vector>
#include <bitset>

namespace hummus
{
	class Component;

	class GameObject : public Object
	{
	public:
		enum eFlags
		{
			ACTIVE,
			VISIBLE,
			DESTROY,
			TRANSIENT
		};


	public:
		GameObject() = default;
		GameObject(const GameObject& other);

		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new GameObject(*this); }

		virtual void Read(const rapidjson::Value& value) override;

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

		void ReadComponents(const rapidjson::Value& value);

		void Update();
		void Draw();

		friend class Component;
		friend class PhysicsComponent;

	public:
		std::string m_name;
		std::string m_tag;
		float m_lifetime{ 0 };
		
		std::bitset<32> m_flags;

		Transform m_transform;
		Engine* m_engine{ nullptr };

	protected:
		std::vector<Component*> m_components;
	};
}