
#include "PhysicsBodyBox2D.h"
#include "PhysicsWorldBox2D.h"
#include "PhysicsWorld.h"


namespace fw {

	PhysicsBodyBox2D::PhysicsBodyBox2D(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density)
	{

        b2World* pWorld2D = static_cast<PhysicsWorldBox2D*>(pWorld)->Getb2World();
        //b2World* pWorld2D = pWorld->Getb2World();

        b2BodyDef bodyDef;

        bodyDef.position.Set(m_Position.x, m_Position.y); /// this is not updating now, this is why gravity is not working i think
        if (isDynamic)
            bodyDef.type = b2_dynamicBody;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

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

    void PhysicsBodyBox2D::SetPosition(vec2 pos)
    {
        m_pBody->SetTransform(pos, 0);
    }

    b2Vec2 PhysicsBodyBox2D::GetPosition()
    {
        return  m_pBody->GetPosition();
    }

    b2Body* PhysicsBodyBox2D::GetBody()
    {
        return m_pBody;
    }

}