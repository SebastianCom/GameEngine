#include "CoreHeaders.h"

#include "PhysicsWorldBullet3D.h"
#include "PhysicsBodyBullet3D.h"
#include "Events/Event.h"
#include "Events/EventManager.h"
#include "Components/TransformComponent.h"
#include "Objects/GameObject.h"
#include "btBulletDynamicsCommon.h"

namespace fw {

EventManager* g_pEventManager;

PhysicsWorldBullet3D::PhysicsWorldBullet3D(EventManager* pEventManager)
{
    m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
    m_pDispatcher = new btCollisionDispatcher( m_pCollisionConfiguration );
    m_pBroadphase = new btDbvtBroadphase();
    m_pConstraintSolver = new btSequentialImpulseConstraintSolver;

    m_pWorld = new btDiscreteDynamicsWorld( m_pDispatcher, m_pBroadphase, m_pConstraintSolver, m_pCollisionConfiguration );
    m_pWorld->setGravity( btVector3(c_DefaultGravity.x, c_DefaultGravity.y, c_DefaultGravity.z) );

    g_pEventManager = pEventManager;
}

PhysicsWorldBullet3D::~PhysicsWorldBullet3D()
{
    delete m_pWorld;

    delete m_pConstraintSolver;
    delete m_pBroadphase;
    delete m_pDispatcher;
    delete m_pCollisionConfiguration;
}

void PhysicsWorldBullet3D::Update(float deltaTime)
{
    m_pWorld->stepSimulation( deltaTime, 0 );
}

void PhysicsWorldBullet3D::SetGravity(vec3 gravity)
{
    m_pWorld->setGravity( btVector3(gravity.x, gravity.y, gravity.z) );
}

PhysicsBody* PhysicsWorldBullet3D::CreateBody(TransformComponent* pTransform, bool isDynamic, float density, GameObject* pGameObject)
{
    vec3 pos = pTransform->GetPosition();
    vec3 rot = pTransform->GetRotation();

    // Setup the position and orientation transform for the object.
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin( btVector3(pos.x, pos.y, pos.z) );
    transform.setRotation( btQuaternion(rot.x, rot.y, rot.z) );

    // Create the shape, ideally these would be shared between objects.
    vec3 scale = pTransform->GetScale();
    btCollisionShape* pShape = new btBoxShape( btVector3(scale.x, scale.y, scale.z)/2 );

    // Density/mass of 0 means the object is static.
    assert( isDynamic || density == 0.0f );

    // For dynamic objects, calculate the center of inertia based on the mass/density and shape.
    btVector3 localInertia(0,0,0);
    if( isDynamic )
    {
        pShape->calculateLocalInertia( density, localInertia );
    }

    // Create a motion state object, this can provide callbacks for syncing the physics object to our transform,
    // but would require us overriding this class.
    btMotionState* pMotionState = new btDefaultMotionState( transform );

    // Create the rigid body.
    btRigidBody::btRigidBodyConstructionInfo rbInfo( density, pMotionState, pShape, localInertia );
    btRigidBody* pRigidBody = new btRigidBody( rbInfo );
    pRigidBody->setUserPointer( pGameObject );

    // Add it to the world.
    m_pWorld->addRigidBody( pRigidBody );

    // Wrap it in our physic body class and return it.
    PhysicsBodyBullet3D* pBody = new PhysicsBodyBullet3D( this, pRigidBody );
    return pBody;
}

b2Joint* PhysicsWorldBullet3D::CreateJoint(PhysicsBody* pBody, vec3 pos, JointType jointType, PhysicsBody* otherBody)
{
    assert( false ); // implement this.
    return nullptr;
}

b2Joint* PhysicsWorldBullet3D::CreateJoint(PhysicsBody* pBody, b2Joint* jointOne, b2Joint* jointTwo, PhysicsBody* otherBody)
{
    return nullptr;
}

} // namespace fw

