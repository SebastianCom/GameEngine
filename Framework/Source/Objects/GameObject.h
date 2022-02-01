#pragma once

#include "../Libraries/box2d/include/box2d/box2d.h"
#include "Math/Vector.h"
#include "Physics/PhysicsBody.h"

namespace fw {

class Camera;
class GameCore;
class Mesh;
class Scene;
class PhysicsWorld;
class Material;

class GameObject
{
public:
    GameObject(Scene* pScene, Mesh* pMesh, Material* pMaterial, vec2 pos);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera);

    void CreateBody(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density);

    // Getters.
    vec2 GetPosition() { return m_Position; }
    vec3 GetRotation() { return m_Rotation; }
    vec3 GetScale() { return m_Scale; }

    // Setters.
    // void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }
    void SetPosition(vec2 pos) { m_Position = pos; }
    void SetRotation(vec3 rot) { m_Rotation = rot; }
    void SetScale(vec3 scale) { m_Scale = scale; }

protected:

    Scene* m_pScene = nullptr;

    PhysicsBody* m_pPhysicsBody = nullptr;
    //b2Body* m_pPhysicsBody = nullptr;

    Mesh* m_pMesh = nullptr;
    
    Material* m_Material = nullptr;

    vec2 m_UVScale = vec2( 1, 1 );
    vec2 m_UVOffset = vec2( 0, 0 );

    vec2 m_Position = vec2( 0, 0 );
    vec3 m_Rotation = vec3( 0, 0,0 );
    vec3 m_Scale = vec3( 0, 0,0 );
};

} // namespace fw
