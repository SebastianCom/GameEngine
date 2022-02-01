#include "Framework.h"

#include "GameObject.h"
#include "Scene.h"

namespace fw {

GameObject::GameObject(Scene* pScene, Mesh* pMesh, Material* pMaterial, vec2 pos)
    : m_pMesh( pMesh )
    , m_pScene( pScene)
    , m_Position( pos )
    , m_Material( pMaterial)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
    if (m_pPhysicsBody)
    {
        b2Vec2 physicsPosition = m_pPhysicsBody->GetPosition();
        ImGui::Text("%0.2f, %0.2f", physicsPosition.x, physicsPosition.y);
        m_Position.Set(physicsPosition.x, physicsPosition.y);
    }
}

void GameObject::Draw(Camera* pCamera)
{
    vec2 m_Scale = vec2(2, 2 );

    //mat4 worldMat;
    //worldMat.CreateSRT(m_Scale, m_Rotation, m_Position);

    m_pMesh->Draw( pCamera, m_Material, m_Scale, m_Position, m_UVScale, m_UVOffset, 0.0f );
}

void GameObject::CreateBody(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density)
{
    m_pPhysicsBody = pWorld->CreateBody(isDynamic, size, density);
    m_pPhysicsBody->SetPosition(m_Position); ///check if gravity is still working.
    int bp = 1;
}

} // namespace fw
