#pragma once

#include "Math/Vector.h"

namespace fw {

class GameObject;
class PhysicsBody;
class TransformComponent;
enum class JointType;

class PhysicsWorld
{
protected:
    static const vec3 c_DefaultGravity;

public:
    virtual ~PhysicsWorld() = 0 {}
    virtual void Update(float deltaTime) = 0;
    virtual void SetGravity(vec3 gravity) = 0;

    virtual PhysicsBody* CreateBody(TransformComponent* pTransform, bool isDynamic, float density, GameObject* pGameObject) = 0;
    virtual  b2Joint* CreateJoint(PhysicsBody* pBody, vec3 pos, JointType jointType, PhysicsBody* otherBody) = 0;
    virtual  b2Joint* CreateJoint(PhysicsBody* pBody, b2Joint* jointOne, b2Joint* jointTwo, PhysicsBody* otherBody) = 0;
};

} // namespace fw
