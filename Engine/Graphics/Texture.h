#pragma once
#include <Math\Vector2.h>
#include <string>
#include <SDL.h>

namespace hummus
{
	class Texture
	{
	public:
		bool Create(const std::string& fileName, SDL_Renderer* renderer);
		void Destroy();

		void Draw(const Vector2& pos, const Vector2& scale, float angle);

		Vector2 GetSize();

	protected:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}