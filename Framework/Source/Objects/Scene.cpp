#include "CoreHeaders.h"

#include "Scene.h"
#include "Physics/PhysicsWorld.h"
#include "Objects/GameObject.h"
#include "Events/Event.h"
#include "Objects/Camera.h"
#include "Components/ComponentManager.h"
#include "../Libraries/imgui/imgui.h"
#include "GameObjects/Player.h"
#include "GameObjects/Meteor.h"

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

    //if (pEvent->GetEventType() == RemoveObjectEvent::GetStaticEventType())
    //{
    //    RemoveObjectEvent* pRemoveObEvent = static_cast<RemoveObjectEvent*>(pEvent);
    //    std::vector<GameObject*> pObject  = pRemoveObEvent->GetGameObjects();
    //    GameObject* pObjectToRemove = pRemoveObEvent->GetObjectToRemove();
    //    MeshComponent* pMeshToRemove = pRemoveObEvent->GetMeshToRemove();

    //    Player* pPlayer = dynamic_cast<Player*>(pObjectToRemove);
    //    Meteor* pMeteor = dynamic_cast<Meteor*>(pObjectToRemove);
    //    //Player
    //    if(pPlayer)
    //    {
    //        for (int i = 0; i < pObject.size(); i++)
    //        {
    //            Player* pPlayerToRemove = dynamic_cast<Player*>(pObject[i]);
    //            if (pPlayerToRemove)
    //            {
    //                pObject[i]->RemoveComponent(pMeshToRemove);
    //                pObject[i]->m_pPhysicsBody->GetBody()->SetEnabled(false);
    //                pObject.erase(std::next(pObject.begin(), i));
    //                break;
    //            }
    //        }
    //    }
    //    else if (pMeteor)
    //    {
    //        pObject.erase(std::next(m_ActiveObjects.begin(), i));
    //        m_pMeteors.push_back(MeteorToRemove);
    //        m_pMeteors.back()->m_pPhysicsBody->GetBody()->SetEnabled(false);
    //        m_pMeteors.back()->SetPosition(vec2(0, 7));
    //        m_pMeteors.back()->m_pPhysicsBody->SetPosition(m_pMeteors.back()->GetPosition());
    //        m_pMeteors.back()->RemoveComponent(m_pMeteorMeshComp);
    //    }

    //}
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
