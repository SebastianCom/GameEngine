#pragma once

#include "Component.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"

namespace fw {

class TransformComponent : public Component
{
public:
    TransformComponent(vec3 pos, vec3 rot, vec3 scale);
    virtual ~TransformComponent();

    static const char* GetStaticType() { return "TransformComponent"; }
    virtual const char* GetType() override { return GetStaticType(); }

    void UpdateWorldTransform();
    const mat4& GetWorldTransform() const;

    vec3 GetPosition() { return m_Position; }
    vec3 GetRotation() { return m_Rotation; }
    vec3 GetScale() { return m_Scale; }

    void SetPosition(vec3 pos) { m_Position = pos; }
    void SetRotation(vec3 rot) { m_Rotation = rot; }
    void SetScale(vec3 scale) { m_Scale = scale; }

protected:
    mat4 m_WorldTranform;
    vec3 m_Position = vec3( 0, 0, 0 );
    vec3 m_Rotation = vec3( 0, 0, 0 );
    vec3 m_Scale = vec3( 1, 1, 1 );
};

} // namespace fw
