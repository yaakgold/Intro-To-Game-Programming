#pragma once
#include "Components/Component.h"
#include "Components/AudioComponent.h"

namespace hummus
{
	class EnemyComponent : public Component
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new EnemyComponent(*this); }

		virtual void Update() override;

	};
}