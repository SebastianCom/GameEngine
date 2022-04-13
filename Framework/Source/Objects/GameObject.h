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

class GameObject
{
public:
    GameObject(std::string name, Scene* pScene, vec3 pos);
    virtual ~GameObject();

    virtual void Update(float deltaTime);

    void CreateBody(PhysicsWorld* pWorld, bool isDynamic, float density);

    void AddComponent(Component* pComponent);

    void CreateLight(vec3 pos, vec3 color, float radius, Mesh* mesh);

    std::vector<LightComponent*> GetLightComponents() { return m_pLightComponent; };

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
