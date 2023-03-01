#define SDL_MAIN_HANDLED

#include "Engine.h"
#include "Game.h"

int main(int argc, char *arg[])
{

    Game game = Game();

    game.Initialize(800, 600);

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