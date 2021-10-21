#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../EntityManager.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../Game.h"

class Transform : public Component
{
public:
    glm::vec2 position;
    glm::vec2 velocity;

    int width;
    int height;
    int scale;

    Transform(int posX, int posY, int velX, int velY, int width, int height, int scale)
        : position(glm::vec2(posX, posY)), velocity(glm::vec2(velX, velY)),
          width(width), height(height), scale(scale) {}

    void init()
    {
    }

    void update(float deltaTime)
    {
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
    }

    void render()
    {
        SDL_Rect transformRectangle{(int)position.x,(int) position.y, width, height};

        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(Game::renderer, &transformRectangle); //draw the rectange with a given renderer
    }
};

#endif