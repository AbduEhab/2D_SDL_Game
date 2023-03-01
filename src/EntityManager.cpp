#include "EntityManager.h"

void EntityManager::Render() const
{
    for (auto &entity : entities)
    {
        entity->Render();
    }
}

void EntityManager::Update(float delta_time)
{
    for (auto &entity : entities)
    {
        entity->Update(delta_time);
    }
}

bool EntityManager::Clear()
{
    for (auto &entity : entities)
    {
        entity->Destroy();
    }

    return true;
}

size_t EntityManager::Size() const
{
    return entities.size();
}

Entity &EntityManager::AddEntity(std::string entity_name)
{
    Entity *entity = new Entity(*this, entity_name);

    entities.emplace_back(entity);

    return *entity;
}

bool EntityManager::IsEmpty() const
{
    return entities.size() == 0;
}

std::vector<Entity *> EntityManager::get_entities() const
{
    return entities;
}

void EntityManager::ListAllEntities() const
{

    std::cout << "EntityManager<EntityDump>:\n{" << std::endl;

    for (auto entity : entities)
    {
        std::cout << "\t" << entity->name << "\n\t{" << std::endl;
        entity->ListAllComponents("\t\t");

        std::cout << "\t}" << std::endl;
    }

    std::cout << "}" << std::endl;
}