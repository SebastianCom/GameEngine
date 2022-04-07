#pragma once

#include "Math/Vector.h"
#include "Math/Matrix.h"

namespace fw {

class Camera;
class ShaderProgram;
class Texture;

struct VertexFormat
{
    vec3 pos;
    unsigned char color[4];
    vec2 uv;
    vec3 normal;
};

class Mesh
{
public:
    Mesh(GLenum primitiveType, const std::vector<VertexFormat>& verts);
    Mesh(GLenum primitiveType, const std::vector<VertexFormat>& verts, const std::vector<unsigned int>& indices);
    Mesh(const char* objfilename);
    virtual ~Mesh();

    void Create(GLenum primitiveType, const std::vector<VertexFormat>& verts);
    void Create(GLenum primitiveType, const std::vector<VertexFormat>& verts, const std::vector<unsigned int>& indices);
    void LoadFromOBJ(const char* objfilename);

    void SetupUniform(ShaderProgram* pShader, char* name, float value);
    void SetupUniform(ShaderProgram* pShader, char* name, vec2 value);
    void SetupAttribute(ShaderProgram* pShader, char* name, int size, GLenum type, GLboolean normalize, int stride, int64_t startIndex);
    void Draw(Camera* pCamera, ShaderProgram* pShader, Texture* pTexture, const mat4& worldMat, const mat4& normalMat, vec2 uvScale, vec2 uvOffset, float time);

protected:
    GLuint m_VBO = 0;
    GLuint m_IBO = 0;
    GLenum m_PrimitiveType = GL_POINTS;
    int m_NumVerts = 0;
    int m_NumIndices = 0;

    std::vector<vec3> m_Vertices;
    std::vector<vec2> m_UVCoords;
    std::vector<vec3> m_Normals;
    std::vector<vec3> m_VertexFormat;
};

} // namespace fw
