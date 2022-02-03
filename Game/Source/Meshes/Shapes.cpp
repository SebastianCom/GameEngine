#include "Framework.h"

#include "DataTypes.h"
#include "Shapes.h"

const std::vector<fw::VertexFormat> g_SpriteVerts =
{
    { vec3(0.0f,1.0f,0.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(1.0f,1.0f,0.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.0f,0.0f,0.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(1.0f,0.0f,0.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
};

const std::vector<unsigned int> g_SpriteIndices =
{
    0,1,2,2,1,3,
};

const std::vector<fw::VertexFormat> g_CubeVerts =
{
    // Front
    { vec3(0.0f,1.0f,-1.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(1.0f,1.0f,-1.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.0f,0.0f,-1.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(1.0f,0.0f,-1.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    

    // Back
    { vec3(0.0f,1.0f,1.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(1.0f,1.0f,1.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.0f,0.0f,1.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(1.0f,0.0f,1.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right

     // Right
    { vec3(1.0f,1.0f,1.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(1.0f,1.0f,-1.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(1.0f,0.0f,1.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(1.0f,0.0f,-1.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right

     // Left
    { vec3(0.0f,1.0f,-1.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(0.0f,1.0f,1.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.0f,0.0f,-1.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(0.0f,0.0f,1.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right

};

const std::vector<unsigned int> g_CubeIndices =
{
    0,1,2,2,1,3, 4,5,6,6,5,7, 8,9,10,10,9,11, 12,13,14,14,13,15

    //3,1,2,2,1,0, 7,5,6,6,5,4,11,9,10,10,9,8,15,13,14,14,13,12
};

fw::Mesh* CreatePlane()
{
    std::vector<fw::VertexFormat> verts;
    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
           vec3 pos = vec3(float(x), float(y));
            verts.push_back({ pos,  255,255,255,255,  vec2(0.5f,0.5f) });
        }
    }

    //std::vector<unsigned int> indices;

    fw::Mesh* pMesh = new fw::Mesh(GL_POINTS, verts); //, indices );
    return pMesh;
}

