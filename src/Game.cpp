#include <iostream>

#include <Components/SpriteComponent.h>
#include <Components/TransformComponent.h>
#include <Game.h>

EntityManager manager;
AssetManager *Game::asset_manager = new AssetManager(&manager);
SDL_Renderer *Game::renderer;

[[NODISCARD]] bool Game::IsRunning() const
{
    return is_running;
}

void Game::Initialize(int width, int height) // init SDL
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error init sdl." << std::endl;
        return;
    }
    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "error with window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cerr << "error with renderer" << std::endl;
        return;
    }

    LoadLevel(0);

    is_running = true;
}

void Game::LoadLevel([[maybe_unused]] int level_number) const
{
    asset_manager->AddTexture("tank-right", "../assets/images/tank-big-right.png");

    Entity &entity(manager.AddEntity("first dot"));
    entity.AddComponent<TransformComponent>(0, 10, 10, 10, 20, 20, 1);
    entity.AddComponent<SpriteComponent>("tank-right");
}

void Game::ProcessInput()
{
    // create the SDL event object
    SDL_PollEvent(&event); // tell SDL to track the event
    switch (event.type)    // get event type and switch on it
    {
    case SDL_QUIT:          // escape key on the window
        is_running = false; // break game loop
        break;

    case SDL_KEYDOWN:                           // if any key is pressed down
        if (event.key.keysym.sym = SDLK_ESCAPE) // if this key is the Esc key
            is_running = false;
        break;
    }
}

static inline TimePoint time_s = Clock::now();
static inline uint8_t frames = 1;

void Game::Update(float delta_time)
{
    manager.Update(delta_time);

    bool res = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - time_s).count() >= FRAME_TIME_TARGET;

    if (res) [[unlikely]]
    {
        SDL_SetWindowTitle(window, (std::to_string(frames /*1000 / delta_time*/).append(" | ").append(std::to_string(delta_time))).c_str());
        debug_print("Game Update: ", manager.get_entities()[0]->get_component<TransformComponent>()->ToString());
        time_s = Clock::now();
        frames = 1;
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
    SDL_DestroyWindow(window);
    SDL_Quit();
}