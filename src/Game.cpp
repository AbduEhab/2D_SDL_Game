#include <glm/glm.hpp>
#include <iostream>

#include "./Game.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

EntityManager manager;
AssetManager *Game::asset_manager = new AssetManager(&manager);
SDL_Renderer *Game::renderer;

Game::Game()
{
    _is_running = false;
}

Game::~Game()
{
}

[[NODISCARD]] bool Game::IsRunning() const
{
    return _is_running;
}

void Game::Initialize(int width, int height) // init SDL
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error init sdl." << std::endl;
        return;
    }
    _window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
    if (!_window)
    {
        std::cerr << "error with window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(_window, -1, 0);
    if (!renderer)
    {
        std::cerr << "error with renderer" << std::endl;
        return;
    }

    LoadLevel(0);

    _is_running = true;
}

void Game::LoadLevel(int level_number) const
{
    asset_manager->AddTexture("tank-right", "../assets/images/tank-big-right.png");

    Entity &entity(manager.AddEntity("first dot"));
    entity.AddComponent<TransformComponent>(0, 10, 10, 10, 20, 20, 1);
    entity.AddComponent<SpriteComponent>("tank-right");
}

void Game::ProcessInput()
{
    // create the SDL event object
    SDL_PollEvent(&_event); // tell SDL to track the event
    switch (_event.type)    // get event type and switch on it
    {
    case SDL_QUIT:           // escape key on the window
        _is_running = false; // break game loop
        break;

    case SDL_KEYDOWN:                            // if any key is pressed down
        if (_event.key.keysym.sym = SDLK_ESCAPE) // if this key is the Esc key
            _is_running = false;
        break;
    }
}

inline TimePoint time_s = Clock::now();
inline uint8_t frames = 0;

void Game::Update(float delta_time)
{
    manager.Update(delta_time);

    bool res = (Clock::now() - time_s).count() * 1e-9 >= 1;

    if (res)
    {
        SDL_SetWindowTitle(_window, (std::to_string(frames).append(" | ").append(std::to_string(delta_time))).c_str());
        DebugPrint(manager.get_entities()[0]->get_component<TransformComponent>()->ToString());
        time_s = Clock::now();
        frames = 0;
    }

    frames++;
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255); // set up the given renderer to render a specific color
    SDL_RenderClear(renderer);                         // clear back buffer with the specified color

    manager.Render();

    SDL_RenderPresent(renderer); // swap back and front buffer
}

//  cleaning after myself
void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}