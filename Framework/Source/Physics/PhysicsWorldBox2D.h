#pragma once

#include "../Libraries/box2d/include/box2d/box2d.h"
#include "Physics/PhysicsWorld.h"
#include "Math/Vector.h"

namespace fw {

    class EventManager;

    class ContactListener : public b2ContactListener
    {
    public:
        ContactListener(EventManager* pEventManager);
        virtual ~ContactListener();

        /// Called when two fixtures begin to touch.
        virtual void BeginContact(b2Contact* contact) override;

        /// Called when two fixtures cease to touch.
        virtual void EndContact(b2Contact* contact) override;

        EventManager* m_pEventManager;
    };

    class PhysicsWorldBox2D: public PhysicsWorld
    {
    public:
        PhysicsWorldBox2D(EventManager* pEventManager);
        virtual ~PhysicsWorldBox2D();
        virtual void Update(float deltaTime) override;
        virtual void SetGravity(vec2 gravity) override;
        virtual PhysicsBody* CreateBody(bool isDynamic, vec2 size, float density, GameObject* gameOb) override;

        b2World* Getb2World() { return m_pWorld; };

    protected:
        b2World* m_pWorld;
        ContactListener* m_pContListener;
    };






} // namespace fw