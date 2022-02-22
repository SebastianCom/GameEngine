#include "CoreHeaders.h"

#include "Scene.h"
#include "Physics/PhysicsWorld.h"
#include "Objects/GameObject.h"
#include "Events/Event.h"
#include "Objects/Camera.h"
#include "Components/ComponentManager.h"

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

} // namespace fw
