#include "AssetManager.h"

AssetManager::AssetManager(EntityManager *manager) : manager_(manager)
{
}

void AssetManager::Clear()
{
    textures_.clear();
}

void AssetManager::AddTexture(std::string texture_id, const char *texture_file)
{
    textures_.emplace(texture_id, TextureManager::LoadTexture(texture_file));
}

SDL_Texture *AssetManager::get_texture(std::string texture_id)
{
    return textures_[texture_id];
}