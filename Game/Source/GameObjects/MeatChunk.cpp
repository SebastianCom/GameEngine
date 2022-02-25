#include "Framework.h"

#include "MeatChunk.h"

MeatChunk::MeatChunk(fw::Scene* pScene, vec3 pos)
    : GameObject("Meat Chunk", pScene, pos)
{

}

MeatChunk::~MeatChunk()
{
}

void MeatChunk::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

}
