#pragma once

namespace fw {

class Camera;
class Component;

class ComponentManager
{
public:
    ComponentManager();
    virtual ~ComponentManager() {}

    void Update(float deltaTime);
    void Draw(Camera* pCamera);

    void AddComponent(Component* pComponent);
    void RemoveComponent(Component* pComponent);

    void UpdatePhysics(Component* pPhysComp, Component* pTranComp);

    Component* GetComponentOftype(const char* pComponentName);

protected:
    std::map<const char*, std::vector<Component*>> m_Components; // for every component in the map they have a vector 
};

} // namespace fw
