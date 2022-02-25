#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "Objects/GameObject.h"

class Scene;

class MeatChunk : public fw::GameObject
{
public:
    MeatChunk(fw::Scene* pScene, vec3 pos);
    virtual ~MeatChunk();

    virtual void Update(float deltaTime) override;
    //virtual void Draw() override;



protected:


};
