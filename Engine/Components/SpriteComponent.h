#pragma once
#include "RenderComponent.h"

namespace hummus
{
	class SpriteComponent : public RenderComponent
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual void Read(const rapidjson::Value& value);

		virtual void Update() override;
		virtual void Draw() override;

	protected:
		std::string m_textureName;
		SDL_Rect m_rect{ 0, 0, 0, 0 };
	};
}