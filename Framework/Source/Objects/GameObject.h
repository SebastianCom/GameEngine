#pragma once

#include "../Libraries/box2d/include/box2d/box2d.h"
#include "Math/Vector.h"
#include "Physics/PhysicsBody.h"

namespace fw {

class Camera;
class GameCore;
class Mesh;

class PhysicsWorld;
class Material;

class GameObject
{
public:
    GameObject(GameCore* pGame, Mesh* pMesh, Material* pMaterial, vec2 pos);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera);

    void CreateBody(PhysicsWorld* pWorld, bool isDynamic, vec2 size, float density);

    // Getters.
    vec2 GetPosition() { return m_Position; }

    // Setters.
    //void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

protected:

    PhysicsBody* m_pPhysicsBody = nullptr;
    //b2Body* m_pPhysicsBody = nullptr;

    Mesh* m_pMesh = nullptr;
    
    Material* m_Material = nullptr;

    vec2 m_UVScale = vec2( 1, 1 );
    vec2 m_UVOffset = vec2( 0, 0 );

    vec2 m_Position = vec2( 0, 0 );
};

} // namespace fw
