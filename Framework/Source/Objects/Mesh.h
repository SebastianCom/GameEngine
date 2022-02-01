#pragma once

#include "Math/Vector.h"

namespace fw {

class Camera;
class ShaderProgram;
class Texture;
class Material;

struct VertexFormat
{
    vec3 pos;
    unsigned char color[4];
    vec2 uv;
};

class Mesh
{
public:
    Mesh(GLenum primitiveType, const std::vector<VertexFormat>& verts);
    Mesh(GLenum primitiveType, const std::vector<VertexFormat>& verts, const std::vector<unsigned int>& indices);
    virtual ~Mesh();

    void SetupUniform(ShaderProgram* pShader, char* name, float value);
    void SetupUniform(ShaderProgram* pShader, char* name, vec2 value);
    void SetupAttribute(ShaderProgram* pShader, char* name, int size, GLenum type, GLboolean normalize, int stride, int64_t startIndex);
    void Draw(Camera* pCamera, Material* pMaterial, vec2 scale, vec2 pos, vec2 uvScale, vec2 uvOffset, float time);

protected:
    GLuint m_VBO = 0;
    GLuint m_IBO = 0;
    GLenum m_PrimitiveType = GL_POINTS;
    int m_NumVerts = 0;
    int m_NumIndices = 0;

};

} // namespace fw
