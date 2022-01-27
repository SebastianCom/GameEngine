#include "Framework.h"

#include "Enemy.h"

Enemy::Enemy(fw::GameCore* pGame, fw::Mesh* pMesh, fw::Material* pMaterial, vec2 pos)
    : GameObject( pGame, pMesh, pMaterial, pos )
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
}
