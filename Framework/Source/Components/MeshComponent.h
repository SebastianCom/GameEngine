#pragma once

#include "Component.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"

namespace fw {

class Camera;
class GameObject;
class Material;
class Mesh;
class ShaderProgram;
class Texture;
class LightComponent;

class MeshComponent : public Component
{
public:
    //MeshComponent() = default;
    MeshComponent(Mesh* pMesh, Material* pMaterial);
    virtual ~MeshComponent();

    static const char* GetStaticType() { return "MeshComponent"; }
    virtual const char* GetType() override { return GetStaticType(); }

    void Draw(Camera* pCamera, const mat4& worldMat, const mat4& normalMat);

    void SetUVScale(vec2 uvScale) { m_UVScale = uvScale; }
    void SetUVOffset(vec2 uvOffset) { m_UVOffset = uvOffset; }

protected:
    Mesh* m_pMesh = nullptr;
    Material* m_pMaterial = nullptr;   
    LightComponent* m_LightComponent;
    vec2 m_UVScale = vec2( 1, 1 );
    vec2 m_UVOffset = vec2( 0, 0 );
};

} // namespace fw
