#include "pch.h"
#include "Texture.h"
#include "Renderer.h"

namespace hummus
{
	bool Texture::Create(const std::string& fileName, void* renderer)
	{
		mem_renderer = static_cast<Renderer*>(renderer)->m_renderer;
		SDL_Surface* surface = IMG_Load(fileName.c_str());

		if (surface == nullptr)
		{
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(mem_renderer, surface);
		SDL_FreeSurface(surface);
		if (m_texture == nullptr)
		{
			return false;
		}

		return true;
	}

	void Texture::Destroy()
	{
		SDL_DestroyTexture(m_texture);
	}

	void Texture::Draw(const Vector2& pos, const Vector2& scale, float angle)
	{
		Vector2 size = GetSize() * scale;

		SDL_Rect rect;
		rect.x = static_cast<int>(pos.x);
		rect.y = static_cast<int>(pos.y);
		rect.w = static_cast<int>(size.x);
		rect.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(mem_renderer, m_texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
	}

	Vector2 Texture::GetSize()
	{
		int w, h;
		SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);

		return Vector2(w, h);
	}
}