#include "CoreHeaders.h"

#include "Scene.h"
#include "Physics/PhysicsWorld.h"
#include "Objects/GameObject.h"
#include "Events/Event.h"
#include "Objects/Camera.h"
#include "Components/ComponentManager.h"
#include "../Libraries/imgui/imgui.h"

namespace fw {

Scene::Scene(GameCore* pGameCore)
{
	m_pGame = pGameCore;

    m_pComponentManager = new ComponentManager();

}

Scene::~Scene()
{
    for (fw::GameObject* pObject : m_ActiveObjects)
    {
        delete pObject;
    }
    
    delete m_pCamera;
    
    delete m_pComponentManager;

    delete m_pPhysicsWorld;


}

void Scene::Update(float deltaTime)
{
    m_pPhysicsWorld->Update(deltaTime); 

    for (auto it = m_ActiveObjects.begin(); it != m_ActiveObjects.end(); it++)
    {
        fw::GameObject* pObject = *it;
        pObject->Update(deltaTime);
    }
    Editor_CreateObjectList();
   // m_pCamera->Update(deltaTime);
}

void Scene::OnEvent(Event* pEvent)
{

    if (pEvent->GetEventType() == RemoveFromGameEvent::GetStaticEventType())
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find(m_ActiveObjects.begin(), m_ActiveObjects.end(), pObject);
        m_ActiveObjects.erase(it);

        delete pObject;
    }

    if (pEvent->GetEventType() == CollisionEvent::GetStaticEventType())
    {
        CollisionEvent* pCollisionEvent = static_cast<CollisionEvent*>(pEvent);
        CollObjectA = pCollisionEvent->GetGameObjectA();
        CollObjectB = pCollisionEvent->GetGameObjectB();

    }
    else
    {
        CollObjectA = nullptr;
        CollObjectB = nullptr;
    }
}

void Scene::Draw()
{

    m_pComponentManager->Draw(m_pCamera);
   
    //for (auto it = m_ActiveObjects.begin(); it != m_ActiveObjects.end(); it++)
    //{
    //    fw::GameObject* pObject = *it;
    //    pObject->Draw(m_pCamera);
    //}
}

void Scene::Editor_CreateObjectList()
{
    ImGui::Begin("Object List");
    
    if( ImGui::TreeNodeEx(this, ImGuiTreeNodeFlags_DefaultOpen, "Objects"))
    {
        for (GameObject* pObject : m_ActiveObjects)
        {
            char name[30];
            sprintf_s(name, 30, "%s", pObject->GetName().c_str());

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            ImGui::TreeNodeEx(pObject, flags, name);
            if (ImGui::IsItemClicked())
            {
                // pObject->m_pPhysicsBody->GetBody()->SetEnabled(!pObject->m_pPhysicsBody->GetBody()->IsEnabled()); logic for a puase button i mmade up in class

                m_pEditor_SelectedObject = pObject;
            }
        }
        ImGui::TreePop();
    }
    ImGui::End(); // Object List

    if (m_pEditor_SelectedObject)
    {

        char name[30];
        sprintf_s(name, 30, "%s", m_pEditor_SelectedObject->GetName().c_str());

        ImGui::Begin("Inspector");
        m_pEditor_SelectedObject->Editor_FillInspectorWindow();
    


        ImGui::End(); // Selected Object
    }
    
}



} // namespace fw
