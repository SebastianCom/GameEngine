#include "Framework.h"

#include "Meteor.h"
#include "PlayerController.h"

Meteor::Meteor(fw::Scene* pScene, vec3 pos)
    : GameObject("Meteor", pScene, pos)
{
}

Meteor::~Meteor()
{
}

void Meteor::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

}
