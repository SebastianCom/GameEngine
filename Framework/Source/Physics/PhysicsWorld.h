#pragma once

#include "Math/Vector.h"

namespace fw {

class GameObject;
class PhysicsBody;
class TransformComponent;

class PhysicsWorld
{
protected:
    static const vec3 c_DefaultGravity;

public:
    virtual ~PhysicsWorld() = 0 {}
    virtual void Update(float deltaTime) = 0;
    virtual void SetGravity(vec3 gravity) = 0;

    virtual PhysicsBody* CreateBody(TransformComponent* pTransform, bool isDynamic, float density, GameObject* pGameObject) = 0;
    virtual void CreateJoint(PhysicsBody* pBody, vec3 pos) = 0;
};

} // namespace fw
