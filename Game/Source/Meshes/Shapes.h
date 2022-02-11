#pragma once

extern const std::vector<fw::VertexFormat> g_SpriteVerts;
extern const std::vector<unsigned int> g_SpriteIndices;
extern const std::vector<fw::VertexFormat> g_CubeVerts;
extern const std::vector<unsigned int> g_CubeIndices;
//extern  std::vector<fw::VertexFormat> g_WaterVerts;
fw::Mesh* CreatePlane(vec2 gridSize, vec3 worldSize );