#pragma once
#include <box2d/box2d.h>
#include <Components/PhysicsComponent.h>

namespace hummus
{
	class RigidBodyComponent : public PhysicsComponent
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new RigidBodyComponent(*this); }

		void Read(const rapidjson::Value& value);

		virtual void Update() override;

		virtual void ApplyForce(const Vector2& force) override;

	protected:
		PhysicsSystem::RigidBodyData m_rb;
		b2Body* m_body{ nullptr };
	};
}