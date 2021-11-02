#pragma once

#include "EntityManager.h"
#include "TextureManager.h"
#include <map>

class AssetManager
{
private:
    EntityManager *manager_;
    std::map<std::string, SDL_Texture *> textures_;

public:
    AssetManager(EntityManager *manager);
    ~AssetManager();
    void Clear();
    void AddTexture(std::string texture_id, const char *asset_file);
    SDL_Texture *get_texture(std::string texture_id);
};
