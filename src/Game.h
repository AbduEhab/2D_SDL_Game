#pragma once

#define DEBUG(x)    \
                    \
    if (DEBUG_ONLY) \
        x;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "AssetManager.h"
#include "Component.h"
#include "Entity.h"
#include "EntityManager.h"

class AssetManager;

class Game
{
private:
    bool is_running_;
    SDL_Window *window_; // the sdl frame

public:
    Game();
    ~Game();
    static AssetManager *asset_manager;
    int ticks_last_frame;
    bool IsRunning() const;
    static SDL_Renderer *renderer_; // the sdl graphics renderer
    void LoadLevel(int level_number);
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};
