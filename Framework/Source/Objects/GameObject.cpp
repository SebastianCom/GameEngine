#include "Framework.h"

#include "GameObject.h"
#include "Components/MeshComponent.h"
#include "Components/TransformComponent.h"
#include "Physics/PhysicsBody.h"

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
    if( m_pPhysicsBody )
    {
        GetTransform()->SetPosition( m_pPhysicsBody->GetPosition() );
        GetTransform()->SetRotation( m_pPhysicsBody->GetRotation() );
    }
}

void GameObject::CreateBody(PhysicsWorld* pWorld, bool isDynamic, float density)
{
    m_pPhysicsBody = pWorld->CreateBody( GetTransform(), isDynamic, density, this );
}

void GameObject::AddComponent(Component* pComponent)
{
    pComponent->SetGameObject( this );
    m_pScene->GetComponentManager()->AddComponent( pComponent );
    m_Components.push_back( pComponent );
}

void GameObject::Editor_FillInspectorWindow()
{
    ImGui::Text( "Name: %s", m_Name.c_str() );

    // TODO:
    // m_pTransform->Editor_FillInspectorWindow();
    //if( ImGui::DragFloat3( "Pos", &m_Position.x, 0.01f ) )
    //{
    //    m_pPhysicsBody->SetPosition( m_Position );
    //}
    //ImGui::DragFloat3( "Rot", &m_Rotation.x, 0.01f );
    //ImGui::DragFloat3( "Scale", &m_Scale.x, 0.01f );

    if( m_pPhysicsBody )
    {
        m_pPhysicsBody->Editor_FillInspectorWindow();
    }
}

} // namespace fw
