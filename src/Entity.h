#pragma once

#include "Constants.h"

#include "Component.h"
#include "EntityManager.h"

#include <map>
#include <string>
#include <typeinfo>
#include <vector>

class Component;
class EntityManager;

class [[NODISCARD]] Entity
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
    [[NODISCARD]] bool IsActive() const;
    void Update(float delta_time);
    void Render();
    void Destroy();

    std::string ToString();

    template <typename T, typename... TArgs>
    [[NODISCARD]] T &AddComponent(TArgs &&...args) 
    {
        T *comp(new T(std::forward<TArgs>(args)...));
        comp->_owner = this;
        comp->Initialize();
        components_.emplace_back(comp);
        components_by_types_[&typeid(*comp)] = comp;
        return *comp;
    }

    template <typename T>
    [[NODISCARD]] T *get_component()
    {
        return static_cast<T *>(components_by_types_[&typeid(T)]);
    }
};