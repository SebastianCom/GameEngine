#include "Framework.h"

#include "GameObject.h"
#include "Components/MeshComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PhysicsBodyComponent.h"
#include "Physics/PhysicsBody.h"
#include "Components/LightComponent.h"

namespace fw {

GameObject::GameObject(std::string name, Scene* pScene, vec3 pos)
    : m_Name( name )
    , m_pScene( pScene )
{
    m_pTransform = new TransformComponent( pos, vec3(0), vec3(1) );
    AddComponent( m_pTransform );
}

GameObject::~GameObject()
{
    for( Component* pComponent : m_Components )
    {
        m_pScene->GetComponentManager()->RemoveComponent( pComponent );
        delete pComponent;
    }
}

void GameObject::Update(float deltaTime)
{
    if (m_pPhysicsBody)
    {
        m_pScene->GetComponentManager()->UpdatePhysics(m_pPhysicsBody, m_pTransform);
    }
}

void GameObject::CreateBody(PhysicsWorld* pWorld, bool isDynamic, float density)
{
    m_pPhysicsBody = new fw::PhysicsBodyComponent(pWorld, isDynamic, density, this, m_pTransform);
    AddComponent(m_pPhysicsBody);
}

void GameObject::AddComponent(Component* pComponent)
{
    pComponent->SetGameObject( this );
    m_pScene->GetComponentManager()->AddComponent( pComponent );
    m_Components.push_back( pComponent );
}

void GameObject::CreateLight(vec3 pos, vec3 color, float radius, Mesh* mesh)
{
    m_pLightComponent = new fw::LightComponent(pos, color, radius, mesh);
    AddComponent(m_pLightComponent);
}

void GameObject::Editor_FillInspectorWindow()
{
    ImGui::Text( "Name: %s", m_Name.c_str() );
 
    

    if( m_pPhysicsBody )
    {
        m_pTransform->Editor_FillInspectorWindow(m_pPhysicsBody);
        m_pPhysicsBody->Editor_FillInspectorWindow(m_pTransform);
        m_pLightComponent->Editor_FillInspectorWindow();//TODO
    }
    else
        m_pTransform->Editor_FillInspectorWindow();
}

} // namespace fw
