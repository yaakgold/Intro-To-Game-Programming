#include <pch.h>
#include <Engine.h>
#include <Core/Json.h>
#include <Core/Factory.h>
#include <Math/MathFile.h>
#include <Graphics/Texture.h>
#include <Objects/GameObject.h>
#include <Components/PhysicsComponent.h>
#include <Components/SpriteComponent.h>
#include "Components/PlayerComponent.h"

hummus::Engine engine;
hummus::Factory<hummus::Object, std::string> objectFactory;

int main(int, char**)
{
#pragma region JSON Testing
	/*
	rapidjson::Document document;
	hummus::json::Load("json.txt", document);

	std::string str; 
	hummus::json::Get(document, "string", str);
	std::cout << str << std::endl; 
	
	bool b;
	hummus::json::Get(document, "bool", b); 
	std::cout << b << std::endl; 
	
	int i1; 
	hummus::json::Get(document, "integer1", i1); 
	std::cout << i1 << std::endl; 
	
	int i2;
	hummus::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl; 
	
	float f;
	hummus::json::Get(document, "float", f);
	std::cout << f << std::endl; 
	
	hummus::Vector2 v2; 
	hummus::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl; 
	
	hummus::Color color; 
	hummus::json::Get(document, "color", color);
	std::cout << color << std::endl;
	*/
#pragma endregion

	engine.Startup();

	objectFactory.Register("GameObject", hummus::Object::Instantiate<hummus::GameObject>);
	objectFactory.Register("PhysicsComponent", hummus::Object::Instantiate<hummus::PhysicsComponent>);
	objectFactory.Register("SpriteComponent", hummus::Object::Instantiate<hummus::SpriteComponent>);
	objectFactory.Register("PlayerComponent", hummus::Object::Instantiate<hummus::PlayerComponent>);
	
	hummus::GameObject* player = objectFactory.Create<hummus::GameObject>("GameObject");
	player->Create(&engine);
	rapidjson::Document document;
	hummus::json::Load("player.txt", document);
	player->Read(document);

	hummus::Component* comp = objectFactory.Create<hummus::PhysicsComponent>("PhysicsComponent");
	player->AddComponent(comp);
	comp->Create();

	comp = objectFactory.Create<hummus::SpriteComponent>("SpriteComponent");
	player->AddComponent(comp);
	hummus::json::Load("sprite.txt", document);
	comp->Read(document);
	comp->Create();

	comp = objectFactory.Create<hummus::PlayerComponent>("PlayerComponent");
	player->AddComponent(comp);
	comp->Create();

	//Create textures
	hummus::Texture* background = engine.GetSystem<hummus::ResourceManager>()->Get<hummus::Texture>("background.png", engine.GetSystem<hummus::Renderer>());
	
	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		}

		engine.Update();
		player->Update();


		//Quit
		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == hummus::InputSystem::eButtonState::HELD)
			quit = true;

		//Draw
		background->Draw({ 0, 0 }, { 1, 1 }, 0);

		player->Draw();

		engine.GetSystem<hummus::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}
