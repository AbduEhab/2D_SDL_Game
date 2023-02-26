#define SDL_MAIN_HANDLED

#include "Engine.h"
#include "Game.h"

int main(int argc, char *arg[])
{

    Game game = Game();

    game.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    Engine::ticks_last_frame = Clock::now();

    float ticks_last_frame = 0;

    while (game.IsRunning())
    {
        Engine::calculate_deltatime_and_wait();

        game.ProcessInput();
        game.Update(Engine::delta_time);
        game.Render();
    }

    return 0;
}


// #include <SDL.h>
// #include <stdio.h>

// int main(int argc, char *arg[])
// {
// 	// Initialize SDL
// 	if (SDL_Init(SDL_INIT_VIDEO) != 0)
// 	{
// 		printf("SDL could not initialize: Error %s\n", SDL_GetError());
// 		return 1;
// 	}

// 	// SDL Window setup
// 	SDL_Window *window = SDL_CreateWindow("SDL2 Tutorial",
// 										  SDL_WINDOWPOS_UNDEFINED,
// 										  SDL_WINDOWPOS_UNDEFINED,
// 										  640, 480, 0);

// 	if (window == nullptr)
// 	{
// 		printf("Unable to create window. Error %s\n", SDL_GetError());
// 		return 1;
// 	}

// 	// Wait for 2,000 miliseconds (2 seconds)
// 	SDL_Delay(2000);

// 	// Destroy the window and shutdown the program
// 	SDL_DestroyWindow(window);
// 	SDL_Quit();

// 	return 0;
// }