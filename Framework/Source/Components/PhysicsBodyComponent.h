#pragma once

#include "Component.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Framework.h"

namespace fw {

class PhysicsWorld;
class PhysicsBody;
class TransformComponent;
class EventManager;
class Event;


class PhysicsBodyComponent : public Component, public EventListener
{
public:
    PhysicsBodyComponent(PhysicsWorld* pWorld, bool dynamic, float density, GameObject* pGameObject, TransformComponent* pTransform);
    virtual ~PhysicsBodyComponent();

    static const char* GetStaticType() { return "PhysicsBodyComponent"; }
    virtual const char* GetType() override { return GetStaticType(); }

    PhysicsBody* GetBody() { return m_pBody; };

    void Editor_FillInspectorWindow(TransformComponent* pTransform);

    void RegisterForEvents(EventManager* pEventManager);

    virtual void OnEvent(fw::Event* pEvent) override;

protected:

    PhysicsBody* m_pBody;
    PhysicsWorld* m_pWorld; 
    bool m_bDynamic; 
    float m_Density;

    GameObject* m_pGameObject = nullptr;

    vec3 m_Position = vec3( 0, 0, 0 );
    vec3 m_Rotation = vec3( 0, 0, 0 );
    vec3 m_Scale = vec3( 1, 1, 1 );
};

} // namespace fw
