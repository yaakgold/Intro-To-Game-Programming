#pragma once

#include <Math/Transform.h>
#include <Objects/Object.h>
#include <Engine.h>
#include <vector>
#include <bitset>
#include <list>

namespace hummus
{
	class Component;
	class Scene;

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

		void BeginContact(GameObject* other);
		void EndContact(GameObject* other);
		std::vector<GameObject*> GetContactsByTag(const std::string& tag);

		friend class Component;
		friend class PhysicsComponent;

	public:
		std::string m_name;
		std::string m_tag;
		float m_lifetime{ 0 };
		
		std::bitset<32> m_flags;

		Transform m_transform;
		Engine* m_engine{ nullptr };
		Scene* m_scene{ nullptr };

	protected:
		std::vector<Component*> m_components;
		std::list<GameObject*> m_contacts;
	};
}