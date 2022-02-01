#include "CoreHeaders.h"

#include "Material.h"

namespace fw {

    Material::Material(ShaderProgram* m_pShader, Texture* m_pTexture, const Color4f m_Color())
    {
        m_Shader = m_pShader;
        m_Texture = m_pTexture;
        Color = m_Color();
    }

    Material::~Material()
    {
        //delete m_Shader;
       // delete m_Texture;
    }

    ShaderProgram* Material::GetShader()
    {
        return m_Shader;
    }

    Texture* Material::GetTexture()
    {
        return m_Texture;
    }


} // namespace fw



