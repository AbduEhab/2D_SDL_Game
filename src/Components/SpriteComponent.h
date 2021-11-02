#pragma once

#include "../AssetManager.h"
#include "../TextureManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform_;
    SDL_Texture *texture_;
    SDL_Rect sourceRect_;
    SDL_Rect destiationRect_;

public:
    SDL_RendererFlip flip_ = SDL_FLIP_NONE;

    SpriteComponent(std::string texture_id)
    {
        set_texture(texture_id);
    }
    void set_texture(std::string texture_id)
    {
        texture_ = Game::asset_manager->get_texture(texture_id);
    }

    void Initialize()
    {
        transform_ = owner_->get_component<TransformComponent>();
        sourceRect_.x = 0;
        sourceRect_.y = 0;
        sourceRect_.w = transform_->width_;
        sourceRect_.h = transform_->height_;
    }

    void Update(float delta_time)
    {
        destiationRect_.x = (int)transform_->position_.x;
        destiationRect_.y = (int)transform_->position_.y;
        destiationRect_.w = transform_->width_ * transform_->scale_;
        destiationRect_.h = transform_->height_ * transform_->scale_;
    }

    void Render()
    {
        TextureManager::Draw(texture_, sourceRect_, destiationRect_, flip_);
    }

    std::string ToString()
    {
        return Component::toString(std::string("SpriteComponent"));
    }
};