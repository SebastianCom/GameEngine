#pragma once

#include "Math/Vector.h"

namespace fw {

class PhysicsBody
{
public:
    virtual ~PhysicsBody() = 0 {}

    // Getters.
    virtual vec3 GetPosition() = 0;
    virtual vec3 GetRotation() = 0;

    // Setters.
    virtual void SetTransform(vec3 pos, vec3 rot) = 0;

    // Forces.
    virtual void ApplyForceToCenter(vec3 force) = 0;

public:
    virtual void Editor_FillInspectorWindow() = 0;
};

} // namespace fw
