#include <Graphics/Texture.h>
#include <pch.h>

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_INIT Error." << SDL_GetError() << std::endl;
		return 1;
	}

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);

	SDL_Window* window = SDL_CreateWindow("GAT 150", 100, 100, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error. " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error. " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//Create textures
	int width = 128, height = 128; 

	SDL_Texture* texture1 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
	Uint32* pixels = new Uint32[width * height];
	memset(pixels, 255, width * height * sizeof(Uint32));
	SDL_UpdateTexture(texture1, NULL, pixels, width * sizeof(Uint32));

	hummus::Texture texture;
	texture.Create("sf2.png", renderer);
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

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderClear(renderer);

		//Draw
		for (size_t i = 0; i < width * height; i++)
		{
			Uint8 c = rand() % 256;
			pixels[i] = (c << 24 | c << 16 | c << 8);
		}

		//pixel memory (8/8/8/8), (8/8/8/8)
		//pixel memory (c/c/c/0), (c/c/c/0)

		SDL_UpdateTexture(texture1, NULL, pixels, width * sizeof(Uint32));
	
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = width * 2;
		rect.h = height * 3;
		SDL_RenderCopy(renderer, texture1, NULL, &rect);

		angle += 0.1f;
		texture.Draw({ 500, 100 }, { 1, 1 }, angle);

		SDL_RenderPresent(renderer);
	}

	IMG_Quit();
	SDL_Quit();

	return 0;
}
