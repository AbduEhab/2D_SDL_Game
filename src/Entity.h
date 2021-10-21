#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include "EntityManager.h"

#include <string>
#include <vector>

class Component;
class EntityManager;

class Entity
{
private:
    EntityManager &manager;
    bool active;
    std::vector<Component *> components;

public:
    std::string name;
    Entity(EntityManager &manager);
    Entity(EntityManager &manager, std::string name);
    bool isActive() const;
    void update(float deltaTime);
    void render();
    void destroy();

    template <typename T, typename... TArgs>
    T &addComponent(TArgs &&...args)
    {
        T *comp(new T(std::forward<TArgs>(args)...));
        comp->owner = this;
        comp->init();
        components.push_back(comp);
        return *comp;
    }
};

#endif