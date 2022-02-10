#include "CoreHeaders.h"

#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Utility/Utility.h"
#include "Math/MyMatrix.h"
#include "Material.h"


namespace fw {

Mesh::Mesh(GLenum primitiveType, const std::vector<VertexFormat>& verts)
    : m_PrimitiveType( primitiveType )
{
    m_NumVerts = (int)verts.size();

    // Generate a buffer for our vertex attributes.
    glGenBuffers( 1, &m_VBO );

    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    // Copy our attribute data into the VBO.
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*m_NumVerts, &verts[0], GL_STATIC_DRAW );
}

Mesh::Mesh(GLenum primitiveType, const std::vector<VertexFormat>& verts, const std::vector<unsigned int>& indices)
    :Mesh(primitiveType, verts)
{
    m_NumIndices = (int)indices.size();

    // Generate a buffer for our indices.
    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * m_NumIndices, &indices[0], GL_STATIC_DRAW);
}

Mesh::~Mesh()
{
    // Release the memory.
    glDeleteBuffers( 1, &m_VBO );
    glDeleteBuffers( 1, &m_IBO );
}

void Mesh::SetupUniform(ShaderProgram* pShader, char* name, float value)
{
    GLint location = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform1f( location, value );
}

void Mesh::SetupUniform(ShaderProgram* pShader, char* name, vec3 value)
{
    GLint location = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform2f( location, value.x, value.y );
}

void Mesh::SetupUniform(ShaderProgram* pShader, char* name, Color4f value)
{
    GLint location = glGetUniformLocation(pShader->GetProgram(), name);
    glUniform4f(location, value.r, value.g, value.b, value.a);
}

//void Mesh::SetupUniform(ShaderProgram* pShader, char* name, Color4f value)
//{
//    GLint location = glGetUniformLocation(pShader->GetProgram(), name);
//    glUniform4i(location, value.r, value.g, value.b, value.a);
//}

void Mesh::SetupAttribute(ShaderProgram* pShader, char* name, int size, GLenum type, GLboolean normalize, int stride, int64_t startIndex)
{
    GLint location = glGetAttribLocation( pShader->GetProgram(), name );
    if( location != -1 )
    {
        glEnableVertexAttribArray( location );
        glVertexAttribPointer( location, size, type, normalize, stride, (void*)startIndex );
    }
}

void Mesh::Draw(Camera* pCamera, Material* pMaterial, MyMatrix worldMat, vec2 uvScale, vec2 uvOffset, float time)
{


    ShaderProgram* pShader = pMaterial->GetShader();
    Texture* pTexture = pMaterial->GetTexture();

    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

    // Get the attribute variable’s location from the shader.
    // Describe the attributes in the VBO to OpenGL.
    SetupAttribute( pShader, "a_Position", 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), offsetof(VertexFormat, pos) );
    SetupAttribute( pShader, "a_Color", 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), offsetof(VertexFormat, color));
    SetupAttribute( pShader, "a_UVCoord", 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), offsetof(VertexFormat, uv));

    // Setup the uniforms.
    glUseProgram( pShader->GetProgram() );


    GLint location = glGetUniformLocation(pShader->GetProgram(), "u_WorldMatrix");
    glUniformMatrix4fv(location, 1, false, &worldMat.m11);

    MyMatrix viewMat;
   //   viewMat.CreateLookAtView(vec3(pCamera->GetPosition().x, pCamera->GetPosition().y, -20), vec3(0, 1, 0), vec3(pCamera->GetPosition().x, pCamera->GetPosition().y, 0));
   viewMat.CreateLookAtView(pCamera->GetPosition() + vec3(0,0,-10), vec3(0, 1, 0), vec3(0, 0, 0));

    location = glGetUniformLocation(pShader->GetProgram(), "u_ViewMatrix");
    glUniformMatrix4fv(location, 1, false, &viewMat.m11);

    MyMatrix projMat;
    projMat.CreatePerspectiveVFoV(45.0f, 1.0f, 0.01f, 100.0f);
    location = glGetUniformLocation(pShader->GetProgram(), "u_ProjMatrix");
    glUniformMatrix4fv(location, 1, false, &projMat.m11);
   


    SetupUniform(pShader, "u_ProjectionScale", pCamera->GetProjectionScale());
    // Transform uniforms.
    SetupUniform( pShader, "u_ObjectTranslation", worldMat.GetTranslation() );
    SetupUniform( pShader, "u_ObjectScale", worldMat.GetScale() );
    SetupUniform( pShader, "u_UVScale", uvScale );
    SetupUniform( pShader, "u_UVOffset", uvOffset );
    SetupUniform( pShader, "u_Tint", pMaterial->GetColor());
    //SetupUniform( pShader, "u_Color", pMaterial->GetColor() );
    
    
    // Misc uniforms.
    SetupUniform( pShader, "u_Time", (float)GetSystemTimeSinceGameStart() );

    // Setup textures.
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );

    // Draw the primitive.
    if (m_NumIndices > 0)
    {
        glDrawElements(m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(m_PrimitiveType, 0, m_NumVerts);
    }
}

} // namespace fw
