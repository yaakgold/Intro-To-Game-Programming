#pragma once
#include "pch.h"
#include <time.h>
#include "Engine.h"

namespace hummus
{
	bool Engine::Startup()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cout << "SDL_INIT Error." << SDL_GetError() << std::endl;
			return false;
		}

		m_systems.push_back(new Renderer);
		m_systems.push_back(new InputSystem);
		m_systems.push_back(new ResourceManager);
		m_systems.push_back(new PhysicsSystem);
		m_systems.push_back(new AudioSystem);


		for (auto system : m_systems)
		{
			system->Startup();
		}

		GetSystem<Renderer>()->Create("GAT 150", 800, 600);

		return true;
	}

	void Engine::Shutdown()
	{
		for (auto system : m_systems)
		{
			system->Shutdown();
			delete system;
		}

		m_systems.clear();

		SDL_Quit();
	}

	void Engine::Update()
	{
		m_timer.Tick();
		for (auto system : m_systems)
		{
			system->Update();
		}
	}
}