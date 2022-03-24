#pragma once

#include "Physics/PhysicsBody.h"

class btRigidBody;

namespace fw {

class PhysicsWorldBullet3D;

class PhysicsBodyBullet3D : public PhysicsBody
{
public:
    PhysicsBodyBullet3D(PhysicsWorldBullet3D* pWorld, btRigidBody* pRigidBody);
    virtual ~PhysicsBodyBullet3D() override;

    // Getters.
    virtual vec3 GetPosition() override;
    virtual vec3 GetRotation() override;

    // Setters.
    virtual void SetTransform(vec3 pos, vec3 rot) override;

    // Forces.
    virtual void ApplyForceToCenter(vec3 force) override;

    // Custom box2d methods.
    btRigidBody* GetbtBody() { return m_pBody; }

public:
    virtual void Editor_FillInspectorWindow() override;

protected:
    PhysicsWorldBullet3D* m_pWorld = nullptr;
    btRigidBody* m_pBody = nullptr;
};

} // namespace fw
