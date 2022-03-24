#pragma once

#include "Math/Vector.h"
#include "Math/Matrix.h"

namespace fw {

class ShaderProgram;
class Texture;

class Material
{
public:
    Material(ShaderProgram* pShaderProgram, Texture* pTexture, Color4f color);
    virtual ~Material();

    ShaderProgram* GetShader() { return m_pShaderProgram; }
    Texture* GetTexture() { return m_pTexture; }

protected:
    ShaderProgram* m_pShaderProgram;
    Texture* m_pTexture;
    Color4f m_Color;
};

} // namespace fw
