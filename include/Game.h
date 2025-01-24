#pragma once

#include "Constants.hpp"

#include <SDL.h>
#include <SDL_image.h>

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>

// #include <SDL_ttf.h>

#include "AssetManager.h"
#include "Component.h"
#include "Entity.h"
#include "EntityManager.h"

class AssetManager;
enum class KEYSTATE: int {
    PRESSED,
    RELEASED,
    NONE
 };

class Game
{
private:
    bool running = false;
    SDL_Window *window; // the sdl frame

public:
    Game() = default;

    static AssetManager *asset_manager;
    static KEYSTATE key_state;
    static SDL_Keycode last_key;

    float scale = 1.f;

    [[nodiscard]] bool is_running() const;
    static SDL_Renderer *renderer; // the sdl graphics renderer
    void load_level(int level_number) const;
    void init(int width, int height);
    void process_input();
    void update(const float delta_time);
    void render(const float delta_time);
    void destroy();
};
