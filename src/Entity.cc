#include "Entity.h"

Entity::Entity(EntityManager &manager) : manager_(manager)
{
    is_active_ = true;
}

Entity::Entity(EntityManager &manager, std::string name) : manager_(manager), name_(name)
{
    is_active_ = true;
}

void Entity::Update(float deltaTime)
{
    for (auto &component : components_)
    {
        component->Update(deltaTime);
    }
}

void Entity::Render()
{
    for (auto &component : components_)
    {
        component->Render();
    }
}

void Entity::Destroy()
{
    this->is_active_ = false;
}

bool Entity::IsActive() const
{
    return this->is_active_;
}

std::string Entity::ToString()
{
    std::string s;

    s = s.append("  ") + name_ + ":\n";

    for (auto &component : components_)
    {
        s = s.append("\t") + component->ToString();
    }

    return s + "\n";
}