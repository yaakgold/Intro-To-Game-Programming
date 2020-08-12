#pragma once
#include <Components/Component.h>

namespace hummus
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw() = 0;
	};
}