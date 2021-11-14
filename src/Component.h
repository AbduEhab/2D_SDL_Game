#pragma once

#include "Entity.h"
#include <string>

class Entity;

class Component
{
public:
    Entity *owner_;
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