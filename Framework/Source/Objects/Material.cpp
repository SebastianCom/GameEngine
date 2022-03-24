#include "CoreHeaders.h"

#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Utility/Utility.h"
#include "Math/Matrix.h"
#include "Material.h"

namespace fw {

Material::Material(ShaderProgram* pShaderProgram, Texture* pTexture, Color4f color)
    : m_pShaderProgram( pShaderProgram )
    , m_pTexture( pTexture )
    , m_Color( color )
{
}

Material::~Material()
{
}

} // namespace fw
