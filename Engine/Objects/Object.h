#pragma once
#include "Core/Json.h"

namespace hummus
{
	class Object
	{
	public:
		virtual bool Create(void* data = nullptr) = 0;
		virtual void Destroy() = 0;

		virtual void Read(const rapidjson::Value& value) {}
	};
}