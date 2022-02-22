#pragma once


#include "Math/Vector.h"
#include "PhysicsBody.h"
#include "PhysicsBodyBox2D.h"



namespace fw {

    class GameObject;
    class Camera;
    class Material;

    class PhysicsWorld
    {
    protected:
        static const vec2 c_DefaultGravity;
        PhysicsBody* m_pBody = nullptr;

    public:
        
        virtual ~PhysicsWorld() = 0 {}
        virtual void Update(float deltaTime) = 0;
        virtual void SetGravity(vec2 gravity) = 0;
        virtual PhysicsBody* CreateBody(bool isDynamic, vec2 size, float density, GameObject* gameOb) = 0 {};
        virtual void Draw(Camera* pCamera, Material* pMaterial) = 0;
    };

} // namespace fw
