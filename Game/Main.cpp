#include <Resources/ResourceManager.h>
#include <Graphics/Texture.h>
#include <Graphics/Renderer.h>
#include <pch.h>

hummus::ResourceManager rm;
hummus::Renderer renderer;

int main(int, char**)
{
	renderer.Startup();
	renderer.Create("GAT150", 800, 600);

	//Create textures
	hummus::Texture* texture1 = rm.Get<hummus::Texture>("sf2.png", &renderer);
	hummus::Texture* texture2 = rm.Get<hummus::Texture>("sf2.png", &renderer);
	float angle{ 0 };
	
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

		renderer.StartFrame();

		//Draw
		angle += 0.1f;
		texture1->Draw({ 500, 100 }, { 1, 1 }, angle);
		texture2->Draw({ 100, 100 }, { 1, 1 }, -angle);

		renderer.EndFrame();
	}

	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
