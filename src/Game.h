#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Component.h"
#include "Entity.h"
#include "EntityManager.h"

class Game
{
private:
    bool running;
    SDL_Window *window; // the sdl frame

public:
    Game();
    ~Game();
    int ticksLastFrame;
    bool isRunning() const;
    static SDL_Renderer *renderer; // the sdl graphics renderer
    void loadLevel(int levelNumber);
    void initialize(int width, int height);
    void processInput();
    void update();
    void render();
    void destroy();
};

#endif