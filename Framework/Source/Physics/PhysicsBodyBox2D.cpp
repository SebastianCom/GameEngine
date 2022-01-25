
#include "PhysicsBodyBox2D.h"
#include "PhysicsWorldBox2D.h"


namespace fw {

	PhysicsBodyBox2D::PhysicsBodyBox2D(PhysicsWorldBox2D* pWorld, bool isDynamic, vec2 size, float density)
	{

        //b2World* pWorld2D = static_cast<PhysicsWorldBox2D*>(pWorld)->Getb2World();
        b2World* pWorld2D = pWorld->Getb2World();

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

}