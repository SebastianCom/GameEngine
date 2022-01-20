#pragma once

#include "../Libraries/box2d/include/box2d/box2d.h"
#include "Physics/PhysicsWorld.h"
#include "Math/Vector.h"

namespace fw {

    class PhysicsWorldBox2D: public PhysicsWorld
    {
    public:
        PhysicsWorldBox2D();
        virtual ~PhysicsWorldBox2D();
        virtual void Update(float deltaTime) override;
        virtual void SetGravity(vec2 gravity) override;

        b2World* Getb2World() { return m_pWorld; };

    protected:
        b2World* m_pWorld;

    };



} // namespace fw