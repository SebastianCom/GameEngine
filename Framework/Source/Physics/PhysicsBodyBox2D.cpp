
#include "PhysicsBodyBox2D.h"
#include "PhysicsWorldBox2D.h"
#include "PhysicsWorld.h"
#include "Objects/GameObject.h"


namespace fw {

	PhysicsBodyBox2D::PhysicsBodyBox2D(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density, GameObject* gameOb)
	{

        b2World* pWorld2D = static_cast<PhysicsWorldBox2D*>(pWorld)->Getb2World();
        //b2World* pWorld2D = pWorld->Getb2World();

        b2BodyDef bodyDef;

        bodyDef.position.Set(m_Position.x, m_Position.y);
        bodyDef.angle = -m_Rotation.z / 180.0f * PI;
        if (isDynamic)
            bodyDef.type = b2_dynamicBody;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(gameOb);

        b2PolygonShape shape;
        shape.SetAsBox(size.x / 2, size.y / 2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = density;

        m_pBody = pWorld2D->CreateBody(&bodyDef);
        m_pBody->CreateFixture(&fixtureDef);

	}

	PhysicsBodyBox2D::~PhysicsBodyBox2D()
	{

	}

    void PhysicsBodyBox2D::SetPosition(vec3 pos)
    {
        m_Position = pos;
        m_pBody->SetTransform(pos, 0);
    }

    b2Vec2 PhysicsBodyBox2D::GetPosition()
    {
        return  m_pBody->GetPosition();
    }

    void PhysicsBodyBox2D::SetRotation(vec3 rot)
    {
        m_Rotation = rot;
        m_pBody->SetTransform(m_Position, rot.z);
    }

    vec3 PhysicsBodyBox2D::GetRotation()
    {
        return m_Rotation;
    }

    b2Body* PhysicsBodyBox2D::GetBody()
    {
        return m_pBody;
    }

}