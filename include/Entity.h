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
    EntityManager &_manager;
    bool is_active_;
    std::vector<Component *> _components;
    std::map<const std::type_info *, Component *> _components_by_types;

public:
    std::string name_;
    Entity(EntityManager &manager);
    Entity(EntityManager &manager, std::string name);
    void ListAllComponents(std::string indentation = "") const;
    [[NODISCARD]] bool IsActive() const;
    void Update(float delta_time);
    void Render() const;
    void Destroy();

    std::string ToString();

    template <typename T, typename... TArgs>
    [[NODISCARD]] constexpr T &AddComponent(TArgs &&...args)
    {
        T *comp(new T(std::forward<TArgs>(args)...));
        comp->_owner = this;
        comp->Initialize();
        _components.emplace_back(comp);
        _components_by_types[&typeid(*comp)] = comp;
        return *comp;
    }

    template <typename T>
    [[NODISCARD]] constexpr T *get_component() const
    {
        return static_cast<T *>(_components_by_types[&typeid(T)]);
    }

    template <typename T>
    [[NODISCARD]] constexpr bool HasComponent() const
    {
        return !(_components_by_types[&typeid(T)] == nullptr);
    }
};