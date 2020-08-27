#include <pch.h>
#include <Engine.h>
#include <Core/Json.h>
#include <Core/Factory.h>
#include <Objects/Scene.h>
#include <Math/MathFile.h>
#include <Graphics/Texture.h>
#include <Objects/ObjectFactory.h>
#include "Components/PlayerComponent.h"

hummus::Engine engine;
hummus::Scene scene;

int main(int, char**)
{
	engine.Startup();

	hummus::ObjectFactory::Instance().Initialize();
	hummus::ObjectFactory::Instance().Register("PlayerComponent", new hummus::Creator<hummus::PlayerComponent, hummus::Object>);

	scene.Create(&engine);

	rapidjson::Document document;
	hummus::json::Load("scene.txt", document);
	scene.Read(document);

	for (size_t i = 0; i < 10; i++)
	{
		hummus::GameObject* gameObject = hummus::ObjectFactory::Instance().Create<hummus::GameObject>("ProtoCoin");
		gameObject->m_transform.position = { hummus::random(0, 800), hummus::random(200, 300) };
		//gameObject->m_transform.angle = hummus::random(0, 360);
		scene.AddGameObject(gameObject);
	}

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
		scene.Update();


		//Quit
		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == hummus::InputSystem::eButtonState::HELD)
			quit = true;

		engine.GetSystem<hummus::Renderer>()->StartFrame();

		scene.Draw();

		engine.GetSystem<hummus::Renderer>()->EndFrame();
	}

	scene.Destroy();
	engine.Shutdown();

	return 0;
}
