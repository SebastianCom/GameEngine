#include "Framework.h"

#include "DataTypes.h"
#include "Shapes.h"

const std::vector<fw::VertexFormat> g_SpriteVerts =
{
    { vec3(-0.5f, 0.5f,0.0f),  255,255,255,255,  vec2(0.0f,1.0f), vec3(0,0,-1) }, // top left
    { vec3( 0.5f, 0.5f,0.0f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(0,0,-1) }, // top right
    { vec3(-0.5f,-0.5f,0.0f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(0,0,-1) }, // bottom left
    { vec3( 0.5f,-0.5f,0.0f),  255,255,255,255,  vec2(1.0f,0.0f), vec3(0,0,-1) }, // bottom right
};                                                            
const std::vector<unsigned int> g_SpriteIndices =
{
    0, 1, 2, 2, 1, 3,
};

const std::vector<fw::VertexFormat> g_CubeVerts =
{
    // Front
    { vec3(-0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,1.0f), vec3(0,0,-1) }, // top left
    { vec3( 0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(0,0,-1) }, // top right
    { vec3(-0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(0,0,-1) }, // bottom left
                                                                            
    { vec3( 0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(0,0,-1) }, // top right
    { vec3( 0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f), vec3(0,0,-1) }, // bottom right
    { vec3(-0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(0,0,-1) }, // bottom left

    // Back
    { vec3(-0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f), vec3(0,0,1) }, // top left
    { vec3(-0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(0,0,1) }, // bottom left
    { vec3( 0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(0,0,1) }, // top right
    { vec3( 0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,0.0f), vec3(0,0,1) }, // bottom right
    { vec3( 0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(0,0,1) }, // top right
    { vec3(-0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(0,0,1) }, // bottom left

    // Left
    { vec3(-0.5f, -0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f), vec3(-1,0,0) }, // top left
    { vec3(-0.5f,  0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(-1,0,0) }, // top right
    { vec3(-0.5f, -0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(-1,0,0) }, // bottom left
    { vec3(-0.5f,  0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f), vec3(-1,0,0) }, // bottom right
    { vec3(-0.5f, -0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(-1,0,0) }, // bottom left
    { vec3(-0.5f,  0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(-1,0,0) }, // top right

    // Right
    { vec3(0.5f, -0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f), vec3(1,0,0) }, // top left
    { vec3(0.5f, -0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(1,0,0) }, // bottom left
    { vec3(0.5f,  0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(1,0,0) }, // top right
    { vec3(0.5f,  0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f), vec3(1,0,0) }, // bottom right
    { vec3(0.5f,  0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(1,0,0) }, // top right
    { vec3(0.5f, -0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(1,0,0) }, // bottom left

    // Top
    { vec3(-0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f), vec3(0,1,0) }, // top left
    { vec3( 0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(0,1,0) }, // top right
    { vec3(-0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(0,1,0) }, // bottom left
    { vec3( 0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f), vec3(0,1,0) }, // bottom right
    { vec3(-0.5f, 0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(0,1,0) }, // bottom left
    { vec3( 0.5f, 0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(0,1,0) }, // top right

    // Bottom
    { vec3(-0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f), vec3(0,-1,0) }, // top left
    { vec3(-0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(0,-1,0) }, // bottom left
    { vec3( 0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(0,-1,0) }, // top right
    { vec3( 0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f), vec3(0,-1,0) }, // bottom right
    { vec3( 0.5f,-0.5f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f), vec3(0,-1,0) }, // top right
    { vec3(-0.5f,-0.5f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f), vec3(0,-1,0) }, // bottom left
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

            verts.push_back( { pos,  255,255,255,255,  vec2(pos.x/5.0f, pos.z/5.0f), vec3(0,1,0) } );
        }
    }   

    fw::Mesh* pMesh = new fw::Mesh( GL_POINTS, verts ); //, indices );
    return pMesh;
};

fw::Mesh* CreateCylinder(float height, float radius, ivec2 vertCount, vec2 uvStart, vec2 uvRange)
{
    int numVerts = vertCount.x * vertCount.y;
    int numIndices = (vertCount.x - 1) * (vertCount.y - 1) * 6;

    std::vector<fw::VertexFormat> verts(numVerts);
    std::vector<unsigned int> indices(numIndices);

    float heightStepSize = height / (vertCount.y - 1);
    vec2 uvStepSize(uvRange.x / (vertCount.x - 1), uvRange.y / (vertCount.y - 1));

    for (int y = 0; y < vertCount.y; y++)
    {
        for (int x = 0; x < vertCount.x; x++)
        {
            float angle = (x / (float)(vertCount.x - 1)) * 2 * PI;
            vec2 circlePos = vec2(cos(angle), sin(angle)) * radius;

            verts[y * vertCount.x + x].pos = vec3(circlePos.x, y * heightStepSize, circlePos.y);
            verts[y * vertCount.x + x].normal = vec3(circlePos.x, 0, circlePos.y);
            verts[y * vertCount.x + x].normal.Normalize();
            verts[y * vertCount.x + x].uv = uvStart + vec2(x, y) * uvStepSize;
        }
    }

    for (int y = 0; y < vertCount.y - 1; y++)
    {
        for (int x = 0; x < vertCount.x - 1; x++)
        {
            indices[(y * (vertCount.x - 1) + x) * 6 + 0] = (y * vertCount.x + x) + 0;
            indices[(y * (vertCount.x - 1) + x) * 6 + 2] = (y * vertCount.x + x) + 1;
            indices[(y * (vertCount.x - 1) + x) * 6 + 1] = (y * vertCount.x + x) + vertCount.x;

            indices[(y * (vertCount.x - 1) + x) * 6 + 3] = (y * vertCount.x + x) + 1;
            indices[(y * (vertCount.x - 1) + x) * 6 + 5] = (y * vertCount.x + x) + vertCount.x + 1;
            indices[(y * (vertCount.x - 1) + x) * 6 + 4] = (y * vertCount.x + x) + vertCount.x;
        }
    }

    fw::Mesh* pMesh = new fw::Mesh(GL_TRIANGLES, verts, indices);
    return pMesh;
};

fw::Mesh* CreateSphere(float radius, ivec2 vertCount, vec2 uvStart, vec2 uvRange)
{
    int numVerts = vertCount.x * vertCount.y;
    int numIndices = (vertCount.x - 1) * (vertCount.y - 1) * 6;

    std::vector<fw::VertexFormat> verts(numVerts);
    std::vector<unsigned int> indices(numIndices);

    vec2 uvStepSize(uvRange.x / (vertCount.x - 1), uvRange.y / (vertCount.y - 1));

    for (int y = 0; y < vertCount.y; y++)
    {
        float hPerc = y / ((float)vertCount.y - 1) * 2 - 1; // -1 to 1

        for (int x = 0; x < vertCount.x; x++)
        {
            float ringRadius = sqrt(1 - hPerc * hPerc);
            float ringAngleRadians = (x / (float)(vertCount.x - 1)) * 2 * PI;
            vec2 ringPos = vec2(cos(ringAngleRadians), sin(ringAngleRadians)) * ringRadius;

            verts[y * vertCount.x + x].pos = vec3(ringPos.x, hPerc, ringPos.y) * radius;
            verts[y * vertCount.x + x].normal = vec3(ringPos.x, hPerc, ringPos.y) * radius;
            verts[y * vertCount.x + x].normal.Normalize();
            verts[y * vertCount.x + x].uv = uvStart + vec2(x, y) * uvStepSize;
        }
    }

    for (int y = 0; y < vertCount.y - 1; y++)
    {
        for (int x = 0; x < vertCount.x - 1; x++)
        {
            indices[(y * (vertCount.x - 1) + x) * 6 + 0] = (y * vertCount.x + x) + 0;
            indices[(y * (vertCount.x - 1) + x) * 6 + 2] = (y * vertCount.x + x) + 1;
            indices[(y * (vertCount.x - 1) + x) * 6 + 1] = (y * vertCount.x + x) + vertCount.x;

            indices[(y * (vertCount.x - 1) + x) * 6 + 3] = (y * vertCount.x + x) + 1;
            indices[(y * (vertCount.x - 1) + x) * 6 + 5] = (y * vertCount.x + x) + vertCount.x + 1;
            indices[(y * (vertCount.x - 1) + x) * 6 + 4] = (y * vertCount.x + x) + vertCount.x;
        }
    }

    fw::Mesh* pMesh = new fw::Mesh(GL_TRIANGLES, verts, indices);
    return pMesh;
};


fw::Mesh* CreatePlane(vec3 topLeftPos, vec2 worldSize, ivec2 vertCount, vec2 uvStart, vec2 uvRange)
{
    int numVerts = vertCount.x * vertCount.y;
    int numIndices = (vertCount.x - 1) * (vertCount.y - 1) * 6;

    std::vector<fw::VertexFormat> verts(numVerts);
    std::vector<unsigned int> indices(numIndices);

    vec3 stepSize(worldSize.x / (vertCount.x - 1), 0, worldSize.y / (vertCount.y - 1));
    vec2 uvStepSize(uvRange.x / (vertCount.x - 1), uvRange.y / (vertCount.y - 1));

    for (int y = 0; y < vertCount.y; y++)
    {
        for (int x = 0; x < vertCount.x; x++)
        {
            verts[y * vertCount.x + x].pos = topLeftPos + vec3(x, 0, y) * stepSize;
            verts[y * vertCount.x + x].normal.Set(0, 1, 0);
            verts[y * vertCount.x + x].uv = uvStart + vec2(x, y) * uvStepSize;
        }
    }

    for (int y = 0; y < vertCount.y - 1; y++)
    {
        for (int x = 0; x < vertCount.x - 1; x++)
        {
            indices[(y * (vertCount.x - 1) + x) * 6 + 0] = (y * vertCount.x + x) + 0;
            indices[(y * (vertCount.x - 1) + x) * 6 + 1] = (y * vertCount.x + x) + vertCount.x;
            indices[(y * (vertCount.x - 1) + x) * 6 + 2] = (y * vertCount.x + x) + 1;

            indices[(y * (vertCount.x - 1) + x) * 6 + 3] = (y * vertCount.x + x) + 1;
            indices[(y * (vertCount.x - 1) + x) * 6 + 4] = (y * vertCount.x + x) + vertCount.x;
            indices[(y * (vertCount.x - 1) + x) * 6 + 5] = (y * vertCount.x + x) + vertCount.x + 1;
        }
    }

    fw::Mesh* pMesh = new fw::Mesh(GL_TRIANGLES, verts, indices);
    return pMesh;
};