#ifndef COMPONENT_H
#define COMPONENT_H

#include "Entity.h"

class Entity;

class Component
{
public:
    Entity *owner;
    ~Component();
    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
};

#endif