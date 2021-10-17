#define SDL_MAIN_HANDLED
#include "./Constants.h"
#include "./Game.h"
#include <iostream>

int main(int argc, char *arg[])
{

    Game *game = new Game();

    game->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->isRunning())
    {
        game->processInput();
        game->update();
        game->render();
    }

    game->destroy();

    return 0;
}