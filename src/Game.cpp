#include <glm/glm.hpp>
#include <iostream>

#include "./Constants.h"
#include "./Game.h"
#include "Components/Transform.h"

EntityManager manager;
SDL_Renderer *Game::renderer;

Game::Game()
{
    running = false;
}

Game::~Game()
{
}

bool Game::isRunning() const
{
    return running;
}

void Game::initialize(int width, int height) // init SDL
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error init sdl." << std::endl;
        return;
    }
    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
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

    loadLevel(0);

    running = true;
}

void Game::loadLevel(int levelNumber)
{
    Entity &entity(manager.addEntity("first dot"));

    entity.addComponent<Transform>(0, 0, 10, 10, 20, 20, 1);
}

void Game::processInput()
{
    SDL_Event event;       // create the SDL event object
    SDL_PollEvent(&event); // tell SDL to track the event
    switch (event.type)    // get event type and switch on it
    {
    case SDL_QUIT:       // escape key on the window
        running = false; // break game loop
        break;

    case SDL_KEYDOWN:                           // if any key is pressed down
        if (event.key.keysym.sym = SDLK_ESCAPE) // if this key is the Esc key
            running = false;
        break;
    }
}

void Game::update()
{
    float waitTime = FRAME_TIME_TARGET - (SDL_GetTicks() - ticksLastFrame); // calculate time to wait between frames

    if (waitTime > 0 && waitTime <= FRAME_TIME_TARGET)
        SDL_Delay(waitTime); // hold exec untill the specified ms has passed

    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f; // diffrence between the time since the last frame and the current frame in seconds

    ticksLastFrame = SDL_GetTicks(); // update the lastFrameTime time to be used in the next pass

    manager.update(deltaTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255); //set up the given renderer to render a specific color
    SDL_RenderClear(renderer);                         //clear back buffer with the specified color

    manager.render();

    SDL_RenderPresent(renderer); // swap back and front buffer
}

//  cleaning after myself
void Game::destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}