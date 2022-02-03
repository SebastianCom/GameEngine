#pragma once
#include "Math/Vector.h"

namespace fw {

    class ShaderProgram;
    class Texture;
    
    class Material
    {
    public:
        Material(ShaderProgram* m_pShader, Texture* m_pTexture, const Color4f m_Color());
        virtual ~Material();

        ShaderProgram* GetShader();
        Texture* GetTexture();
        Color4f GetColor();
    
    protected:
     
        ShaderProgram* m_Shader;
        Texture* m_Texture;
        Color4f Color;
        
    };

} // namespace fw
