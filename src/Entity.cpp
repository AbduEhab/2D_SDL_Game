#include "Entity.h"

Entity::Entity(EntityManager &manager) : manager(manager)
{
    is_active = true;
}

Entity::Entity(EntityManager &manager, std::string name) : manager(manager), name(name)
{
    is_active = true;
}

void Entity::Update(float deltaTime)
{
    for (auto &component : components)
    {
        component->Update(deltaTime);
    }
}

void Entity::Render() const
{
    for (auto &component : components)
    {
        component->Render();
    }
}

void Entity::Destroy()
{
    this->is_active = false;
}

bool Entity::IsActive() const
{
    return this->is_active;
}

void Entity::ListAllComponents(std::string indentation) const
{
    for (auto &component : components_by_types)
    {
        std::cout << std::string(indentation) + std::string("Component<") + std::string(component.first->name()).substr(2) + ">" << std::endl;
    }
}

std::string Entity::ToString()
{
    std::string s;

    s = s.append("  ") + name + ":\n{";

    for (auto &component : components)
    {
        s = s.append("\t") + component->ToString() + "\n";
    }

    return s + "}";
}