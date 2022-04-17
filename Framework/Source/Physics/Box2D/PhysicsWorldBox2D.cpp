#include "PhysicsWorldBox2D.h"
#include "PhysicsBodyBox2D.h"

#include "Components/TransformComponent.h"
#include "Objects/GameObject.h"
#include "Events/EventManager.h"
#include "Events/Event.h"

namespace fw {

//=======================
// MyContactListener.
//=======================
MyContactListener::MyContactListener(EventManager* pEventManager)
    : m_pEventManager( pEventManager )
{
}

void MyContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* pFixtureA = contact->GetFixtureA();
    b2Fixture* pFixtureB = contact->GetFixtureB();

    b2Body* pBodyA = pFixtureA->GetBody();
    b2Body* pBodyB = pFixtureB->GetBody();

    GameObject* pObjectA = reinterpret_cast<GameObject*>( pBodyA->GetUserData().pointer );
    GameObject* pObjectB = reinterpret_cast<GameObject*>( pBodyB->GetUserData().pointer );

    // Create an event saying Object A and Object B hit each other.
    CollisionEvent* pCollision = new CollisionEvent( pObjectA, pObjectB );
    m_pEventManager->AddEvent( pCollision );
}

//=======================
// PhysicsWorldBox2D
//=======================
PhysicsWorldBox2D::PhysicsWorldBox2D(EventManager* pEventManager)
{
    m_pWorld = new b2World( c_DefaultGravity );

    m_pContactListener = new MyContactListener( pEventManager );
    m_pWorld->SetContactListener( m_pContactListener );

    // Create a ground body for joints in future.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    m_pGroundBody = m_pWorld->CreateBody( &bodyDef );
}

PhysicsWorldBox2D::~PhysicsWorldBox2D()
{
    delete m_pContactListener;
    delete m_pWorld;
}

void PhysicsWorldBox2D::Update(float deltaTime)
{
    float timeStep = 1/60.0f;

    bool didAWorldStep = false;
    m_TimeAccumulated += deltaTime;

    while( m_TimeAccumulated >= timeStep )
    {
        didAWorldStep = true;
        m_pWorld->Step( timeStep, 8, 3 );
        m_TimeAccumulated -= timeStep;
    }

    if( didAWorldStep == false )
    {
        m_pWorld->ClearForces();
    }
}

//void PhysicsWorldBox2D::Draw(Camera* pCamera, Material* pMaterial)
//{
//    m_pWorld->DebugDraw();
//
//    //Rebuild a mesh (either here or in Box2DDebugDraw, it's up to you)
//    pMesh->Create( pass in the verts 
//    //Draw the mesh after everything else.
//    pMesh->Draw( camera, material, ... )
//}

void PhysicsWorldBox2D::SetGravity(vec3 gravity)
{
    m_pWorld->SetGravity( gravity );
}

PhysicsBody* PhysicsWorldBox2D::CreateBody(TransformComponent* pTransform, bool isDynamic, float density, GameObject* pGameObject)
{
    vec3 pos = pTransform->GetPosition();
    vec3 rot = pTransform->GetRotation();
    vec3 scale = pTransform->GetScale();

    // Setup the body definition structure.
    b2BodyDef bodyDef;
    bodyDef.position.Set( pos.x, pos.y );
    bodyDef.angle = -rot.z / 180.0f * PI;
    if( isDynamic )
    {
        bodyDef.type = b2_dynamicBody;
    }
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>( pGameObject );

    // Setup the shape.
    b2PolygonShape shape;
    shape.SetAsBox( scale.x/2, scale.y/2 );

    // Setup the fixture definition with the shape.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = density;

    // Create the body and the fixture.
    b2Body* pBody = m_pWorld->CreateBody( &bodyDef );
    pBody->CreateFixture( &fixtureDef );

    return new PhysicsBodyBox2D( pBody );
}

b2Joint* PhysicsWorldBox2D::CreateJoint(PhysicsBody* pBody, vec3 pos, JointType jointType, PhysicsBody* otherBody)
{
    if (jointType == JointType::Revolute)
    {
        b2RevoluteJointDef jointDef;
        jointDef.Initialize( static_cast<PhysicsBodyBox2D*>(pBody)->Getb2Body(), m_pGroundBody, pos );
        b2Joint* pJoint = m_pWorld->CreateJoint( &jointDef );

        b2FrictionJointDef frictionDef;
        frictionDef.Initialize(static_cast<PhysicsBodyBox2D*>(pBody)->Getb2Body(), m_pGroundBody, pos);
        frictionDef.collideConnected = true;
        frictionDef.maxForce = 10.0f;
        frictionDef.maxTorque = 1.0f;
        b2Joint* pFriction = m_pWorld->CreateJoint(&frictionDef);

        return pJoint;

    }
    else if (jointType == JointType::Distance)
    {
        b2DistanceJointDef jointDef;
        jointDef.Initialize(static_cast<PhysicsBodyBox2D*>(pBody)->Getb2Body(), static_cast<PhysicsBodyBox2D*>(otherBody)->Getb2Body(), pBody->GetPosition(), otherBody->GetPosition());
        b2Joint* pJoint = m_pWorld->CreateJoint(&jointDef);
        return pJoint;
    }
}

b2Joint* PhysicsWorldBox2D::CreateJoint(PhysicsBody* pBody, b2Joint* jointOne, b2Joint* jointTwo, PhysicsBody* otherBody)
{
    b2GearJointDef jointDef;
    jointDef.joint1 = jointOne;
    jointDef.joint2 = jointTwo;
    jointDef.bodyA = static_cast<PhysicsBodyBox2D*>(otherBody)->Getb2Body();
    jointDef.bodyB = static_cast<PhysicsBodyBox2D*>(pBody)->Getb2Body();
    b2Joint* pJoint = m_pWorld->CreateJoint(&jointDef);

    return pJoint;
}

} // namespace fw
