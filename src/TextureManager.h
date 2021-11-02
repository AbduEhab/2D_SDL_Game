#pragma once

#include "Game.h"

class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const char* textureFile); 
    static void Draw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destinationRect, SDL_RendererFlip flip);
};
