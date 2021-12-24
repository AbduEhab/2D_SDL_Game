#pragma once

#include "Entity.h"

class Entity;

class Component
{
public:
    Entity *_owner;
    ~Component() {}
    virtual void Initialize() {}
    virtual void Update(float delta_time) = 0;
    virtual void Render() {}

    virtual std::string ToString()
    {
        return std::string("Method Not Implemented");
    }

protected:
    virtual std::string toString(std::string name)
    {
        return std::string("Component<" + name + ">");
    }
};