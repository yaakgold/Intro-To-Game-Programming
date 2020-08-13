#pragma once
#include "Components/Component.h"

namespace hummus
{
	class PlayerComponent : public Component
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual void Update() override;

	};
}