#pragma once

#include "Events/EventManager.h"

namespace fw {

class Event;

class GameCore : public EventListener
{
public:
    virtual ~GameCore() = 0 {}

    virtual void StartFrame(float deltaTime) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
};

} // namespace fw
