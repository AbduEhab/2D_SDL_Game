#include "EntityManager.h"

void EntityManager::Render() const
{
    for (auto &entity : _entities)
    {
        entity->Render();
    }
}

void EntityManager::Update(float delta_time)
{
    for (auto &entity : _entities)
    {
        entity->Update(delta_time);
    }
}

bool EntityManager::Clear()
{
    for (auto &entity : _entities)
    {
        entity->Destroy();
    }

    return true;
}

size_t EntityManager::Size() const
{
    return _entities.size();
}

Entity &EntityManager::AddEntity(std::string entity_name)
{
    Entity *entity = new Entity(*this, entity_name);

    _entities.emplace_back(entity);

    return *entity;
}

bool EntityManager::IsEmpty() const
{
    return _entities.size() == 0;
}

std::vector<Entity *> EntityManager::get_entities() const
{
    return _entities;
}

void EntityManager::ListAllEntities() const
{

    std::cout << "EntityManager<EntityDump>:\n{" << std::endl;

    for (auto entity : _entities)
    {
        std::cout << "\t" << entity->name_ << "\n\t{" << std::endl;
        entity->ListAllComponents("\t\t");

        std::cout << "\t}" << std::endl;
    }

    std::cout << "}" << std::endl;
}