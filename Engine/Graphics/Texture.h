#pragma once
#include <Resources/Resource.h>
#include <Math\Vector2.h>
#include <string>
#include <SDL.h>

namespace hummus
{
	class Texture : public Resource
	{
	public:
		bool Create(const std::string& fileName, void* renderer) override;
		void Destroy() override;

		void Draw(const Vector2& pos, const Vector2& scale, float angle);
		void Draw(const SDL_Rect& source, const Vector2& pos, const Vector2& scale, float angle);

		Vector2 GetSize();

	protected:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* mem_renderer{ nullptr };
	};
}