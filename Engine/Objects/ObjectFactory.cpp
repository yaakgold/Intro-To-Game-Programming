#include "pch.h"
#include "ObjectFactory.h"
#include "Objects/GameObject.h"
#include "Components/SpriteComponent.h"
#include "Components/PhysicsComponent.h"

namespace hummus
{
	void ObjectFactoryImpl::Initialize()
	{
		ObjectFactory::Instance().Register("GameObject", hummus::Object::Instantiate<hummus::GameObject>);
		ObjectFactory::Instance().Register("PhysicsComponent", hummus::Object::Instantiate<hummus::PhysicsComponent>);
		ObjectFactory::Instance().Register("SpriteComponent", hummus::Object::Instantiate<hummus::SpriteComponent>);
	}
}
