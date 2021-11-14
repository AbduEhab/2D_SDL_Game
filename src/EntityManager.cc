#include "EntityManager.h"

void EntityManager::Render()
{
    for (auto &entity : entities_)
    {
        entity->Render();
    }
}

void EntityManager::Update(float delta_time)
{
    for (auto &entity : entities_)
    {
        entity->Update(delta_time);
    }
}

bool EntityManager::Clear()
{
    for (auto &entity : entities_)
    {
        entity->Destroy();
    }

    return true;
}

uint32_t EntityManager::Size()
{
    return entities_.size();
}

Entity &EntityManager::AddEntity(std::string entity_name)
{
    Entity *entity = new Entity(*this, entity_name);

    entities_.emplace_back(entity);

    return *entity;
}

std::vector<Entity *> EntityManager::get_entities() const
{
    return entities_;
}

void EntityManager::ListAllEntities()
{

    std::cout << "EntityManager<EntityDump>:\n----" << std::endl;

    for (auto entity : entities_)
    {
        std::cout << entity->name_ << std::endl;
        entity->ListAllComponents();

        std::cout << std::endl;
    }

    std::cout << "----" << std::endl;
}