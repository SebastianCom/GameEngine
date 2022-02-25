#pragma once

#include "Math/Vector.h"
#include "Objects/GameObject.h"


namespace fw {

enum class DeviceType { Keyboard, Mouse };
enum class InputState { Pressed, Released };

//===============================================
// Event class
//===============================================
class Event
{
public:
    Event() {}
    virtual ~Event() {}

    // Event Type Getters.
    virtual const char* GetEventType() = 0;
};

//===============================================
// InputEvent class
//===============================================
class InputEvent : public Event
{
public:
    InputEvent(DeviceType deviceType, InputState inputState, int keyCode)
        : m_DeviceType( deviceType )
        , m_InputState( inputState )
        , m_ID( keyCode )
    {
    }

    // Event Type Getters.
    static const char* GetStaticEventType() { return "InputEvent"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }

    // Getters.
    DeviceType GetDeviceType() { return m_DeviceType; }
    InputState GetInputState() { return m_InputState; }
    int GetID() { return m_ID; }
    vec2 GetPosition() { return m_Pos; }

protected:
    DeviceType m_DeviceType;
    InputState m_InputState;
    int m_ID;
    vec2 m_Pos;
};

//===============================================
// RemoveFromGameEvent class
//===============================================
class RemoveFromGameEvent : public Event
{
public:
    RemoveFromGameEvent(GameObject* pObject)
    {
        m_pObject = pObject;
    }
    virtual ~RemoveFromGameEvent() {}

    // Event Type Getters.
    static const char* GetStaticEventType() { return "RemoveFromGameEvent"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }

    // Getters.
    GameObject* GetGameObject() { return m_pObject; }

protected:
    GameObject* m_pObject = nullptr;
};


//===============================================
// CollsionEvent class
//===============================================
class CollisionEvent : public Event
{
public:
    CollisionEvent(GameObject* pObjectA, GameObject* pObjectB)
    {
        m_pObjectA = pObjectA;
        m_pObjectB = pObjectB;
    }
    virtual ~CollisionEvent() {}
    // Event Type Getters.
    static const char* GetStaticEventType() { return "CollisionEvent"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }

    // Getters.
    GameObject* GetGameObjectA() { return m_pObjectA; }
    GameObject* GetGameObjectB() { return m_pObjectB; }

protected:
    GameObject* m_pObjectA = nullptr;
    GameObject* m_pObjectB = nullptr;
};

//===============================================
// RemoveObjectEvent class
//===============================================
class RemoveObjectEvent : public Event
{
public:
    RemoveObjectEvent(std::vector<GameObject*> pObjects, GameObject* pObjectToRemove, MeshComponent* pMeshComp, std::vector<GameObject*> pReturnPool)
    {
        m_Objects = pObjects;
        m_pObjectToRemove = pObjectToRemove;
        m_pMeshToRemove = pMeshComp;
    }
    virtual ~RemoveObjectEvent() {}
    // Event Type Getters.
    static const char* GetStaticEventType() { return "RemoveObjectEvent"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }

    std::vector<GameObject*> GetGameObjects() { return m_Objects; }
    GameObject* GetObjectToRemove() { return m_pObjectToRemove; }
    MeshComponent* GetMeshToRemove() { return m_pMeshToRemove; }

protected:
    std::vector<GameObject*> m_Objects;
    GameObject* m_pObjectToRemove = nullptr;
    MeshComponent* m_pMeshToRemove = nullptr;
};


} // namespace fw
