#pragma once

#include "Component.h"
#include "Entity.h"

class Entity;

class EntityManager
{
private:
    std::vector<Entity *> entities;

public:
    void Update(float delta_time);
    void Render() const;
    [[NODISCARD]] size_t Size() const;
    [[NODISCARD]] bool IsEmpty() const;
    [[NODISCARD]] Entity &AddEntity(std::string entity_name);
    [[NODISCARD]] std::vector<Entity *> get_entities() const;
    void ListAllEntities() const;
    bool Clear();
};