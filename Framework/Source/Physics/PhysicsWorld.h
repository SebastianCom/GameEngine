#pragma once


#include "Math/Vector.h"

namespace fw {

    class PhysicsWorld
    {
    protected:
        static const vec2 c_DefaultGravity;

    public:
        virtual ~PhysicsWorld() = 0 {}
        virtual void Update(float deltaTime) = 0;
        virtual void SetGravity(vec2 gravity) = 0;
    };

} // namespace fw
