#pragma once
#include <Core/Factory.h>
#include <Core/Singleton.h>
#include <Objects/Object.h>

namespace hummus
{
	class ObjectFactoryImpl : public Factory<Object, std::string> 
	{
	public:
		void Initialize();
	};
	class ObjectFactory : public Singleton<ObjectFactoryImpl>
	{
	private:
		ObjectFactory() {}
	};
}