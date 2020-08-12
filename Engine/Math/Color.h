#pragma once

#include <SDL.h>
#include <windows.h>
#include <iostream>

namespace hummus
{
	struct Color
	{
		float r, g, b, a;

		Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{} {}
		Color(float r, float g, float b, float a = 1.0f) : r{ r }, g{ g }, b{ b }, a{ a } {}

		void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }

		static const Color white;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color yellow;
		static const Color purple;
		static const Color orange;

#pragma region Operator Overloads

		float& operator [] (size_t index) { return (&r)[index]; }
		const float& operator [] (size_t index) const { return (&r)[index]; }

		//Two colors
		Color operator + (const Color& c) const { return Color{ r + c.r, g + c.g, b + c.b }; }
		Color operator - (const Color& c) const { return Color{ r - c.r, g - c.g, b - c.b }; }
		Color operator * (const Color& c) const { return Color{ r * c.r, g * c.g, b * c.b }; }
		Color operator / (const Color& c) const { return Color{ r / c.r, g / c.g, b / c.b }; }

		Color& operator += (const Color& c) { r += c.r; g += c.g; b += c.b; return *this; }
		Color& operator -= (const Color& c) { r -= c.r; g -= c.g; b -= c.b; return *this; }
		Color& operator *= (const Color& c) { r *= c.r; g *= c.g; b *= c.b; return *this; }
		Color& operator /= (const Color& c) { r /= c.r; g /= c.g; b /= c.b; return *this; }

		//Color and a scalar
		Color operator + (float s) const { return Color{ r + s, g + s, b + s }; }
		Color operator - (float s) const { return Color{ r - s, g - s, b - s }; }
		Color operator * (float s) const { return Color{ r * s, g * s, b * s }; }
		Color operator / (float s) const { return Color{ r / s, g / s, b / s }; }

		Color& operator += (float s) { r += s; g += s; b += s; return *this; }
		Color& operator -= (float s) { r -= s; g -= s; b -= s; return *this; }
		Color& operator *= (float s) { r *= s; g *= s; b *= s; return *this; }
		Color& operator /= (float s) { r /= s; g /= s; b /= s; return *this; }

		operator SDL_Color() const { return Pack888(); }

		//Streams
		friend std::istream& operator >> (std::istream& stream, Color& c);

#pragma endregion

#pragma region Method Declaration

		SDL_Color Pack888() const;

#pragma endregion

	};

#pragma region Method Implementation
	
	inline SDL_Color Color::Pack888() const
	{
		SDL_Color color;
		color.r = static_cast<BYTE>(r * 255.0f);
		color.g = static_cast<BYTE>(g * 255.0f);
		color.b = static_cast<BYTE>(b * 255.0f);
		color.a = static_cast<BYTE>(a * 255.0f);

		return color;
	}

#pragma endregion
}