#pragma once

#include "../Libraries/box2d/include/box2d/box2d.h"
#include "Math/Vector.h"
#include "Physics/PhysicsBody.h"
#include "Math/MyMatrix.h"
#include "Components/Component.h"


namespace fw {

class Camera;
class GameCore;
class Mesh;
class Scene;
class PhysicsWorld;
class Material;
class MeshComponent;
class Component;

class GameObject
{
public:
    GameObject(Scene* pScene, vec3 pos);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    //virtual void Draw(Camera* pCamera);

    void CreateBody(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density);
    void CreateBody(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density, const char* shape);

    // Getters.
    const MyMatrix& GetWorldTransform();
    vec3 GetPosition() { return m_Position; }
    vec3 GetRotation() { return m_Rotation; }
    vec3 GetScale() { return m_Scale; }


    void AddComponent(Component* pComp);
    void RemoveComponent(Component* pComp);
    //MeshComponent* GetComponent() { return m_pMeshComponent; }
    //MeshComponent* GetComponent(static const char* CompName);
    
    template <class Type>
    Type* GetComponent()
    {
        for (Component* pComponent : m_Components)
        {
            if (pComponent->GetType() == Type::GetStaticType())
            {
                return static_cast<Type*>(pComponent);
            }
        }
        return nullptr;
    }

    // Setters.
    // void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }
    void SetPosition(vec3 pos) { m_Position = pos; }
    void SetRotation(vec3 rot) { m_Rotation = rot; }
    void SetScale(vec3 scale) { m_Scale = scale; }
   

    PhysicsBody* m_pPhysicsBody = nullptr;

protected:

    Scene* m_pScene = nullptr;

    //b2Body* m_pPhysicsBody = nullptr;

    //TransformComponent* m_pTransform;
    //std::vector<component*> m_Components;

    MeshComponent* m_pMeshComponent = nullptr;
    std::vector<Component*> m_Components;

    MyMatrix m_WorldTransform;


    vec3 m_Position = vec3( 0, 0, 0 );
    vec3 m_Rotation = vec3( 0, 0, 0 );
    vec3 m_Scale = vec3( 0, 0, 0 );

    const char* m_pShape = nullptr;
};

} // namespace fw
