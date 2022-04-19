#pragma once

extern const std::vector<fw::VertexFormat> g_SpriteVerts;
extern const std::vector<unsigned int> g_SpriteIndices;

extern const std::vector<fw::VertexFormat> g_CubeVerts;

fw::Mesh* CreatePlane();
fw::Mesh* CreatePlane(vec3 topLeftPos, vec2 worldSize, ivec2 vertCount, vec2 uvStart, vec2 uvRange);
fw::Mesh* CreateSphere(float radius, ivec2 vertCount, vec2 uvStart, vec2 uvRange);
fw::Mesh* CreateCylinder(float height, float radius, ivec2 vertCount, vec2 uvStart, vec2 uvRange);
