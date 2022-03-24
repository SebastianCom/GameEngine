#pragma once

#include "Physics/PhysicsWorld.h"

class btBroadphaseInterface;
class btCollisionConfiguration;
class btCollisionShape;
class btConstraintSolver;
class btDispatcher;
class btDynamicsWorld;

namespace fw {

class EventManager;
class PhysicsBodyBullet3D;

class PhysicsWorldBullet3D : public PhysicsWorld
{
    friend PhysicsBodyBullet3D;

public:
    PhysicsWorldBullet3D(EventManager* pEventManager);
    virtual ~PhysicsWorldBullet3D();
    virtual void Update(float deltaTime) override;
    virtual void SetGravity(vec3 gravity) override;

    virtual PhysicsBody* CreateBody(TransformComponent* pTransform, bool isDynamic, float density, GameObject* pGameObject) override;
    virtual void CreateJoint(PhysicsBody* pBody, vec3 pos) override;

    // Getters
    btDynamicsWorld* GetbtWorld() { return m_pWorld; };

protected:
    btDynamicsWorld* m_pWorld = nullptr;

    btCollisionConfiguration* m_pCollisionConfiguration = nullptr;
    btDispatcher* m_pDispatcher = nullptr;
    btBroadphaseInterface* m_pBroadphase = nullptr;
    btConstraintSolver* m_pConstraintSolver = nullptr;
};

} // namespace fw