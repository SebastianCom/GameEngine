#include "PhysicsBodyBox2D.h"

namespace fw {

	PhysicsBodyBox2D::PhysicsBodyBox2D(bool isDynamic, vec2 size, float density)
	{

        b2World* pWorld2D = pWorld->Getb2World();

        b2BodyDef bodyDef;

        bodyDef.position.Set(m_Position.x, m_Position.y);
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