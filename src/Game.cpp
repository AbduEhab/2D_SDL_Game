#include "./Game.h"
#include "../lib/glm/glm.hpp"
#include "./Constants.h"
#include <iostream>

Game::Game()
{
    isRunning = false;
}

Game::~Game()
{
}

bool Game::IsRunning() const
{
    return isRunning;
}

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVel = glm::vec2(20.0f, 20.0f);

void Game::Initialize(int width, int height)    // init SDL
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

    isRunning = true;
}

void Game::ProcessInput()
{
    SDL_Event event;       // create the SDL event object
    SDL_PollEvent(&event); // tell SDL to track the event
    switch (event.type)    // get event type and switch on it
    {
    case SDL_QUIT:         // escape key on the window
        isRunning = false; // break game loop
        break;

    case SDL_KEYDOWN:                           // if any key is pressed down
        if (event.key.keysym.sym = SDLK_ESCAPE) // if this key is the Esc key
            isRunning = false;
        break;
    }
}

void Game::Update()
{
    // while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TIME_TARGET));

    float waitTime = FRAME_TIME_TARGET - (SDL_GetTicks() - ticksLastFrame); // calculate time to wait between frames

    if (waitTime > 0 && waitTime <= FRAME_TIME_TARGET)
        SDL_Delay(waitTime); // hold exec untill the specified ms has passed

    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f; // diffrence between the time since the last frame and the current frame in seconds

    ticksLastFrame = SDL_GetTicks(); // update the lastFrameTime time to be used in the next pass

    // deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    projectilePos.x += projectileVel.x * deltaTime;
    projectilePos.y += projectileVel.y * deltaTime;
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255); //setsup the given renderer to render a specific color
    SDL_RenderClear(renderer);                         //clear back buffer with the specified color

    SDL_Rect projectile{(int)projectilePos.x, (int)projectilePos.y, 10, 10}; // create rectangle

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //setsup the given renderer to render a specific color
    SDL_RenderFillRect(renderer, &projectile);            //draw the rectange with a given renderer

    SDL_RenderPresent(renderer); // swap back and front buffer
}

//  cleaning after myself
void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}