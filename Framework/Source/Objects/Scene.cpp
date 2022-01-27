#include "CoreHeaders.h"

#include "Scene.h"
#include "Physics/PhysicsWorld.h"
#include "Objects/GameObject.h"
#include "Events/Event.h"
#include "Objects/Camera.h"

namespace fw {

Scene::Scene(GameCore* pGameCore)
{
	m_pGame = pGameCore;


}

Scene::~Scene()
{
    for (fw::GameObject* pObject : m_Objects)
    {
        delete pObject;
    }

    delete m_pPhysicsWorld;

    delete m_pCamera;
}

void Scene::Update(float deltaTime)
{
    m_pPhysicsWorld->Update(deltaTime); //maybbe this is what sets gavity

    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++)
    {
        fw::GameObject* pObject = *it;
        pObject->Update(deltaTime);
    }
}

void Scene::OnEvent(Event* pEvent)
{

    if (pEvent->GetEventType() == RemoveFromGameEvent::GetStaticEventType())
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find(m_Objects.begin(), m_Objects.end(), pObject);
        m_Objects.erase(it);

        delete pObject;
    }
}

void Scene::Draw()
{

    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++)
    {
        fw::GameObject* pObject = *it;
        pObject->Draw(m_pCamera);
    }
}

} // namespace fw
