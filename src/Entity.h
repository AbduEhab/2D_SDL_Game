#pragma once

#include "Component.h"
#include "EntityManager.h"

#include <map>
#include <string>
#include <typeinfo>
#include <vector>

class Component;
class EntityManager;

class Entity
{
private:
    EntityManager &manager_;
    bool is_active_;
    std::vector<Component *> components_;
    std::map<const std::type_info *, Component *> components_by_types_;

public:
    std::string name_;
    Entity(EntityManager &manager);
    Entity(EntityManager &manager, std::string name);
    void ListAllComponents();
    bool IsActive() const;
    void Update(float delta_time);
    void Render();
    void Destroy();

    std::string ToString();

    template <typename T, typename... TArgs>
    T &AddComponent(TArgs &&...args)
    {
        T *comp(new T(std::forward<TArgs>(args)...));
        comp->owner_ = this;
        comp->Initialize();
        components_.emplace_back(comp);
        components_by_types_[&typeid(*comp)] = comp;
        return *comp;
    }

    template <typename T>
    T *get_component()
    {
        return static_cast<T *>(components_by_types_[&typeid(T)]);
    }
};