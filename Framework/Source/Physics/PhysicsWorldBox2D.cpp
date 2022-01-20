#include "PhysicsWorldBox2D.h"

namespace fw {
	PhysicsWorldBox2D::PhysicsWorldBox2D()
	{
		m_pWorld = new b2World(c_DefaultGravity);
	}
	PhysicsWorldBox2D::~PhysicsWorldBox2D()
	{
		delete m_pWorld;
	}

	void PhysicsWorldBox2D::Update(float deltaTime)
	{
		m_pWorld->Step(deltaTime, 8, 3);
	}

	void PhysicsWorldBox2D::SetGravity(vec2 gravity)
	{
		m_pWorld->SetGravity(gravity);
	}
}