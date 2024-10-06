#include "Menu.h"
#include "Slider.h"

Menu* Menu::s_Instance = nullptr;

Menu::Menu()
    : rSlider(10, 10, 300, 10, 0, 255, 'R'),
      gSlider(10, 40, 300, 10, 0, 255, 'G'),
      bSlider(10, 70, 300, 10, 0, 255, 'B'),
      aSlider(10, 100, 300, 10, 0, 255, 'A')
{
    std::cerr<<"GUI Initiated"<<std::endl;
    //def_RenderColor = {100, 150, 200, 255};
}

Menu* Menu::GetInstance()
{
    return (s_Instance != nullptr) ? s_Instance : new Menu();
}

void Menu::HandleEvent(const SDL_Event& e)
{
//    rSlider.HandleEvent(e);
//    gSlider.HandleEvent(e);
//    bSlider.HandleEvent(e);
//    aSlider.HandleEvent(e);

    if (e.type == SDL_QUIT)
    {
        running = false;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEWHEEL)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                rSlider.HandleKeyDown(e);
                gSlider.HandleKeyDown(e);
                bSlider.HandleKeyDown(e);
                aSlider.HandleKeyDown(e);
                if(cursorRect.x >= menuFocus.x && cursorRect.y >= menuFocus.y &&
                cursorRect.x <= menuFocus.x + menuFocus.w && cursorRect.y <= menuFocus.y + 30)
                {
                    pressed = overButton ? true : false;
                    dragging = !overButton ? true : false;
                    std::cerr << "Dragging Menu" << std::endl;
                }
            }
            else if (e.button.button == SDL_BUTTON_RIGHT)
            {
                std::cerr << "Mouse's right button clicked" << std::endl;
            }
            else if (e.button.button == SDL_BUTTON_MIDDLE)
            {
                if(IsMenuFocused && w_Menu != 200 && h_Menu != 300)
                {
                    w_Menu = 200;
                    h_Menu = 300;
                    std::cerr << "Mouse's middle button clicked; switched to default zoom state!" << std::endl;
                }
                // startX = event.button.x;
                // startY = event.button.y;
            }
        }
        else if (e.type == SDL_MOUSEMOTION)
        {
            rSlider.HandleDragging(e);
            gSlider.HandleDragging(e);
            bSlider.HandleDragging(e);
            aSlider.HandleDragging(e);
            if (dragging && !IsMenuClosed)
            {
                currentX = event.motion.x;
                currentY = event.motion.y;
            }
        }
        else if (e.type == SDL_MOUSEBUTTONUP)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                dragging = false;
                rSlider.HandleKeyUp(e);
                gSlider.HandleKeyUp(e);
                bSlider.HandleKeyUp(e);
                aSlider.HandleKeyUp(e);
            }
        }
        else if (e.type == SDL_MOUSEWHEEL)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (e.wheel.y > 0)
            {
                if(w_Menu <= 400 && h_Menu <= 600 && IsMenuFocused)
                {
                    w_Menu += 2;
                    h_Menu += 2;
                    std::cerr << "Mouse Wheel Scroll Up; zooming into menu!" << std::endl;
                }
                else if (IsMenuFocused)
                    std::cerr << "Zoom in limit reached!" << std::endl;
            }
            else if (e.wheel.y < 0)
            {
                if(w_Menu >= 152 && h_Menu >= 252 && IsMenuFocused)
                {
                    w_Menu -= 2;
                    h_Menu -= 2;
                    std::cerr << "Mouse Wheel Scroll Down; zooming out of menu!" << std::endl;
                }
                else if (IsMenuFocused)
                    std::cerr << "Zoom out limit reached!" << std::endl;
            }
        }
    }
}

void Menu::InitMenu(SDL_Renderer* rendererID, SDL_Window* windowID)
{
    SDL_GetWindowSize(windowID, &w_Windw, &h_Windw);
    while(running)
    {
        while (SDL_PollEvent(&event))
        {
            HandleEvent(event);
        }

        if(rSlider.started || gSlider.started || bSlider.started/* || aSlider.started*/){
            def_RenderColor.r = rSlider.GetValue();
            def_RenderColor.g = gSlider.GetValue();
            def_RenderColor.b = bSlider.GetValue();
            def_RenderColor.a = aSlider.GetValue();
        }

        DefaultRenderState(rendererID);

        SDL_GetMouseState(&cursorRect.x, &cursorRect.y);
        overButton = (cursorRect.x >= closeButton.x && cursorRect.y >= closeButton.y &&
                      cursorRect.x <= closeButton.x + closeButton.w && cursorRect.y <= closeButton.y + closeButton.h);

        menuFocus = {currentX - w_Menu/2, currentY - 20, w_Menu, h_Menu};
        IsMenuFocused = (cursorRect.x >= menuFocus.x && cursorRect.y >= menuFocus.y &&
                         cursorRect.x <= menuFocus.x + menuFocus.w && cursorRect.y <= menuFocus.y + menuFocus.h);

        if (overButton)
        {
            SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
        }
        else if (!IsMenuClosed)
        {
            if(!dragging)
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
            else if(dragging)
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
        }

        if (pressed && overButton)
        {
            DrawMenu(rendererID, 0, 0, 0, 0, 0, 0, true);
            SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
            std::cerr << "Menu Closed" << std::endl;
            DefaultRenderState(rendererID);
            closeButton = {0, 0, 0, 0};
            IsMenuClosed = true;
            pressed = false;
        }

        if (!IsMenuClosed)
        {
            closeButton = DrawMenu(rendererID, menuFocus.x, menuFocus.y, w_Menu, h_Menu, 10, 4, overButton);
        }

        rSlider.Render(rendererID);
        gSlider.Render(rendererID);
        bSlider.Render(rendererID);
        aSlider.Render(rendererID);

        SDL_RenderPresent(rendererID);
    }
}

void Menu::DefaultRenderState(SDL_Renderer* renderer)
{
    //SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));

    SDL_SetRenderDrawColor(renderer, def_RenderColor.r, def_RenderColor.g, def_RenderColor.b, def_RenderColor.a);
    SDL_RenderClear(renderer);
}

SDL_Rect Menu::DrawMenu(SDL_Renderer* rendererID, int x_menu, int y_menu, int w_menu, int h_menu, int r_rects, int w_border, bool hover)
{
    SDL_Rect rect_Windw = {0, 0, w_Windw, h_Windw};
    SDL_Renderer *renderer = rendererID;
    int w = w_menu, h = h_menu;
    int x = x_menu + w_border / 2;
    int y = y_menu + w_border / 2;
    int r = r_rects;
    int wb = w_border;

    // Background Color
    SDL_SetRenderDrawColor(renderer, def_RenderColor.r, def_RenderColor.g, def_RenderColor.b, def_RenderColor.a);
    SDL_RenderFillRect(rendererID, &rect_Windw);

    // Outline Rectangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    DrawRoundedRect(renderer, x - wb / 2, y - wb / 2, w + wb, h + wb, r + wb / 2);

    // Top Body
    int h0 = (h >= 40) ? 40 : h;
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    DrawRoundedRect(renderer, x, y, w, h0, r);

    // Close Button
    int yClose = y, wClose = h0, hClose = h0 - r, xClose = x + w - wClose;
    if (hover)
        SDL_SetRenderDrawColor(renderer, 200, 6, 6, 255);
    else
        SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
    DrawRoundedRect(renderer, xClose, yClose, wClose, hClose, 15);
    SDL_Rect closeButton = {xClose, yClose, wClose, hClose};

    // Middle Body
    int y1 = y + h0 - r, h1 = (h - h0 + r >= 200) ? 200 : h - h0, r1 = 0;
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
    DrawRoundedRect(renderer, x, y1, w, h1, r1);

    // Bottom Body
    int y2 = y1 + h1 - r, h2 = (h - h0 - h1 >= r) ? h - h0 - h1 + 2 * r : h - h0 - h1;
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
    DrawRoundedRect(renderer, x, y2, w, h2, r);

    return closeButton;
}

void Menu::Quit(SDL_Renderer* renderer, SDL_Window* window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cerr << "GUI Quited" << std::endl;

    delete s_Instance;
    s_Instance = nullptr;
}
