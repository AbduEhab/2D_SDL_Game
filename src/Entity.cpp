#include "Entity.h"

Entity::Entity(EntityManager &manager) : manager(manager)
{
    active = true;
}

Entity::Entity(EntityManager &manager, std::string name) : manager(manager), name(name)
{
    active = true;
}

void Entity::update(float deltaTime)
{
    for (auto &component : components)
    {
        component->update(deltaTime);
    }
}

void Entity::render()
{
    for (auto &component : components)
    {
        component->Render();
    }
}

void Entity::destroy()
{
    this->active = false;
}

bool Entity::isActive() const
{
    return this->active;
}