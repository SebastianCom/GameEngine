#include "CoreHeaders.h"

#include "Framework.h"
#include "PhysicsBodyComponent.h"
#include "Physics/PhysicsWorld.h"
#include "Physics/Box2D/PhysicsBodyBox2D.h"
#include "Events/EventManager.h"
#include "Events/Event.h"

namespace fw {

PhysicsBodyComponent::PhysicsBodyComponent(PhysicsWorld* pWorld, bool dynamic, float density, GameObject* pGameObject, TransformComponent* pTransform)
    : m_pWorld(pWorld)
    , m_bDynamic(dynamic)
    , m_Density(density)
    , m_pGameObject(pGameObject)
{
    m_pBody = pWorld->CreateBody(pTransform, dynamic, density, pGameObject);

}

PhysicsBodyComponent::PhysicsBodyComponent(PhysicsWorld* pWorld, bool dynamic, float density, GameObject* pGameObject, TransformComponent* pTransform, bool sensor)
    : m_pWorld(pWorld)
    , m_bDynamic(dynamic)
    , m_Density(density)
    , m_pGameObject(pGameObject)
{
    m_pBody = pWorld->CreateBody(pTransform, dynamic, density, pGameObject, sensor);
}

PhysicsBodyComponent::~PhysicsBodyComponent()
{
    delete m_pBody;
}

void PhysicsBodyComponent::Editor_FillInspectorWindow(TransformComponent* pTransform)
{

    vec3 pos = m_pBody->GetPosition();
    vec3 rot = m_pBody->GetRotation();

    if (ImGui::DragFloat3("Physics Pos", &pos.x, 0.01f))
    {
        pTransform->SetPosition(pos);
    }
    if (ImGui::DragFloat3("Physics Rot", &rot.x, 1.0f))
    {
  
        m_pBody->SetEnabled(false);
        
        pTransform->SetRotation(rot);
    }
    ImGui::DragFloat3("Physics Scale", &m_Scale.x, 0.01f);

    m_pBody->SetTransform(pos, rot);
    
    m_pBody->SetEnabled(true);
}

void PhysicsBodyComponent::RegisterForEvents(EventManager* pEventManager)
{
    if (pEventManager)
    {
       pEventManager->RegisterForEvents(fw::CollisionEvent::GetStaticEventType(), this);
    }
}

void PhysicsBodyComponent::OnEvent(fw::Event* pEvent)
{
    if (pEvent->GetEventType() == fw::CollisionEvent::GetStaticEventType())
    {
        m_pGameObject->GetScene()->CollObjectA = dynamic_cast<CollisionEvent*>(pEvent)->m_pObjectA;
        m_pGameObject->GetScene()->CollObjectB = dynamic_cast<CollisionEvent*>(pEvent)->m_pObjectB;
    }
}

} // namespace fw
