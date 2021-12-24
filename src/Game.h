#pragma once

#include "Constants.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "AssetManager.h"
#include "Component.h"
#include "Entity.h"
#include "EntityManager.h"

class AssetManager;

class Game
{
private:
    bool _is_running;
    SDL_Window *_window; // the sdl frame
    SDL_Event _event;

public:
    Game();
    ~Game();
    static AssetManager *asset_manager;
    int ticks_last_frame;
    [[NODISCARD]] bool IsRunning() const;
    static SDL_Renderer *renderer; // the sdl graphics renderer
    void LoadLevel(int level_number) const;
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};
