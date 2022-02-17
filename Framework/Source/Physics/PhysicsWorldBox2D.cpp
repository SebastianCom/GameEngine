#include "PhysicsWorldBox2D.h"
#include "Events/EventManager.h"
#include "Events/Event.h"

namespace fw {


	/// CONTACT LISTENER

	ContactListener::ContactListener(EventManager* pEventManager)
		: m_pEventManager(pEventManager)
	{
		//m_pEventManager;
	}
	ContactListener::~ContactListener()
	{
	}
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* pFixA = contact->GetFixtureA();
		b2Fixture* pFixB = contact->GetFixtureB();

		b2Body* pBodyA = pFixA->GetBody();
		b2Body* pBodyB = pFixB->GetBody();

		GameObject* pObjectA = reinterpret_cast<GameObject*>(pBodyA->GetUserData().pointer);
		GameObject* pObjectB = reinterpret_cast<GameObject*>(pBodyB->GetUserData().pointer);

		//create an event saying Object A and B hit each oter
		CollisionEvent* pCollision = new CollisionEvent(pObjectA, pObjectB);
		m_pEventManager->AddEvent(pCollision);

	}

	void ContactListener::EndContact(b2Contact* contact)
	{

	}

	/// Phyics world

	PhysicsWorldBox2D::PhysicsWorldBox2D(EventManager* pEventManager)
	{
		m_pWorld = new b2World(c_DefaultGravity);

		m_pContListener = new ContactListener(pEventManager);
		m_pWorld->SetContactListener(m_pContListener);
	}
	PhysicsWorldBox2D::~PhysicsWorldBox2D()
	{
		delete m_pWorld;
		delete m_pBody;
		delete m_pContListener;
	}

	void PhysicsWorldBox2D::Update(float deltaTime)
	{
		m_pWorld->Step(deltaTime, 8, 3);
	}

	void PhysicsWorldBox2D::SetGravity(vec2 gravity)
	{
		m_pWorld->SetGravity(gravity);
	}

	PhysicsBody* PhysicsWorldBox2D::CreateBody(bool isDynamic, vec2 size, float density, GameObject* gameOb)
	{
		m_pBody = new PhysicsBodyBox2D(this, isDynamic, size, density, gameOb);
		return m_pBody;
	}


}