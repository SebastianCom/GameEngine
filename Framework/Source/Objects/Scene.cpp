#include "CoreHeaders.h"

#include "Scene.h"
#include "GameObject.h"
#include "Components/ComponentManager.h"
#include "Events/Event.h"
#include "Objects/Camera.h"
#include "Physics/PhysicsWorld.h"
#include "../Libraries/imgui/imgui.h"

namespace fw {

Scene::Scene(GameCore* pGameCore)
    : m_pGame( pGameCore )
{
    m_pComponentManager = new ComponentManager();
}

Scene::~Scene()
{
    for( fw::GameObject* pObject : m_Objects )
    {
        delete pObject;
    }

    delete m_pCamera;

    delete m_pComponentManager;

    delete m_pPhysicsWorld;
}

void Scene::OnEvent(Event* pEvent)
{
    if( pEvent->GetEventType() == RemoveFromGameEvent::GetStaticEventType() )
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>( pEvent );
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find( m_Objects.begin(), m_Objects.end(), pObject );
        m_Objects.erase( it );

        delete pObject;
    }
}

void Scene::Update(float deltaTime)
{
    if( m_pPhysicsWorld != nullptr )
    {
        m_pPhysicsWorld->Update( deltaTime );
    }

    for( auto it = m_Objects.begin(); it != m_Objects.end(); it++ )
    {
        fw::GameObject* pObject = *it;
        pObject->Update( deltaTime );
    }

    m_pCamera->Update( deltaTime );

    Editor_CreateObjectList();
}

void Scene::Draw()
{
    m_pComponentManager->Draw( m_pCamera );
}

void Scene::ResizeCamera(float sizeX, float sizeY)
{
    // Aspect Ratio = width/height 

    float ARatio = sizeX / sizeY;

    m_pCamera->SetRatio(ARatio);
}


void Scene::Editor_CreateObjectList()
{
    ImGui::Begin( "Object List");

    if( ImGui::TreeNodeEx( this, ImGuiTreeNodeFlags_DefaultOpen, "Objects" ) )
    {
        for( GameObject* pObject : m_Objects )
        {
            char name[30];
            sprintf_s( name, 30, "%s", pObject->GetName().c_str() );

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            ImGui::TreeNodeEx( pObject, flags, name );
            if( ImGui::IsItemClicked() )
            {
                m_pEditor_SelectedObject = pObject;
            }
        }
        ImGui::TreePop();
    }

    ImGui::End(); // Object List

    if( m_pEditor_SelectedObject )
    {
        ImGui::Begin( "Inspector" );

        m_pEditor_SelectedObject->Editor_FillInspectorWindow();

        ImGui::End(); // Inspector
    }
}

} // namespace fw
