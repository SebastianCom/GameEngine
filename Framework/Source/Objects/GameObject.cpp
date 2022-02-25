#include "Framework.h"

#include "GameObject.h"
#include "Scene.h"
#include "Components/MeshComponent.h"

namespace fw {

GameObject::GameObject(std::string name, Scene* pScene, vec3 pos)
    : m_pScene( pScene)
    , m_Position( pos )
    , m_Name(name)
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



        //Modified to set the sprite to fit the Body
        if (m_pShape == "Box" || m_pShape == nullptr)
        {
            b2Vec2 physicsPosition = m_pPhysicsBody->GetPosition();

            vec3 rotation = m_pPhysicsBody->GetRotation();
            m_Rotation = rotation;

            float zAngle = -m_pPhysicsBody->GetBody()->GetAngle() / PI * 90.0f; //Put this in wrapper and fix wrapper
            m_Rotation.Set(0, 0, zAngle);
            m_Position.Set(physicsPosition.x - (m_pPhysicsBody->GetSize().x / 2), physicsPosition.y - (m_pPhysicsBody->GetSize().y / 2), 0);

        }
        else if (m_pShape == "Circle") //TODO: Fix this for rotation of meteors 
        {
            b2Vec2 physicsPosition = m_pPhysicsBody->GetPosition();

            vec3 rotation = m_pPhysicsBody->GetRotation();
            m_Rotation = rotation;

            float zAngle = -m_pPhysicsBody->GetBody()->GetAngle() / PI * 180.0f; //Put this in wrapper and fix wrapper
           // m_Rotation.Set(0, 0, zAngle);
            m_Position.Set(physicsPosition.x - (m_pPhysicsBody->GetSize().x), physicsPosition.y - (m_pPhysicsBody->GetSize().y), 0);
            
            //m_Position.Set(physicsPosition.x , physicsPosition.y, 0);
            // vec2 newpos = vec2((m_Position.x * cos(zAngle)) - m_Position.y * sin(zAngle), (m_Position.y * cos(zAngle)) + m_Position.x * sin(zAngle));
           //vec2 newpos = vec2((m_Position.x + (0.35 * cos(zAngle))), (m_Position.y + (0.35 * sin(zAngle))));
            // m_Position.Set(newpos.x, newpos.y, 0);
           // m_Position.Set((m_Position.x * cos(zAngle)) - m_Position.y*sin(zAngle), (m_Position.y *cos(zAngle)) + m_Position.x * sin(zAngle), 0);
            //m_Position.Set(m_Position.x * (0.35 * cos(zAngle)), m_Position.y * (0.35 * sin(zAngle)), 0);

        } 
    }
}


void GameObject::CreateBody(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density)
{
    m_pPhysicsBody = pWorld->CreateBody(isDynamic, size, density, this);
    m_pPhysicsBody->SetPosition(m_Position);
    m_pPhysicsBody->SetRotation(m_Rotation);
    m_Scale = size;

}

void GameObject::CreateBody(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density, const char* shape)
{
    m_pPhysicsBody = pWorld->CreateBody(isDynamic, size, density, this, shape);
    m_pShape = shape;
    m_pPhysicsBody->SetPosition(m_Position);
    m_pPhysicsBody->SetRotation(m_Rotation);
    if (shape != "Circle" )
        m_Scale = size;
    else
        m_Scale = size*2;

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

void GameObject::RemoveComponent(Component* pComp)
{

    pComp->SetGameObject(this);
    m_pScene->GetComponentManager()->RemoveComponent(pComp);
    m_Components.push_back(pComp);
}


void GameObject::Editor_FillInspectorWindow()
{

    ImGui::Text("Selected Object: %s", GetName().c_str());
    //ImGui::DragFloat3("Position", &m_Position.x, 1.0f);
    //ImGui::DragFloat3("Rotation", &m_Rotation.x, 1.0f);

    if (m_pPhysicsBody)
    {
        m_pPhysicsBody->Editor_FillInspectorWindow();


    }
    ImGui::DragFloat3("Scale", &m_Scale.x, 0.1f);
}

} // namespace fw
