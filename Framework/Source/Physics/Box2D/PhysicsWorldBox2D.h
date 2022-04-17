#pragma once

#include "../Libraries/box2d/include/box2d/box2d.h"
#include "Math/Vector.h"
#include "Physics/PhysicsWorld.h"

namespace fw {

class EventManager;
class TransformComponent;
enum class JointType;

class MyContactListener : public b2ContactListener
{
public:
    MyContactListener(EventManager* pEventManager);

    virtual void BeginContact(b2Contact* contact) override;
    
protected:
    EventManager* m_pEventManager;
};

class PhysicsWorldBox2D : public PhysicsWorld
{
public:
    PhysicsWorldBox2D(EventManager* pEventManager);
    virtual ~PhysicsWorldBox2D();
    virtual void Update(float deltaTime) override;
    virtual void SetGravity(vec3 gravity) override;

    virtual PhysicsBody* CreateBody(TransformComponent* pTransform, bool isDynamic, float density, GameObject* pGameObject) override;
    virtual  b2Joint* CreateJoint(PhysicsBody* pBody, vec3 pos, JointType jointType, PhysicsBody* otherBody) override;
    virtual  b2Joint* CreateJoint(PhysicsBody* pBody, b2Joint* jointOne, b2Joint* jointTwo, PhysicsBody* otherBody) override;


    b2World* Getb2World() { return m_pWorld; }

protected:
    b2World* m_pWorld = nullptr;
    MyContactListener* m_pContactListener = nullptr;
    b2Body* m_pGroundBody = nullptr;

    float m_TimeAccumulated = 0;
};

} // namespace fw
