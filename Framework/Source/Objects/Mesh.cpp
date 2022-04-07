#include "CoreHeaders.h"

#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Utility/Utility.h"
#include "Math/Matrix.h"

namespace fw {

Mesh::Mesh(GLenum primitiveType, const std::vector<VertexFormat>& verts)
    : m_PrimitiveType( primitiveType )
{
    Create( primitiveType, verts );
}

Mesh::Mesh(GLenum primitiveType, const std::vector<VertexFormat>& verts, const std::vector<unsigned int>& indices)
{
    Create( primitiveType, verts, indices );
}

Mesh::Mesh(const char* objfilename)
{
    LoadFromOBJ(objfilename);
}

Mesh::~Mesh()
{
    // Release the memory.
    glDeleteBuffers( 1, &m_VBO );
    glDeleteBuffers( 1, &m_IBO );
}

void Mesh::Create(GLenum primitiveType, const std::vector<VertexFormat>& verts)
{
    Create( primitiveType, verts, std::vector<unsigned int>() );
}

void Mesh::Create(GLenum primitiveType, const std::vector<VertexFormat>& verts, const std::vector<unsigned int>& indices)
{
    glDeleteBuffers( 1, &m_VBO );
    glDeleteBuffers( 1, &m_IBO );

    m_PrimitiveType = primitiveType;
    m_NumVerts = (int)verts.size();
    m_NumIndices = (int)indices.size();

    // Generate a buffer for our vertex attributes.
    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*m_NumVerts, &verts[0], GL_STATIC_DRAW );

    if( m_NumIndices > 0 )
    {
        // Generate a buffer for our indices.
        glGenBuffers( 1, &m_IBO );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_NumIndices, &indices[0], GL_STATIC_DRAW );
    }
}

void Mesh::LoadFromOBJ(const char* objfilename)
{
    long length = 0;
    char* buffer = LoadCompleteFile(objfilename, &length);
    if (buffer == 0 || length == 0)
    {
        delete[] buffer;
        return;
    }
    char* next_token = 0;
    char* line = strtok_s(buffer, "\n", &next_token);

    while (line)
    {
        if (line[0] == 'v' && line[1] == ' ')
        {
            vec3 Temp;
            sscanf(line, "v %f %f %f", &Temp.x, &Temp.y, &Temp.z);
            m_Vertices.push_back(Temp);
        }
        else if (line[0] == 'v' && line[1] == 't')
        {
            vec2 Temp;
            sscanf(line, "vt %f %f", &Temp.x, &Temp.y);
            m_UVCoords.push_back(Temp);
        }
        else if (line[0] == 'v' && line[1] == 'n')
        {
            vec3 Temp;
            sscanf(line, "vn %f %f %f", &Temp.x, &Temp.y, &Temp.z);
            m_Normals.push_back(Temp);
        }
        else if (line[0] == 'f')
        {
            vec3 Temp;
            vec3 Temp2;
            vec3 Temp3;
            sscanf(line, "f %f/%f/%f %f/%f/%f %f/%f/%f", &Temp.x, &Temp.y, &Temp.z, &Temp2.x, &Temp2.y, &Temp2.z, &Temp3.x, &Temp3.y, &Temp3.z);
            m_VertexFormat.push_back(Temp);
            m_VertexFormat.push_back(Temp2);
            m_VertexFormat.push_back(Temp3);
        }

        OutputMessage("%s\n", line);
        line = strtok_s(0, "\n", &next_token);

    }

    std::vector<VertexFormat> verts;
    for (int i = 0; i < m_VertexFormat.size(); i++)
    {
        VertexFormat CurentVertexSet = { m_Vertices[(m_VertexFormat[i].x) - 1], 255, 255, 255, 255, m_UVCoords[(m_VertexFormat[i].y) - 1], m_Normals[(m_VertexFormat[i].z)-1] };
        verts.push_back(CurentVertexSet);
    }

    Create(GL_TRIANGLES, verts, std::vector<unsigned int>());
}

void Mesh::SetupUniform(ShaderProgram* pShader, char* name, float value)
{
    GLint location = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform1f( location, value );
}

void Mesh::SetupUniform(ShaderProgram* pShader, char* name, vec2 value)
{
    GLint location = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform2f( location, value.x, value.y );
}

void Mesh::SetupAttribute(ShaderProgram* pShader, char* name, int size, GLenum type, GLboolean normalize, int stride, int64_t startIndex)
{
    GLint location = glGetAttribLocation( pShader->GetProgram(), name );
    if( location != -1 )
    {
        glEnableVertexAttribArray( location );
        glVertexAttribPointer( location, size, type, normalize, stride, (void*)startIndex );
    }
}

void Mesh::Draw(Camera* pCamera, ShaderProgram* pShader, Texture* pTexture, const mat4& worldMat, const mat4& normalMat, vec2 uvScale, vec2 uvOffset, float time)
{
    //ShaderProgram* pShader = pMaterial->GetShader();
    //Texture* pTexture = pMaterial->GetTexture();

    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

    // Get the attribute variable’s location from the shader.
    // Describe the attributes in the VBO to OpenGL.
    SetupAttribute( pShader, "a_Position", 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), offsetof(VertexFormat, pos) );
    SetupAttribute( pShader, "a_Color", 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), offsetof(VertexFormat, color) );
    SetupAttribute( pShader, "a_UVCoord", 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), offsetof(VertexFormat, uv) );
    SetupAttribute( pShader, "a_Normal", 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), offsetof(VertexFormat, normal) );

    // Setup the uniforms.
    glUseProgram( pShader->GetProgram() );
    
    // Transform uniforms.
    GLint location = glGetUniformLocation( pShader->GetProgram(), "u_WorldMatrix" );
    glUniformMatrix4fv( location, 1, false, &worldMat.m11 );

    location = glGetUniformLocation(pShader->GetProgram(), "u_NormalMatrix");
    glUniformMatrix4fv(location, 1, false, &normalMat.m11);

    location = glGetUniformLocation( pShader->GetProgram(), "u_ViewMatrix" );
    glUniformMatrix4fv( location, 1, false, &pCamera->GetViewMatrix().m11 );

    location = glGetUniformLocation( pShader->GetProgram(), "u_ProjMatrix" );
    glUniformMatrix4fv( location, 1, false, &pCamera->GetProjectionMatrix().m11 );

    // Texture uniforms.
    SetupUniform( pShader, "u_UVScale", uvScale );
    SetupUniform( pShader, "u_UVOffset", uvOffset );

    GLint loc = glGetUniformLocation( pShader->GetProgram(), "u_MaterialColor" );
    Color4f matColor( 15.0f/255.0f, 103.0f/255.0f, 227.0f/255.0f, 1.0f );
    glUniform4f( loc, matColor.r, matColor.g, matColor.b, matColor.a );


    // Setup textures.
    if (pTexture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureID());
    }


    // Misc uniforms.
    SetupUniform( pShader, "u_Time", (float)GetSystemTimeSinceGameStart() );

    // Draw the primitive.
    if( m_NumIndices > 0 )
    {
        glDrawElements( m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, 0 );
    }
    else
    {
        glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
    }
}

} // namespace fw
