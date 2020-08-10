#include "pch.h"
#include "Renderer.h"

namespace hummus
{
    bool hummus::Renderer::Startup()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "SDL_INIT Error." << SDL_GetError() << std::endl;
            return false;
        }

        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);

        return true;
    }

    void hummus::Renderer::Update()
    {

    }

    void hummus::Renderer::Shutdown()
    {
        IMG_Quit();
    }

    bool Renderer::Create(const std::string& windowName, int w, int h)
    {
        m_window = SDL_CreateWindow(windowName.c_str(), 100, 100, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (m_window == nullptr)
        {
            std::cout << "SDL_CreateWindow Error. " << SDL_GetError() << std::endl;
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (m_renderer == nullptr)
        {
            std::cout << "SDL_CreateRenderer Error. " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        return true;
    }

    void Renderer::StartFrame()
    {
        SDL_RenderClear(m_renderer);
    }

    void Renderer::EndFrame()
    {
        SDL_RenderPresent(m_renderer);
    }
}
