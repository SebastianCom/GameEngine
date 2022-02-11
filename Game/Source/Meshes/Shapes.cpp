#include "Framework.h"

#include "DataTypes.h"
#include "Shapes.h"

const std::vector<fw::VertexFormat> g_SpriteVerts =
{
    //{ vec3(0.0f,1.0f,0.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    //{ vec3(1.0f,1.0f,0.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    //{ vec3(0.0f,0.0f,0.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    //{ vec3(1.0f,0.0f,0.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right

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
    { vec3(1.0f,0.0f,0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3(1.0f,1.0f,0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.0f,0.0f,0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(0.0f,1.0f,0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    

    // Back
    { vec3(0.0f,1.0f,-0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(1.0f,1.0f,-0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.0f,0.0f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(1.0f,0.0f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right

     // Right
    { vec3(1.0f,0.0f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3(1.0f,1.0f,-0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(1.0f,0.0f, 0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(1.0f,1.0f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left

     // Left
    { vec3(0.0f,0.0f, 0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3(0.0f,1.0f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.0f,0.0f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(0.0f,1.0f,-0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left

     // Top
    { vec3(1.0f,1.0f, 0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3(1.0f,1.0f,-0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.0f,1.0f, 0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(0.0f,1.0f,-0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
                      
     // Bottom
    { vec3(1.0f,0.0f,-0.5f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    { vec3(1.0f,0.0f, 0.5f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(0.0f,0.0f,-0.5f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(0.0f,0.0f, 0.5f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left

};

const std::vector<unsigned int> g_CubeIndices =
{
    0,1,2,2,1,3, 4,5,6,6,5,7, 8,9,10,10,9,11, 12,13,14,14,13,15, 16,17,18,18,17,19, 20,21,22,22,21,23 

};

fw::Mesh* CreatePlane(vec2 gridSize, vec3 worldSize)
{
   std::vector<unsigned int> g_WaterIndices;
   std::vector<fw::VertexFormat> g_WaterVerts;
    for (int x = 0; x < gridSize.x; x++)
    {
        for (int y = 0; y < gridSize.y; y++) // x * stepsize.x, y * stepsize.y
        {
            vec3 GridSize = vec3(x*(1 / (gridSize.x /worldSize.x)),0, y*(1 / (gridSize.y / worldSize.z)));
            
            g_WaterVerts.push_back({ GridSize,  255,255,255,255,  vec2(GridSize.x/10.f,GridSize.z / 10.f) });
            int bp = 1;
        }
    }

    //g_WaterIndices.push_back(gridSize.x * gridSize.y);
    //g_WaterIndices.push_back(gridSize.x);
    //g_WaterIndices.push_back((gridSize.x * gridSize.y) - gridSize.x);
    //
    //g_WaterIndices.push_back((gridSize.x * gridSize.y) - gridSize.x);
    //g_WaterIndices.push_back(gridSize.x);
    //g_WaterIndices.push_back(0);

    fw::Mesh* pMesh = new fw::Mesh(GL_POINTS, g_WaterVerts); //, indices );
    return pMesh;
}

