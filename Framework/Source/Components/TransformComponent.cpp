#include "CoreHeaders.h"

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

} // namespace fw
