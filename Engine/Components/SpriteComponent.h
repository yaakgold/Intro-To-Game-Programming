#pragma once
#include "RenderComponent.h"

namespace hummus
{
	class SpriteComponent : public RenderComponent
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new SpriteComponent(*this); }

		virtual void Read(const rapidjson::Value& value);

		virtual void Update() override;
		virtual void Draw() override;

		void Flip(bool flip = true) { m_flipped = flip; }

	protected:
		std::string m_textureName;
		Vector2 m_origin;
		SDL_Rect m_rect{ 0, 0, 0, 0 };
		bool m_flipped{ false };
	};
}