#pragma once

#include "../Libraries/box2d/include/box2d/box2d.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Components/Component.h"

namespace fw {

class Camera;
class Component;
class MeshComponent;
class GameCore;
class Mesh;
class ShaderProgram;
class Texture;
class PhysicsBody;
class PhysicsWorld;
class Scene;
class TransformComponent;
class PhysicsBodyComponent;
class LightComponent;

enum class JointType
{
    None = 0,
    Revolute,
    Distance,
    Prismatic,
    Line,
    Weld,
    Pulley,
    Friction,
    Gear,
    Mouse,
    MAX

};

class GameObject
{
public:
    GameObject(std::string name, Scene* pScene, vec3 pos);
    virtual ~GameObject();

    virtual void Update(float deltaTime);

    void CreateBody(PhysicsWorld* pWorld, bool isDynamic, float density);
    void CreateBody(PhysicsWorld* pWorld, bool isDynamic, float density, bool sensor);

    void AddComponent(Component* pComponent);

    void CreateLight(vec3 pos, vec3 color, float radius, Mesh* mesh);

    std::vector<LightComponent*> GetLightComponents() { return m_pLightComponent; };

    void CreateJoint(PhysicsWorld* pWorld, vec3 location, JointType joint, PhysicsBody* otherBody );
    void CreateJoint(PhysicsWorld* pWorld, b2Joint* jointOne, b2Joint* jointTwo, PhysicsBody* otherBody);

    // Getters.
    std::string GetName() { return m_Name; }
    TransformComponent* GetTransform() { return m_pTransform; }
    PhysicsBodyComponent* GetPhysicsBody() { return m_pPhysicsBody; }
    Scene* GetScene() { return m_pScene; }

    template <class Type>
    Type* GetComponent()
    {
        for( Component* pComponent : m_Components )
        {
            if( pComponent->GetType() == Type::GetStaticType() )
            {
                return static_cast<Type*>( pComponent );
            }
        }

        return nullptr;
    };


public:
    void Editor_FillInspectorWindow();

    b2RevoluteJoint* m_pRevJoint = nullptr;
    b2GearJoint* m_pGearJoint = nullptr;
    b2DistanceJoint* m_pDistanceJoint = nullptr;

protected:
    Scene* m_pScene = nullptr;
    std::string m_Name;

    TransformComponent* m_pTransform = nullptr;
    std::vector<Component*> m_Components;

    PhysicsBodyComponent* m_pPhysicsBody = nullptr;
    std::vector<LightComponent*> m_pLightComponent{};

    LightComponent* m_ClickedLight = nullptr;
    int LightIndex = 0;
   
};

} // namespace fw
