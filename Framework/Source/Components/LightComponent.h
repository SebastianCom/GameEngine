#pragma once

#include "Component.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"

namespace fw {

class Mesh;

class LightComponent : public Component
{
public:
 

    LightComponent(vec3 pos, vec3 color, float radius, Mesh* mesh);
    virtual ~LightComponent();

    static const char* GetStaticType() { return "LightComponent"; }
    virtual const char* GetType() override { return GetStaticType(); }

    void SetPosition(vec3 pos) { m_Position = pos; }
    void SetColor(vec3 color) { m_Color = color;  }
    void SetRadius(float radius) { m_Radius = radius;  }

    vec3 GetPosition() { return m_Position; }
    vec3 GetColor() { return m_Color; }
    float GetRadius() { return m_Radius;  }

    void Editor_FillInspectorWindow(int index);

protected:

    vec3 m_Position;
    float m_Radius;
    vec3 m_Color;
    Mesh* m_pMesh;
};

} // namespace fw
