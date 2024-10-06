#include "Menu.h"
#include "SDL.h"
#include <iostream>
//#include "SDL2_gfxPrimitives.h"

int SDL_main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Color color = {100, 150, 200, 255};


    Menu* m_Menu = Menu::GetInstance();
    bool IsRunning = true;
    while(IsRunning)
    {
        if(!m_Menu->GetCloseState())
        {
            IsRunning = false;
        }
        m_Menu->SetDefaultRenderColor(color);
        m_Menu->InitMenu(renderer, window);
    }

    m_Menu->Quit(renderer, window);

    return 0;
}
