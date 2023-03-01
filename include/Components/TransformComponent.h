#pragma once

#include "../EntityManager.h"
#include "../Game.h"
#include <SDL.h>
#include <glm/glm.hpp>

class TransformComponent : public Component
{
public:
    glm::vec2 position;
    glm::vec2 velocity;

    int width;
    int height;
    int scale;

    TransformComponent(int posX, int posY, int velX, int velY, int width, int height, int scale)
        : position(glm::vec2(posX, posY)), velocity(glm::vec2(velX, velY)),
          width(width), height(height), scale(scale) {}

    void Update(float delta_time)
    {
        position.x += velocity.x * delta_time;
        position.y += velocity.y * delta_time;
    }

    std::string ToString()
    {
        return std::string("Component<TransformComponent>: (") + std::to_string(position.x) + std::string(", ") + std::to_string(position.y) + std::string(")");
    }
};