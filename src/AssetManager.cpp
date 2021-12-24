#include "AssetManager.h"

AssetManager::AssetManager(EntityManager *manager) : _manager(manager)
{
}

void AssetManager::Clear()
{
    _textures.clear();
}

void AssetManager::AddTexture(std::string texture_id, const char *texture_file)
{
    _textures.emplace(texture_id, TextureManager::LoadTexture(texture_file));
}

SDL_Texture *AssetManager::get_texture(std::string texture_id)
{
    return _textures[texture_id];
}