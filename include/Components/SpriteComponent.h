#pragma once

#include "../AssetManager.h"
#include "../TextureManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *_transform;
    SDL_Texture *_texture;
    SDL_Rect _sourceRect;
    SDL_Rect _destiationRect;

public:
    SDL_RendererFlip _flip = SDL_FLIP_NONE;

    SpriteComponent(std::string _textureid)
    {
        set_texture(_textureid);
    }
    void set_texture(std::string _textureid)
    {
        _texture = Game::asset_manager->get_texture(_textureid);
    }

    void Initialize()
    {
        _transform = _owner->get_component<TransformComponent>();
        _sourceRect.x = 0;
        _sourceRect.y = 0;
        _sourceRect.w = _transform->_width;
        _sourceRect.h = _transform->_height;
    }

    void Update(float delta_time)
    {
        _destiationRect.x = (int)_transform->_position.x;
        _destiationRect.y = (int)_transform->_position.y;
        _destiationRect.w = _transform->_width * _transform->_scale;
        _destiationRect.h = _transform->_height * _transform->_scale;

        if (_transform->_position.x > 800)
        {
            _transform->_velocity.x = -10;
        }
        if (_transform->_position.x < 0)
        {
            _transform->_velocity.x = 10;
        }

        if (_transform->_position.y > 600)
        {
            _transform->_velocity.y = -10;
        }
        if (_transform->_position.y < 0)
        {
            _transform->_velocity.y = 10;
        }
    }

    void Render()
    {
        TextureManager::Draw(_texture, _sourceRect, _destiationRect, _flip);
    }

    std::string ToString()
    {
        return std::string("Component<SpriteComponent>: ");
    }
};