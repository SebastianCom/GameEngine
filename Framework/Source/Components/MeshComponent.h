#pragma once

#include "Component.h"
#include "Math/Vector.h"
#include "Math/MyMatrix.h"



namespace fw {

class GameObject;
class Mesh;
class Material;
class Camera;

class MeshComponent : public Component
{
public:
    MeshComponent(Mesh* pMesh, Material* pMaterial);
    virtual ~MeshComponent();

    static const char* GetStaticType() { return "MeshComponent"; }
    virtual const char* GetType() override { return GetStaticType(); }

    virtual void Draw(Camera* pCamera, const MyMatrix& worldMat);


    void SetUVScale( vec2 uvScale);
    void SetUVOffset(vec2 uvOffset);

protected:
    
    Mesh* m_pMesh = nullptr;
    Material* m_pMaterial = nullptr;
    vec2 m_UVScale = vec2(1, 1);
    vec2 m_UVOffset = vec2(0, 0);
};

} // namespace fw
