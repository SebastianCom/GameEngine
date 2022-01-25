#include "Framework.h"

#include "DataTypes.h"
#include "Shapes.h"

const std::vector<fw::VertexFormat> g_SpriteVerts =
{
    { vec3(0.0f,1.0f,0.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec3(0.0f,0.0f,0.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec3(1.0f,1.0f,0.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
    { vec3(1.0f,0.0f,0.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
};
