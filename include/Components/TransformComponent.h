#pragma once

#include "../EntityManager.h"
#include "../Game.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class TransformComponent : public Component
{
public:
    glm::vec2 _position;
    glm::vec2 _velocity;

    int _width;
    int _height;
    int _scale;

    TransformComponent(int posX, int posY, int velX, int velY, int width, int height, int scale)
        : _position(glm::vec2(posX, posY)), _velocity(glm::vec2(velX, velY)),
          _width(width), _height(height), _scale(scale) {}

    void Update(float delta_time)
    {
        _position.x += _velocity.x * delta_time;
        _position.y += _velocity.y * delta_time;
    }

    std::string ToString()
    {
        return std::string("Component<TransformComponent>: (") + std::to_string(_position.x) + std::string(", ") + std::to_string(_position.y) + std::string(")");
    }
};