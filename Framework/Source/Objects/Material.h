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
    Material(ShaderProgram* pShaderProgram, Texture* pTexture, Color4f color, Texture* pCubemap);
    virtual ~Material();

    ShaderProgram* GetShader() { return m_pShaderProgram; }
    Texture* GetTexture() { return m_pTexture; }
    Texture* GetCubemap() { return m_pCubemap; }

protected:
    ShaderProgram* m_pShaderProgram;
    Texture* m_pTexture;
    Color4f m_Color;
    Texture* m_pCubemap = nullptr;
};

} // namespace fw
