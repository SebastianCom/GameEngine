#include "Framework.h"

#include "GameObject.h"
#include "Scene.h"
#include "Components/MeshComponent.h"

namespace fw {

GameObject::GameObject(Scene* pScene, vec3 pos)
    : m_pScene( pScene)
    , m_Position( pos )
{
 

    //pScene->GetComponentManager()->AddComponent(m_pMeshComponent);

    m_Scale = vec3(1.f, 1.f, 1.f);
}

GameObject::~GameObject()
{
    //for (Component* pComponent : m_Component)
    //{
    //    m_pScene->GetComponentManager()->RemoveComponent(pComponent);
    //    delete pComponent;
    //}
}

void GameObject::Update(float deltaTime)
{
    if (m_pPhysicsBody)
    {

        b2Vec2 physicsPosition = m_pPhysicsBody->GetPosition();

        vec3 rotation = m_pPhysicsBody->GetRotation();
        m_Rotation = rotation;

        float zAngle = -m_pPhysicsBody->GetBody()->GetAngle() / PI * 90.0f; //Put this in wrapper and fix wrapper
        m_Rotation.Set(0, 0, zAngle);

        //Modified to set the sprite to fit the Body
        m_Position.Set(physicsPosition.x - (m_pPhysicsBody->GetSize().x / 2), physicsPosition.y - (m_pPhysicsBody->GetSize().y / 2), 0);
    }
}


void GameObject::CreateBody(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density)
{
    m_pPhysicsBody = pWorld->CreateBody(isDynamic, size, density, this);
    m_pPhysicsBody->SetPosition(m_Position);
    m_pPhysicsBody->SetRotation(m_Rotation);
    m_Scale = size;

}

const MyMatrix& GameObject::GetWorldTransform() //Not technicallly get world matrix however, if i understand the content this is what was need for the object draw call task.
{
    m_WorldTransform.CreateSRT(m_Scale, m_Rotation, m_Position);
    return m_WorldTransform;
}

void GameObject::AddComponent(Component* pComp)
{
    pComp->SetGameObject(this);
    m_pScene->GetComponentManager()->AddComponent(pComp);
    m_Components.push_back(pComp);
}

} // namespace fw
