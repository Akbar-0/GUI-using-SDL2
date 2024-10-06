#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "Slider.h"
#include <iostream>
#include "RoundCornerRect.h"

class Menu
{
public:
    Menu();
    static Menu* GetInstance();
    void HandleEvent(const SDL_Event& e);
    bool GetCloseState()
    {
        return running;
    }
    void SetCloseState()
    {
        running = false;
    }
    void DefaultRenderState(SDL_Renderer* renderer);
    void Quit(SDL_Renderer* renderer, SDL_Window* window);
    void InitMenu(SDL_Renderer* rendererID, SDL_Window* windowID);
    void SetDefaultRenderColor(SDL_Color color)
    {
        def_RenderColor = color;
    }
    SDL_Rect DrawMenu(SDL_Renderer *rendererID, int x_menu, int y_menu, int w_menu, int h_menu, int r_rects, int w_border, bool hover = false);

private:
    SDL_Event event;
    int w_Windw, h_Windw;
    static Menu* s_Instance;
    SDL_Color def_RenderColor;
    int w_Menu = 200, h_Menu = 300;
    int currentX = 400, currentY = 170;
    bool dragging = false, running = true;
    bool pressed = false, overButton = false;
    Slider rSlider, gSlider, bSlider, aSlider;
    SDL_Rect cursorRect, closeButton, menuFocus;
    bool IsMenuClosed = false, IsMenuFocused = false;
};

#endif // MENU_H
