#pragma once

namespace fw {

class Camera;
class ComponentManager;
class Event;
class GameCore;
class GameObject;
class PhysicsWorld;

class Scene
{
public:
    Scene(GameCore* pGameCore);
    virtual ~Scene();

    virtual void StartFrame(float deltaTime) = 0;
    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltaTime);
    virtual void Draw();

    void ResizeCamera(float sizeX, float sizeY);

    ComponentManager* GetComponentManager() { return m_pComponentManager; }
    GameCore* GetGame() { return m_pGame; }
    Camera* GetCamera() { return m_pCamera; }

    void CreateLightComponents();


    GameObject* CollObjectA = nullptr;
    GameObject* CollObjectB = nullptr;

protected:
    void Editor_CreateObjectList();
    GameObject* m_pEditor_SelectedObject = nullptr;

protected:
    GameCore* m_pGame = nullptr;

    PhysicsWorld* m_pPhysicsWorld = nullptr;
    Camera* m_pCamera = nullptr;

    ComponentManager* m_pComponentManager = nullptr;

    std::vector<GameObject*> m_Objects;

};

} // namespace fw
