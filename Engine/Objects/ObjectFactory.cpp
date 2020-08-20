#include "pch.h"
#include "ObjectFactory.h"
#include "Components/SpriteAnimationComponent.h"
#include "Components/PhysicsComponent.h"

namespace hummus
{
	void ObjectFactoryImpl::Initialize()
	{
		ObjectFactory::Instance().Register("GameObject", hummus::Object::Instantiate<hummus::GameObject>);
		ObjectFactory::Instance().Register("PhysicsComponent", hummus::Object::Instantiate<hummus::PhysicsComponent>);
		ObjectFactory::Instance().Register("SpriteComponent", hummus::Object::Instantiate<hummus::SpriteComponent>);
		ObjectFactory::Instance().Register("SpriteAnimationComponent", hummus::Object::Instantiate<hummus::SpriteAnimationComponent>);
	}
}
