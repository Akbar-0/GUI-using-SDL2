#ifndef SDL2_GFX_H
#define SDL2_GFX_H


class SDL2_gfx
{
    public:
        SDL2_gfx();
        virtual ~SDL2_gfx();
        SDL2_GFXPRIMITIVES_SCOPE int roundedRectangleColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 rad, Uint32 color);
        SDL2_GFXPRIMITIVES_SCOPE int roundedRectangleRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1,
		Sint16 x2, Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    protected:

    private:
};

#endif // SDL2_GFX_H
