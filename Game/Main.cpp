#include <pch.h>
#include <Engine.h>
#include "TileMap.h"
#include <Core/Json.h>
#include <Core/Factory.h>
#include <Objects/Scene.h>
#include <Math/MathFile.h>
#include <Graphics/Texture.h>
#include <Objects/ObjectFactory.h>
#include "Components/EnemyComponent.h"
#include "Components/PlayerComponent.h"

hummus::Engine engine;
hummus::Scene scene;

bool restart = false;
bool quit = false;

void StartGame()
{
	engine.Startup();

	hummus::ObjectFactory::Instance().Initialize();
	hummus::ObjectFactory::Instance().Register("PlayerComponent", new hummus::Creator<hummus::PlayerComponent, hummus::Object>);
	hummus::ObjectFactory::Instance().Register("EnemyComponent", new hummus::Creator<hummus::EnemyComponent, hummus::Object>);

	scene.Create(&engine);

	rapidjson::Document document;
	hummus::json::Load("SceneFiles/scene.json", document);
	scene.Read(document);

	hummus::TileMap tileMap;
	hummus::json::Load("SceneFiles/tileMap.json", document);
	tileMap.Read(document);
	tileMap.Create(&scene);

	hummus::EventManager::Instance().Subscribe("CollisionEnter", std::bind(&hummus::PlayerComponent::OnCollisionEnter, scene.FindGameObjectsByTag("Player")[0]->GetComponent<hummus::PlayerComponent>(), std::placeholders::_1), scene.FindGameObjectsByTag("Player")[0]);
	hummus::EventManager::Instance().Subscribe("CollisionExit", std::bind(&hummus::PlayerComponent::OnCollisionExit, scene.FindGameObjectsByTag("Player")[0]->GetComponent<hummus::PlayerComponent>(), std::placeholders::_1), scene.FindGameObjectsByTag("Player")[0]);

}

void GameEvent(const hummus::Event& event)
{
	std::cout << "PlayerDead" << std::endl;

	restart = true;
	quit = true;
}

int main(int, char**)
{
	do
	{
		restart = false;
		StartGame();

		hummus::EventManager::Instance().Subscribe("PlayerDead", &GameEvent);

		SDL_Event event;
		quit = false;
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
	} while (restart);

	return 0;
}
