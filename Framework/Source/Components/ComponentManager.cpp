#include "CoreHeaders.h"

#include "ComponentManager.h"
#include "Component.h"
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
    for (Component* pComponent : m_Components[MeshComponent::GetStaticType()])
    {
        MeshComponent* pMesh = static_cast<MeshComponent*>(pComponent);
        const MyMatrix& worldTransform = pMesh->GetGameObject()->GetWorldTransform();
        pMesh->Draw(pCamera, worldTransform);
 
    }
}

void ComponentManager::AddComponent(Component* pComponent)
{
    std::vector<Component*>& list = m_Components[pComponent->GetType()];

    // Assert that the component *was not* already in the list.
    assert(std::find(list.begin(), list.end(), pComponent) == list.end());

    list.push_back( pComponent );
}

void ComponentManager::RemoveComponent(Component* pComponent)
{
    std::vector<Component*>& list = m_Components[pComponent->GetType()];

    // Assert that the component *was* in the list.
    assert(std::find(list.begin(), list.end(), pComponent) != list.end());

    list.erase(std::remove(list.begin(), list.end(), pComponent), list.end());
}

} // namespace fw
