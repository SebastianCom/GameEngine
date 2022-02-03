#include "Framework.h"

#include "GameObject.h"
#include "Scene.h"
#include "Components/MeshComponent.h"

namespace fw {

GameObject::GameObject(Scene* pScene, Mesh* pMesh, Material* pMaterial, vec3 pos)
    : m_pScene( pScene)
    , m_Position( pos )
{
    m_pMeshComponent = new MeshComponent(pMesh, pMaterial);
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
    if (m_pPhysicsBody)
    {
        b2Vec2 physicsPosition = m_pPhysicsBody->GetPosition();
        ImGui::Text("%0.2f, %0.2f, %0.2f", physicsPosition.x, physicsPosition.y, m_Position.z);
        
        vec3 rotation = m_pPhysicsBody->GetRotation();
        m_Rotation = rotation;

        float zAngle = -m_pPhysicsBody->GetBody()->GetAngle() / PI * 90.0f; //Put this in wrapper and fix wrapper
       m_Rotation.Set(0, 0, zAngle);

        m_Position.Set(physicsPosition.x, physicsPosition.y, 0);
    }
}

void GameObject::Draw(Camera* pCamera)
{
    
    m_Scale = vec3(1.f, 1.f, 1.f); 

    MyMatrix worldMat;
    worldMat.CreateSRT(m_Scale, m_Rotation, m_Position);


    m_pMeshComponent->Draw(pCamera, worldMat);
   
}

void GameObject::CreateBody(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density)
{
    m_pPhysicsBody = pWorld->CreateBody(isDynamic, size, density);
    m_pPhysicsBody->SetPosition(m_Position);
    m_pPhysicsBody->SetRotation(m_Rotation);

}

} // namespace fw
