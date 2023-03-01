#pragma once

#include "Constants.hpp"

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
    EntityManager &manager;
    bool is_active;
    std::vector<Component *> components;
    std::map<const std::type_info *, Component *> components_by_types;

public:
    std::string name;
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
        comp->owner = this;
        comp->Initialize();
        components.emplace_back(comp);
        components_by_types[&typeid(*comp)] = comp;
        return *comp;
    }

    template <typename T>
    [[NODISCARD]] constexpr T *get_component()
    {
        return static_cast<T *>(components_by_types[&typeid(T)]);
    }

    template <typename T>
    [[NODISCARD]] constexpr bool HasComponent()
    {
        return !(components_by_types[&typeid(T)] == nullptr);
    }
};