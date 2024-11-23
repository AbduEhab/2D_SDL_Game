#include <iostream>

#include <Components/SpriteComponent.h>
#include <Components/TransformComponent.h>
#include <Game.h>

EntityManager manager;
AssetManager *Game::asset_manager = new AssetManager(&manager);
SDL_Renderer *Game::renderer;

[[nodiscard]] bool Game::is_running() const
{
    return running;
}

void Game::init(int width, int height) // init SDL
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

    // init imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    load_level(0);

    running = true;
}

void Game::load_level([[maybe_unused]] int level_number) const
{
    asset_manager->clear();

    asset_manager->add_texture("tank-right", "../assets/images/tank-big-right.png");

    switch (level_number)
    {
    case 0:
        Entity &entity(manager.add_entity("first dot"));
        (void)entity.add_component<TransformComponent>(0, 10, 10, 10, 20, 20, 1);
        (void)entity.add_component<SpriteComponent>("tank-right");
        break;
    }
}

void Game::process_input()
{
    // create the SDL event object
    SDL_PollEvent(&event); // tell SDL to track the event
    switch (event.type)    // get event type and switch on it
    {
    case SDL_QUIT:       // escape key on the window
        running = false; // break game loop
        break;

    case SDL_KEYDOWN: // if any key is pressed down

        event.key.keysym.sym = SDLK_ESCAPE;

        if (event.key.keysym.sym) // if this key is the Esc key
            running = false;
        break;
    }

    ImGui_ImplSDL2_ProcessEvent(&event);
}

TimePoint time_s = Clock::now();

void Game::update(float delta_time)
{
    manager.update(delta_time);

    bool res = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - time_s).count() >= FRAME_TIME_TARGET;

    if (res) [[unlikely]]
    {
        SDL_SetWindowTitle(window, (std::to_string(1 / delta_time).append(" | ").append(std::to_string(delta_time))).append(" | ").append(std::to_string(SDL_GetTicks64())).c_str());
        debug_print("Game Update: ", manager.get_entities()[0]->get_component<TransformComponent>()->to_string());
        time_s = Clock::now();
    }
}

void Game::render()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("test");
    ImGui::Text("Hello, world!");
    ImGui::End();

    ImGui::Render();

    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255); // set up the given renderer to render a specific color
    SDL_RenderClear(renderer);                         // clear back buffer with the specified color

    manager.render();

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

    SDL_RenderPresent(renderer); // swap back and front buffer
}

//  cleaning after myself
void Game::destroy()
{
    // imgui
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // sdl
    asset_manager->clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}