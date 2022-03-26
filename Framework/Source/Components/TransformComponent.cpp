#include "CoreHeaders.h"

#include "Framework.h"
#include "TransformComponent.h"

namespace fw {

TransformComponent::TransformComponent(vec3 pos, vec3 rot, vec3 scale)
    : m_Position( pos )
    , m_Rotation( rot )
    , m_Scale( scale )
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::UpdateWorldTransform()
{
    m_WorldTranform.CreateSRT( m_Scale, m_Rotation, m_Position );
}

const mat4& TransformComponent::GetWorldTransform() const
{
    return m_WorldTranform;
}

void TransformComponent::Editor_FillInspectorWindow(PhysicsBodyComponent* pPhysicsBody)
{

    if (ImGui::DragFloat3("Pos", &m_Position.x, 0.01f))
    {
        pPhysicsBody->GetBody()->SetTransform(m_Position, m_Rotation);
    }
    ImGui::DragFloat3("Rot", &m_Rotation.x, 0.01f);
    ImGui::DragFloat3("Scale", &m_Scale.x, 0.01f);
}
void TransformComponent::Editor_FillInspectorWindow()
{

    ImGui::DragFloat3("Pos", &m_Position.x, 0.01f);
    ImGui::DragFloat3("Rot", &m_Rotation.x, 0.01f);
    ImGui::DragFloat3("Scale", &m_Scale.x, 0.01f);
}

} // namespace fw
