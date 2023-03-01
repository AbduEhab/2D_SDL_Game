#pragma once

#include "../AssetManager.h"
#include "../TextureManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destiationRect;

public:
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SpriteComponent(std::string textureid)
    {
        set_texture(textureid);
    }
    void set_texture(std::string texture_id)
    {
        texture = Game::asset_manager->get_texture(texture_id);
    }

    void Initialize()
    {
        transform = owner->get_component<TransformComponent>();
        sourceRect.x = 0;
        sourceRect.y = 0;
        sourceRect.w = transform->width;
        sourceRect.h = transform->height;
    }

    void Update([[maybe_unused]] float delta_time)
    {
        destiationRect.x = (int)transform->position.x;
        destiationRect.y = (int)transform->position.y;
        destiationRect.w = transform->width * transform->scale;
        destiationRect.h = transform->height * transform->scale;

        if (transform->position.x > 800)
        {
            transform->velocity.x = -10;
        }
        if (transform->position.x < 0)
        {
            transform->velocity.x = 10;
        }

        if (transform->position.y > 600)
        {
            transform->velocity.y = -10;
        }
        if (transform->position.y < 0)
        {
            transform->velocity.y = 10;
        }
    }

    void Render()
    {
        TextureManager::Draw(texture, sourceRect, destiationRect, flip);
    }

    std::string ToString()
    {
        return std::string("Component<SpriteComponent>: ");
    }
};