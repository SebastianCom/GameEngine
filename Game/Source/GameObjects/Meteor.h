#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "Objects/GameObject.h"

class Scene;

class Meteor : public fw::GameObject
{
public:
    Meteor(fw::Scene* pScene, vec3 pos);
    virtual ~Meteor();

    virtual void Update(float deltaTime) override;
    //virtual void Draw() override;



protected:


};
