#ifndef SLIDER_H
#define SLIDER_H

#include "SDL.h"
#include "SDL_ttf.h"

class Slider
{
public:
    Slider(int x, int y, int w, int h, int Min, int Max, char c);

    void HandleEvent(const SDL_Event& e);
    void HandleKeyDown(const SDL_Event& e);
    void HandleKeyUp(const SDL_Event& e);
    void HandleDragging(const SDL_Event& e);
    void Render(SDL_Renderer* renderer);

    bool started;

    Uint8 GetValue() const;
    SDL_Rect GetThumbRect()
    {
        return thumbRect;
    }
    // bool SetDragging(bool drag)
    // {
    //     dragging = drag;
    // }

private:
    SDL_Rect sliderRect;
    SDL_Rect thumbRect;
    bool dragging;
    int minValue, maxValue;
    int value;
    char c_Slider;
    TTF_Font* font;
    SDL_Color textColor;
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
};

#endif // SLIDER_H
