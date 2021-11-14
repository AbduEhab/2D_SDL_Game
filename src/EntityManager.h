#pragma once

#include "Component.h"
#include "Entity.h"
#include <string>
#include <vector>
#include <iostream>

class Entity;

class EntityManager
{
private:
    std::vector<Entity *> entities_;

public:
    void Update(float delta_time);
    void Render();
    uint32_t Size();
    bool IsEmpty();
    Entity &AddEntity(std::string entity_name);
    std::vector<Entity *> get_entities() const;
    void ListAllEntities();
    bool Clear();
};