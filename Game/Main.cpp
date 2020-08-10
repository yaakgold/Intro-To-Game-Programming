#include <pch.h>
#include <Core/Timer.h>
#include <Graphics/Texture.h>
#include <Input/InputSystem.h>
#include <Graphics/Renderer.h>
#include <Resources/ResourceManager.h>

hummus::ResourceManager rm;
hummus::Renderer renderer;
hummus::InputSystem inputSystem;
hummus::FrameTimer timer;

//namespace hummus
//{
//	using clock = std::chrono::high_resolution_clock;
//	using clockDuration = std::chrono::duration<clock::rep, std::nano>;
//}


int main(int, char**)
{
	for (size_t i = 0; i < 100; i++)
	{
		std::sqrt(rand() % 100);
	}
	std::cout << timer.ElapsedSeconds() << std::endl;	


	renderer.Startup();
	renderer.Create("GAT150", 800, 600);
	inputSystem.Startup();

	//Create textures
	hummus::Texture* car = rm.Get<hummus::Texture>("cars.png", &renderer);
	hummus::Texture* background = rm.Get<hummus::Texture>("background.png", &renderer);
	float angle{ 0 };
	hummus::Vector2 position{ 400, 300 };
	
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

		timer.Tick();
		inputSystem.Update();
		renderer.StartFrame();

		//Quit
		if (inputSystem.GetButtonState(SDL_SCANCODE_ESCAPE) == hummus::InputSystem::eButtonState::HELD)
			quit = true;

		//Movement
		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == hummus::InputSystem::eButtonState::HELD || inputSystem.GetButtonState(SDL_SCANCODE_A) == hummus::InputSystem::eButtonState::HELD)
		{
			position.x += -200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == hummus::InputSystem::eButtonState::HELD || inputSystem.GetButtonState(SDL_SCANCODE_D) == hummus::InputSystem::eButtonState::HELD)
		{
			position.x += 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_UP) == hummus::InputSystem::eButtonState::HELD || inputSystem.GetButtonState(SDL_SCANCODE_W) == hummus::InputSystem::eButtonState::HELD)
		{
			position.y += -200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_DOWN) == hummus::InputSystem::eButtonState::HELD || inputSystem.GetButtonState(SDL_SCANCODE_S) == hummus::InputSystem::eButtonState::HELD)
		{
			position.y += 200.0f * timer.DeltaTime();
		}

		//Draw
		angle += 180 * timer.DeltaTime();
		background->Draw({ 0, 0 }, { 1, 1 }, 0);
		car->Draw({0, 16, 64, 144}, position, { 1, 1 }, 0);

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
