#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "Objects/GameObject.h"

class Enemy : public fw::GameObject
{
public:
    Enemy(fw::Scene* pScene, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec3 pos);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override;

protected:
};
