#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *textureFile)
{
    SDL_Surface *surface = IMG_Load(textureFile);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer_, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect sourceRect, SDL_Rect destinationRect, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer_, texture, &sourceRect, &destinationRect, 0, 0, flip);
}
