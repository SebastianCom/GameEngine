#pragma once

namespace fw {

    class Camera;
    class Event;
    class GameCore;
    class GameObject;
    class PhysicsWorld;
    class ComponentManager;

class Scene
{
public:
    Scene(GameCore* pGameCore);
    virtual ~Scene();

    virtual void StartFrame(float deltaTime) = 0;
    virtual void Update(float deltaTime);
    virtual void OnEvent(Event* pEvent);
    virtual void Draw();
    virtual void Reset() = 0;

    ComponentManager* GetComponentManager() { return m_pComponentManager; }

    void Editor_CreateObjectList();
    GameObject* m_pEditor_SelectedObject = nullptr;



protected:

    GameCore* m_pGame = nullptr;
    Camera* m_pCamera = nullptr;
    PhysicsWorld* m_pPhysicsWorld;
    std::vector<fw::GameObject*> m_ActiveObjects;
    ComponentManager* m_pComponentManager = nullptr;

    GameObject* CollObjectA = nullptr;
    GameObject* CollObjectB = nullptr;

};

} // namespace fw
