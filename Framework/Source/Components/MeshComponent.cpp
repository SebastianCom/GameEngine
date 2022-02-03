#include "CoreHeaders.h"

#include "MeshComponent.h"
#include "Objects/Mesh.h"

namespace fw {

MeshComponent::MeshComponent(Mesh* pMesh, Material* pMaterial)
    : Component()
    , m_pMesh(pMesh)
    , m_pMaterial(pMaterial)
{

}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::Draw(Camera* pCamera, MyMatrix& worldMat)
{
    m_pMesh->Draw( pCamera, m_pMaterial, worldMat, m_UVScale, m_UVOffset, 0.0f );
}

void MeshComponent::SetUVScale(vec2 uvScale)
{
    m_UVScale = uvScale;
}

void MeshComponent::SetUVOffset(vec2 uvOffset)
{
    m_UVOffset = uvOffset;
}

} // namespace fw
