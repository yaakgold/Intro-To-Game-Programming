#include <pch.h>
#include <Engine.h>
#include <Math/MathFile.h>
#include <Graphics/Texture.h>
#include <Objects/GameObject.h>
#include <Components/PhysicsComponent.h>
#include <Components/SpriteComponent.h>

hummus::Engine engine;
hummus::GameObject player;

int main(int, char**)
{
	for (size_t i = 0; i < 100; i++)
	{
		std::sqrt(rand() % 100);
	}
	std::cout << engine.GetTimer().ElapsedSeconds() << std::endl;	

	engine.Startup();

	player.Create(&engine);
	player.m_transform.position = { 400, 300 };

	hummus::Component* comp = new hummus::PhysicsComponent;
	player.AddComponent(comp);
	comp->Create();

	comp = new hummus::SpriteComponent;
	player.AddComponent(comp);
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
		player.Update();


		//Quit
		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == hummus::InputSystem::eButtonState::HELD)
			quit = true;

		//Movement
		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == hummus::InputSystem::eButtonState::HELD || engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == hummus::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle += -200.0f * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == hummus::InputSystem::eButtonState::HELD || engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == hummus::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle += 200.0f * engine.GetTimer().DeltaTime();
		}

		//Physics
		hummus::Vector2 force{ 0,0 };

		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_UP) == hummus::InputSystem::eButtonState::HELD || engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == hummus::InputSystem::eButtonState::HELD)
		{
			force = hummus::Vector2::forward * 1000.0f;
		}
		if (engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_DOWN) == hummus::InputSystem::eButtonState::HELD || engine.GetSystem<hummus::InputSystem>()->GetButtonState(SDL_SCANCODE_S) == hummus::InputSystem::eButtonState::HELD)
		{
			force = hummus::Vector2::forward * -1000.0f;
		}
		force = hummus::Vector2::Rotate(force, player.m_transform.angle * hummus::DEG_TO_RAD);

		//Draw
		background->Draw({ 0, 0 }, { 1, 1 }, 0);

		player.Draw();

		engine.GetSystem<hummus::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}
