#include "EntityManager.h"

void EntityManager::render()
{
    for (auto &entity : entities)
    {
        entity->render();
    }
}

void EntityManager::update(float deltaTime)
{
    for (auto &entity : entities)
    {
        entity->update(deltaTime);
    }
}

bool EntityManager::clear()
{
    for (auto &entity : entities)
    {
        entity->destroy();
    }

    return true;
}

uint32_t EntityManager::size()
{
    return entities.size();
}

Entity &EntityManager::addEntity(std::string entityName)
{
    Entity *entity = new Entity(*this, entityName);

    entities.emplace_back(entity);

    return *entity;
}