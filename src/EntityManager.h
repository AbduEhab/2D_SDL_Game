#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "Component.h"
#include "Entity.h"
#include <string>
#include <vector>

class Entity;

class EntityManager
{
private:
    std::vector<Entity *> entities;

public:
    void update(float deltaTime);
    void render();
    uint32_t size();
    bool isEmpty();
    Entity &addEntity(std::string entityName);
    std::vector<Entity *> getEntities() const;
    bool clear();
};

#endif