#include "CoreHeaders.h"

#include "ComponentManager.h"
#include "Component.h"
#include "Components/TransformComponent.h"
#include "Components/PlayerMovementComponent.h"
#include "Components/PhysicsBodyComponent.h"
#include "Physics/PhysicsBody.h"
#include "MeshComponent.h"
#include "Objects/GameObject.h"

namespace fw {

ComponentManager::ComponentManager()
{
}

void ComponentManager::Update(float deltaTime)
{
}

void ComponentManager::Draw(Camera* pCamera)
{
    for( Component* pComponent : m_Components[TransformComponent::GetStaticType()] )
    {
        TransformComponent* pTransform = static_cast<TransformComponent*>( pComponent );
        pTransform->UpdateWorldTransform();
    }

    for( Component* pComponent : m_Components[MeshComponent::GetStaticType()] )
    {
        MeshComponent* pMeshComponent = static_cast<MeshComponent*>( pComponent );
        const mat4& worldTransform = pMeshComponent->GetGameObject()->GetTransform()->GetWorldTransform();
        pMeshComponent->Draw( pCamera, worldTransform );
    }
}

void ComponentManager::AddComponent(Component* pComponent)
{
    std::vector<Component*>& list = m_Components[pComponent->GetType()];

    // Assert that the component *was not* already in the list.
    assert( std::find(list.begin(), list.end(), pComponent) == list.end() );

    list.push_back( pComponent );
}

void ComponentManager::RemoveComponent(Component* pComponent)
{
    std::vector<Component*>& list = m_Components[pComponent->GetType()];

    // Assert that the component *was* in the list.
    assert( std::find(list.begin(), list.end(), pComponent) != list.end() );

    list.erase( std::remove(list.begin(), list.end(), pComponent), list.end() );
}

void ComponentManager::UpdatePhysics(Component* pPhysComp, Component* pTranComp)
{
    //for (Component* pPComponent : m_Components["PhysicsBodyComponent"])
    //{
    //    for (Component* pTComponent : m_Components["TransformComponent"])
    //    {
    //        PhysicsBodyComponent* pPhysicsBody = static_cast<PhysicsBodyComponent*>(pPComponent);
    //        TransformComponent* pTransform = static_cast<TransformComponent*>(pTComponent);
    //        //pTransform->SetPosition(pPhysicsBody->GetBody()->GetPosition());
    //       // pTransform->SetRotation(pPhysicsBody->GetBody()->GetRotation());
    //        pPhysicsBody->GetBody()->SetTransform(pTransform->GetPosition(), pTransform->GetRotation());
    //        int bp =1;
    //    }
    //}
   
    PhysicsBodyComponent* pPhysicsBody = static_cast<PhysicsBodyComponent*>(pPhysComp);
    TransformComponent* pTransform = static_cast<TransformComponent*>(pTranComp);

    pTransform->SetPosition(pPhysicsBody->GetBody()->GetPosition());
    pTransform->SetRotation(pPhysicsBody->GetBody()->GetRotation());

}

Component* ComponentManager::GetComponentOftype(const char* pComponentName) //MIDTERM
{

    for (Component* pComponent : m_Components[pComponentName])
    {
        PlayerMovementComponent* pPlayerMovemntComponent = static_cast<PlayerMovementComponent*>(pComponent);
        return pPlayerMovemntComponent;
    }
}

} // namespace fw
