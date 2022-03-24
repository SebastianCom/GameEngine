#include "Framework.h"

#include "Enemy.h"

Enemy::Enemy(fw::Scene* pScene, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec3 pos)
    : GameObject( "Enemy", pScene, pos )
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
}
