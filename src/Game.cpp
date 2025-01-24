#include <iostream>

#include <Components/ControlComponent.h>
#include <Components/SpriteComponent.h>
#include <Components/TransformComponent.h>
#include <Game.h>

EntityManager manager;
AssetManager *Game::asset_manager = new AssetManager(&manager);
SDL_Renderer *Game::renderer;
SDL_Event Game::event;
KEYSTATE Game::key_state;
SDL_Keycode Game::last_key;

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

    SDL_GL_SetSwapInterval(VSYNC); // enable vsync

    // init imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    load_level(0);

    running = true;
}

void Game::load_level([[maybe_unused]] int level_number) const
{
    asset_manager->clear();

    asset_manager->add_texture("tank-right", "../assets/images/tank-big-right.png");
    asset_manager->add_texture("chopper", "../assets/images/chopper-spritesheet.png");

    switch (level_number)
    {
    case 0:
        Entity &tank_entity = manager.add_entity("tank");
        (void)tank_entity.add_component<TransformComponent>(0, 10, 10, 10, 20, 20, 1);
        (void)tank_entity.add_component<SpriteComponent>("tank-right");

        Entity &chopper_entity = manager.add_entity("chopper");
        (void)chopper_entity.add_component<TransformComponent>(0, 0, 0, 0, 32, 32, 1);
        (void)chopper_entity.add_component<SpriteComponent>("chopper", 2, 90, true, false);
        (void)chopper_entity.add_component<ControlComponent>("w", "s", "a", "d", "space");

        break;
    }
}

void Game::process_input()
{
    SDL_Event local_event;
    bool state_updated = false;
    // poll for events
    while (SDL_PollEvent(&local_event))
    {
        Game::event = local_event;
        ImGui_ImplSDL2_ProcessEvent(&event);

        switch (event.type) // get event type and switch on it
        {
        case SDL_QUIT:       // escape key on the window
            running = false; // break game loop
            break;

        case SDL_KEYDOWN: // if any key is pressed down

            if (!state_updated) [[unlikely]]
            {
                debug_print("Key pressed: ", (char)event.key.keysym.sym, ", State: pressed");
                key_state = KEYSTATE::PRESSED;
                last_key = event.key.keysym.sym;
                state_updated = true;
            }

            if (event.key.keysym.sym == SDLK_ESCAPE) // if this key is the Esc key
            {
                print("Escape key pressed");
                running = false;
            }
            else if (event.key.keysym.sym == SDLK_q)
            {
                print("Q key pressed, quitting...");
                running = false;
            }
            break;

        case SDL_KEYUP: // if any key is released

            if (!state_updated) [[unlikely]]
            {
                debug_print("Key pressed: ", (char)event.key.keysym.sym, "State: released");
                key_state = KEYSTATE::RELEASED;
                state_updated = true;
            }
            break;

        default:
            if (!state_updated) [[unlikely]]
                key_state = KEYSTATE::NONE;
            break;
        }
    }
}

TimePoint time_s = Clock::now();

void Game::update(const float delta_time)
{
    manager.update(delta_time);

    bool res = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - time_s).count() >= FRAME_TIME_TARGET;

    if (res) [[unlikely]]
    {
        SDL_SetWindowTitle(window, (std::to_string(1 / delta_time).append(" | ").append(std::to_string(delta_time))).append(" | ").append(std::to_string(SDL_GetTicks64())).c_str());
        // debug_print("Game Update: ", manager.get_entities()[0]->get_component<TransformComponent>()->to_string());
        // debug_print("Game input: ", std::to_string(event.key.keysym.sym));
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

    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255); // set up the given renderer to render a specific color
    SDL_RenderClear(renderer);                         // clear back buffer with the specified color

    manager.render();

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

    SDL_RenderPresent(renderer); // swap back and front buffer
}

void Game::destroy()
{
    // imgui
    print("Destroying ImGui Context");
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // sdl
    print("Clearing Asset Manager");
    asset_manager->clear();

    print("Destroying SDL Renderer");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}