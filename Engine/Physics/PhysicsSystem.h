#pragma once
#include <Core/System.h>
#include <box2d/box2d.h>
#include "Physics/ContactListener.h"

namespace hummus
{
	class GameObject;

	class PhysicsSystem : public System
	{
	public:
		struct RigidBodyData
		{
			Vector2 size;
			float density{ 0 };
			float friction{ 1 };
			float restitution{ 0.3f };
			bool lockAngle{ false };
			bool isDynamic{ false };
			bool isTrigger{ false };
		};

	public:
		virtual bool Startup() override;
		virtual void Update() override;
		virtual void Shutdown() override;

		b2Body* CreateBody(const Vector2& position, float angle, const RigidBodyData& rb, GameObject* gameObject);
		void DestroyBody(b2Body* body);

		static Vector2 WorldToScreen(const Vector2& world) { return world * 32.0f; }
		static Vector2 ScreenToWorld(const Vector2& screen) { return screen * (1.0f / 32.0f); }

	protected:
		b2World* m_world{ nullptr };
		ContactListener* contactListener{nullptr};
	};
}