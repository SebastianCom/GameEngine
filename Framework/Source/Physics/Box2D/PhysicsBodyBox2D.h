#pragma once

#include "../Libraries/box2d/include/box2d/box2d.h"
#include "Math/Vector.h"
#include "Physics/PhysicsBody.h"

namespace fw {

class PhysicsBodyBox2D : public PhysicsBody
{
public:
    PhysicsBodyBox2D(b2Body* pBody);
    virtual ~PhysicsBodyBox2D();

    // Getters.
    virtual vec3 GetPosition() override;
    virtual vec3 GetRotation() override;

    // Setters.
    virtual void SetTransform(vec3 pos, vec3 rot) override;
    virtual void SetEnabled(bool bEnabled) override;

    // Forces.
    virtual void ApplyForceToCenter(vec3 force) override;

    // Custom box2d methods.
    b2Body* Getb2Body() { return m_pBody; }

public:
    virtual void Editor_FillInspectorWindow() override;

protected:
    b2Body* m_pBody = nullptr;
};

} // namespace fw
