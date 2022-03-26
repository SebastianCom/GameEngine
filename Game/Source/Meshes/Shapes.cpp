#include "Framework.h"

#include "DataTypes.h"
#include "Shapes.h"

const std::vector<fw::VertexFormat> g_SpriteVerts =
{
    { vec3(-0.5f, 0.5f,0.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3( 0.5f, 0.5f,0.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(-0.5f,-0.5f,0.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3( 0.5f,-0.5f,0.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
};
const std::vector<unsigned int> g_SpriteIndices =
{
    0, 1, 2, 2, 1, 3,
};

const std::vector<fw::VertexFormat> g_CubeVerts =
{
    // Front
    { vec3(-0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3( 0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(-0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left

    { vec3( 0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3( 0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3(-0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left

    // Back
    { vec3(-0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(-0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3( 0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right

    { vec3( 0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3( 0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(-0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left

    // Left
    { vec3(-0.5f, -0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(-0.5f,  0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(-0.5f, -0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(-0.5f,  0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3(-0.5f, -0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(-0.5f,  0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right

    // Right
    { vec3(0.5f, -0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(0.5f, -0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(0.5f,  0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.5f,  0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3(0.5f,  0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.5f, -0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left

    // Top
    { vec3(-0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3( 0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(-0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3( 0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3(-0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3( 0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right

    // Bottom
    { vec3(-0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(-0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3( 0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3( 0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3( 0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(-0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
};

fw::Mesh* CreatePlane() //vec2 worldSize, ivec2 gridSize)
{
    std::vector<fw::VertexFormat> verts;

    vec2 stepSize = vec2( 1/100.0f, 1/100.0f );

    for( int y=0; y<1000; y++ )
    {
        for( int x=0; x<1000; x++ )
        {
            vec3 pos = vec3( x*stepSize.x, 0, y*stepSize.y );

            verts.push_back( { pos,  255,255,255,255,  vec2(pos.x/5.0f, pos.z/5.0f) } );
        }
    }   

    fw::Mesh* pMesh = new fw::Mesh( GL_POINTS, verts ); //, indices );
    return pMesh;
};
