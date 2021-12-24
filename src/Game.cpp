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
    _window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
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
    asset_manager->AddTexture("tank-right", "../../assets/images/tank-big-right.png");

    Entity &entity(manager.AddEntity("first dot"));
    entity.AddComponent<TransformComponent>(0, 0, 10, 10, 20, 20, 1);
    entity.AddComponent<SpriteComponent>("tank-right");

    Debug(manager.ListAllEntities())
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

void Game::Update()
{
    float waitTime = FRAME_TIME_TARGET - (SDL_GetTicks() - ticks_last_frame); // calculate time to wait between frames

    if (waitTime > 0 && waitTime <= FRAME_TIME_TARGET)
        SDL_Delay(waitTime); // hold exec untill the specified ms has passed

    float delta_time = (SDL_GetTicks() - ticks_last_frame) / 1000.0f; // diffrence between the time since the last frame and the current frame in seconds

    ticks_last_frame = SDL_GetTicks(); // update the lastFrameTime time to be used in the next pass

    manager.Update(delta_time);
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