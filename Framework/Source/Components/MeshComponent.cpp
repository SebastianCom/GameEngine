#include "CoreHeaders.h"

#include "MeshComponent.h"
#include "Objects/Material.h"
#include "Objects/Mesh.h"

namespace fw {

MeshComponent::MeshComponent(Mesh* pMesh, Material* pMaterial)
    : Component()
    , m_pMesh( pMesh )
    , m_pMaterial( pMaterial )
{
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::Draw(Camera* pCamera, const mat4& worldMat, const mat4& normalMat)
{
    assert( m_pMesh != nullptr );

    m_pMesh->Draw( pCamera, m_pMaterial->GetShader(), m_pMaterial->GetTexture(), worldMat, normalMat, m_UVScale, m_UVOffset, 0.0f );
}

} // namespace fw
