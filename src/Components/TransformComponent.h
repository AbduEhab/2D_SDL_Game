#pragma once

#include "../EntityManager.h"
#include "../Game.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class TransformComponent : public Component
{
public:
    glm::vec2 position_;
    glm::vec2 velocity_;

    int width_;
    int height_;
    int scale_;

    TransformComponent(int posX, int posY, int velX, int velY, int width, int height, int scale)
        : position_(glm::vec2(posX, posY)), velocity_(glm::vec2(velX, velY)),
          width_(width), height_(height), scale_(scale) {}

    void Update(float delta_time)
    {
        position_.x += velocity_.x * delta_time;
        position_.y += velocity_.y * delta_time;
    }

    std::string ToString()
    {
        return Component::toString(std::string("TransformComponent"));
    }
};