#include "Slider.h"

Slider::Slider(int x, int y, int w, int h, int Min, int Max, char c)
    : sliderRect{x, y, w, h}, minValue(Min), maxValue(Max), value(Min), c_Slider(c), dragging(false), font(nullptr), textSurface(nullptr), textTexture(nullptr)
{
    thumbRect = {x, y + h / 2 - 10, 20, 20}; // Initialize thumb position
    // Initialize SDL_ttf and load font
    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init Error: %s", TTF_GetError());
        // Handle the error appropriately
    }

    font = TTF_OpenFont("./Atop-R99O3.ttf", 20);
}

void Slider::HandleKeyDown(const SDL_Event& e)
{
    if (e.button.x >= thumbRect.x && e.button.x <= thumbRect.x + thumbRect.w &&
            e.button.y >= thumbRect.y && e.button.y <= thumbRect.y + thumbRect.h)
    {
        dragging = true;
        started = true;
    }
}

void Slider::HandleKeyUp(const SDL_Event& e)
{
    dragging = false;
}

void Slider::HandleDragging(const SDL_Event& e)
{
    if (e.type == SDL_MOUSEMOTION && dragging)
    {
        int newX = e.motion.x;
        thumbRect.x = newX - thumbRect.w / 2;
        if (thumbRect.x < sliderRect.x) thumbRect.x = sliderRect.x;
        if (thumbRect.x > sliderRect.x + sliderRect.w - thumbRect.w) thumbRect.x = sliderRect.x + sliderRect.w - thumbRect.w;
        value = minValue + (thumbRect.x - sliderRect.x) * (maxValue - minValue) / (sliderRect.w - thumbRect.w);
    }
}

void Slider::HandleEvent(const SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.x >= thumbRect.x && e.button.x <= thumbRect.x + thumbRect.w &&
                e.button.y >= thumbRect.y && e.button.y <= thumbRect.y + thumbRect.h)
        {
            dragging = true;
        }
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
        dragging = false;
    }
    else if (e.type == SDL_MOUSEMOTION && dragging)
    {
        int newX = e.motion.x;
        thumbRect.x = newX - thumbRect.w / 2;
        if (thumbRect.x < sliderRect.x) thumbRect.x = sliderRect.x;
        if (thumbRect.x > sliderRect.x + sliderRect.w - thumbRect.w) thumbRect.x = sliderRect.x + sliderRect.w - thumbRect.w;
        value = minValue + (thumbRect.x - sliderRect.x) * (maxValue - minValue) / (sliderRect.w - thumbRect.w);
    }
}

void Slider::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderFillRect(renderer, &sliderRect);

    if(font == nullptr)
        SDL_Log("Failed to load font", font);

    if(c_Slider == 'R'){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        textColor = {0, 255, 255, 255};
        textSurface = TTF_RenderText_Solid(font, "R", textColor);
    }
    else if(c_Slider == 'G'){
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        textColor = {255, 0, 255, 255};
        textSurface = TTF_RenderText_Solid(font, "G", textColor);
    }
    else if(c_Slider == 'B'){
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        textColor = {255, 255, 0, 255};
        textSurface = TTF_RenderText_Solid(font, "B", textColor);
    }
    else if(c_Slider == 'A'){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        textColor = {0, 0, 0, 255};
        textSurface = TTF_RenderText_Solid(font, "A", textColor);
    }
    SDL_RenderFillRect(renderer, &thumbRect);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderDrawRect(renderer, &thumbRect);

    if (textSurface != nullptr) {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture != nullptr) {
            SDL_Rect renderQuad = { thumbRect.x + 3, thumbRect.y - 2, textSurface->w, textSurface->h };
            SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

Uint8 Slider::GetValue() const
{
    return value;
}
