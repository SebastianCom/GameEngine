#include "CoreHeaders.h"

#include "Framework.h"
#include "PhysicsBodyComponent.h"
#include "Physics/PhysicsWorld.h"

namespace fw {

PhysicsBodyComponent::PhysicsBodyComponent(PhysicsWorld* pWorld, bool dynamic, float density, GameObject* pGameObject, TransformComponent* pTransform)
    : m_pWorld(pWorld)
    , m_bDynamic(dynamic)
    , m_Density(density)
{
    m_pBody = pWorld->CreateBody(pTransform, dynamic, density, pGameObject);
}

PhysicsBodyComponent::~PhysicsBodyComponent()
{

}

void PhysicsBodyComponent::Editor_FillInspectorWindow(TransformComponent* pTransform)
{

    vec3 pos = m_pBody->GetPosition();
    vec3 rot = m_pBody->GetRotation();

    if (ImGui::DragFloat3("Physics Pos", &pos.x, 0.01f))
    {
        pTransform->SetPosition(pos);
    }
    if (ImGui::DragFloat3("Physics Rot", &rot.x, 0.01f))
    {
        pTransform->SetRotation(rot);
    }
    ImGui::DragFloat3("Physics Scale", &m_Scale.x, 0.01f);

    m_pBody->SetTransform(pos, rot);
}

} // namespace fw
