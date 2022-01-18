#include "Entity.h"

Entity::Entity(EntityManager &manager) : _manager(manager)
{
    is_active_ = true;
}

Entity::Entity(EntityManager &manager, std::string name) : _manager(manager), name_(name)
{
    is_active_ = true;
}

void Entity::Update(float deltaTime)
{
    for (auto &component : _components)
    {
        component->Update(deltaTime);
    }
}

void Entity::Render() const
{
    for (auto &component : _components)
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

void Entity::ListAllComponents(std::string indentation) const
{
    for (auto &component : _components_by_types)
    {
        std::cout << std::string(indentation) + std::string("Component<") + std::string(component.first->name()).substr(2) + ">" << std::endl;
    }
}

std::string Entity::ToString()
{
    std::string s;

    s = s.append("  ") + name_ + ":\n{";

    for (auto &component : _components)
    {
        s = s.append("\t") + component->ToString() + "\n";
    }

    return s + "}";
}